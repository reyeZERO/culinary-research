#!/usr/bin/env python3
"""
Culinary Research: Federated cookbook/recipe search across public APIs and local datasets.

Searches Internet Archive, Open Library, Google Books, HathiTrust, TheMealDB, and Edamam
in parallel, with optional local CSV/JSON/JSONL dataset search (Recipe1M+, RecipeNLG, etc.).

Usage:
    python3 search_cookbooks.py "borscht" --aliases "borsch,borsht,борщ" --limit 10 --pretty

    # Select specific sources
    python3 search_cookbooks.py "jollof rice" --sources internet-archive,open-library,themealdb --pretty

    # Include a local dataset
    python3 search_cookbooks.py "borscht" --dataset /path/to/recipes.jsonl --limit 20 --pretty

    # Full options
    python3 search_cookbooks.py "borscht" \\
        --aliases "borsch,борщ" \\
        --region "Ukraine" \\
        --sources google-books,internet-archive,open-library,themealdb,edamam \\
        --dataset /path/to/recipes.jsonl \\
        --timeout 30 \\
        --limit 20 \\
        --output results.json

Environment variables:
    GOOGLE_BOOKS_API_KEY  — expected for supported Google Books public-data requests
    EDAMAM_APP_ID         — required for Edamam
    EDAMAM_APP_KEY        — required for Edamam
"""

from __future__ import annotations

import argparse
import csv
import hashlib
import json
import os
import sys
import time
import urllib.error
import urllib.parse
import urllib.request
from pathlib import Path
from concurrent.futures import ThreadPoolExecutor, as_completed
from typing import Any, Iterable

# ─────────────────────────────────────────────────────────────────────────────
# Configuration
# ─────────────────────────────────────────────────────────────────────────────

CACHE_DIR = Path.home() / ".hermes" / "cache" / "culinary-research"

USER_AGENT = "CulinaryResearch/1.0 (hermes-agent)"

# Sources that work without credentials
PUBLIC_SOURCES = ("internet-archive", "open-library", "google-books", "hathitrust", "themealdb")

# All supported provider names
ALL_SOURCES = PUBLIC_SOURCES + ("edamam",)

# ─────────────────────────────────────────────────────────────────────────────
# HTTP utilities
# ─────────────────────────────────────────────────────────────────────────────

def cache_key(source: str, url: str) -> Path:
    CACHE_DIR.mkdir(parents=True, exist_ok=True)
    h = hashlib.md5(f"{source}:{url}".encode()).hexdigest()
    return CACHE_DIR / f"{source}_{h}.json"


def fetch_json(url: str, source: str, timeout: int = 20, use_cache: bool = True) -> Any:
    """Fetch JSON from a URL with caching and error handling."""
    if use_cache:
        ck = cache_key(source, url)
        if ck.exists():
            with open(ck) as f:
                return json.load(f)
    try:
        req = urllib.request.Request(url, headers={"User-Agent": USER_AGENT})
        with urllib.request.urlopen(req, timeout=timeout) as resp:
            data = json.loads(resp.read().decode("utf-8"))
        if use_cache:
            ck = cache_key(source, url)
            with open(ck, "w") as f:
                json.dump(data, f)
        return data
    except urllib.error.HTTPError as e:
        return {"_error": f"HTTP {e.code}: {e.reason}", "_url": url}
    except Exception as e:
        return {"_error": f"{type(e).__name__}: {e}", "_url": url}


def build_params(params: dict) -> str:
    """Build URL query string, handling list values by repeating keys (doseq=True)."""
    return urllib.parse.urlencode(params, doseq=True)


# ─────────────────────────────────────────────────────────────────────────────
# Source 1: Internet Archive
# ─────────────────────────────────────────────────────────────────────────────

def search_internet_archive(query: str, limit: int, timeout: int) -> list[dict]:
    """Discover cookbook-like Internet Archive texts from item metadata."""
    escaped = query.replace('"', '\\"')
    lucene_q = (
        f'mediatype:texts AND (title:"{escaped}" OR subject:"{escaped}" '
        f'OR description:"{escaped}") AND (subject:cooking OR subject:cookery '
        f'OR title:cook* OR description:recipe*)'
    )

    params = build_params({
        "q": lucene_q,
        "fl[]": ["identifier", "title", "creator", "date", "downloads", "language", "subject"],
        "output": "json",
        "rows": min(limit, 200),
        "sort[]": "downloads desc",
    })
    url = f"https://archive.org/advancedsearch.php?{params}"
    data = fetch_json(url, "internet-archive", timeout)

    if "_error" in data:
        return [{"source": "internet-archive", "error": data["_error"]}]

    results = []
    for doc in data.get("response", {}).get("docs", []):
        results.append({
            "source": "internet-archive",
            "identifier": doc.get("identifier", ""),
            "title": doc.get("title", ""),
            "creator": doc.get("creator", ""),
            "date": doc.get("date", ""),
            "language": doc.get("language", ""),
            "downloads": doc.get("downloads", 0),
            "subjects": doc.get("subject", []),
            "url": f"https://archive.org/details/{doc.get('identifier', '')}",
        })
    return results


def ia_search_inside(identifier: str, phrase: str, timeout: int = 20) -> dict:
    """Search inside a specific Internet Archive book for a phrase.

    First fetches item metadata to get the datanode host and path,
    then queries the inside.php full-text search endpoint.
    """
    # Get item metadata
    meta_url = f"https://archive.org/metadata/{identifier}"
    meta = fetch_json(meta_url, f"ia_meta_{identifier}", timeout)
    if "_error" in meta:
        return {"error": meta["_error"]}

    server = meta.get("d1") or meta.get("server", "")
    ddir = meta.get("dir", "")
    if not server or not ddir:
        return {"error": "Could not determine datanode host from metadata"}

    inside_params = build_params({
        "item_id": identifier,
        "doc": identifier,
        "path": ddir,
        "q": phrase,
    })
    inside_url = f"https://{server}/fulltext/inside.php?{inside_params}"
    data = fetch_json(inside_url, f"ia_inside_{identifier}", timeout)
    if "_error" in data:
        return {"error": data["_error"]}

    return {
        "identifier": identifier,
        "phrase": phrase,
        "page_count": data.get("page_count", 0),
        "match_count": len(data.get("matches", [])),
        "matches": [
            {
                "text": m.get("text", "")[:500],
                "pages": [p.get("page") for p in m.get("par", [])],
            }
            for m in data.get("matches", [])[:10]
        ],
    }


# ─────────────────────────────────────────────────────────────────────────────
# Source 2: Open Library
# ─────────────────────────────────────────────────────────────────────────────

def search_open_library(query: str, limit: int, timeout: int) -> list[dict]:
    """Search Open Library for books."""
    params = build_params({
        "q": query,
        "fields": (
            "key,title,author_name,first_publish_year,edition_count,has_fulltext,"
            "ia,availability,publish_year,language,subject"
        ),
        "limit": min(limit, 100),
    })
    url = f"https://openlibrary.org/search.json?{params}"
    data = fetch_json(url, "open-library", timeout)

    if "_error" in data:
        return [{"source": "open-library", "error": data["_error"]}]

    results = []
    for doc in data.get("docs", []):
        key = doc.get("key", "")
        results.append({
            "source": "open-library",
            "title": doc.get("title", ""),
            "authors": doc.get("author_name", []),
            "first_publish_year": doc.get("first_publish_year", ""),
            "publish_years": doc.get("publish_year", [])[:10],
            "edition_count": doc.get("edition_count", 0),
            "has_fulltext": doc.get("has_fulltext", False),
            "ia_identifiers": doc.get("ia", []),
            "availability": doc.get("availability"),
            "languages": doc.get("language", []),
            "subjects": doc.get("subject", [])[:20],
            "work_key": key,
            "url": f"https://openlibrary.org{key}" if key else "",
        })
    return results


# ─────────────────────────────────────────────────────────────────────────────
# Source 3: Google Books
# ─────────────────────────────────────────────────────────────────────────────

def search_google_books(query: str, limit: int, timeout: int) -> list[dict]:
    """Search Google Books API; set GOOGLE_BOOKS_API_KEY for supported public access."""
    query_params = {
        "q": query,
        "maxResults": min(limit, 40),
        "printType": "books",
        "orderBy": "relevance",
    }
    api_key = os.environ.get("GOOGLE_BOOKS_API_KEY")
    if api_key:
        query_params["key"] = api_key
    params = build_params(query_params)

    url = f"https://www.googleapis.com/books/v1/volumes?{params}"
    data = fetch_json(url, "google-books", timeout)

    # Handle errors (rate limits, quota)
    if "_error" in data:
        return [{
            "source": "google-books",
            "error": data["_error"],
            "note": "Set GOOGLE_BOOKS_API_KEY to identify the public-data request.",
        }]
    if isinstance(data.get("error"), dict):
        msg = data["error"].get("message", "Unknown error")
        return [{
            "source": "google-books",
            "error": msg,
            "note": "Check project quota and set GOOGLE_BOOKS_API_KEY.",
        }]

    results = []
    for item in data.get("items", []):
        vinfo = item.get("volumeInfo", {})
        access = item.get("accessInfo", {})
        results.append({
            "source": "google-books",
            "title": vinfo.get("title", ""),
            "authors": vinfo.get("authors", []),
            "publisher": vinfo.get("publisher", ""),
            "published_date": vinfo.get("publishedDate", ""),
            "categories": vinfo.get("categories", []),
            "language": vinfo.get("language", ""),
            "page_count": vinfo.get("pageCount", 0),
            "description": vinfo.get("description", "")[:500],
            "preview_link": vinfo.get("previewLink", ""),
            "info_link": vinfo.get("infoLink", ""),
            "viewability": access.get("viewability", "UNKNOWN"),
            "public_domain": access.get("publicDomain", False),
            "text_snippet": item.get("searchInfo", {}).get("textSnippet", ""),
            "volume_id": item.get("id", ""),
        })
    return results


# ─────────────────────────────────────────────────────────────────────────────
# Source 4: HathiTrust
# ─────────────────────────────────────────────────────────────────────────────

def search_hathitrust(query: str, limit: int, timeout: int) -> list[dict]:
    """HathiTrust: construct catalog search URL (no public REST full-text API)."""
    catalog_url = (
        f"https://babel.hathitrust.org/cgi/ls?q1={urllib.parse.quote(query)};a=srchls;lmt=ft"
    )
    return [{
        "source": "hathitrust",
        "note": "HathiTrust has no public REST full-text search API. Use the catalog URL.",
        "catalog_search_url": catalog_url,
        "query": query,
    }]


def hathitrust_bibliographic(id_type: str, id_value: str, timeout: int = 20) -> dict:
    """Query HathiTrust Bibliographic API by ISBN, OCLC, LCCN, or htid."""
    url = f"https://catalog.hathitrust.org/api/volumes/brief/json/{id_type}:{id_value}"
    return fetch_json(url, "hathitrust-bib", timeout)


# ─────────────────────────────────────────────────────────────────────────────
# Source 5: TheMealDB
# ─────────────────────────────────────────────────────────────────────────────

def search_themealdb(query: str, limit: int, timeout: int) -> list[dict]:
    """Search TheMealDB for recipes by name."""
    terms = [query]
    results = []
    seen_ids = set()

    for term in terms:
        url = f"https://www.themealdb.com/api/json/v1/1/search.php?s={urllib.parse.quote(term)}"
        data = fetch_json(url, f"themealdb_{term}", timeout)

        if "_error" in data:
            continue

        for meal in (data.get("meals") or []):
            meal_id = meal.get("idMeal", "")
            if meal_id in seen_ids:
                continue
            seen_ids.add(meal_id)

            ingredients = []
            for i in range(1, 21):
                ing = (meal.get(f"strIngredient{i}") or "").strip()
                meas = (meal.get(f"strMeasure{i}") or "").strip()
                if ing:
                    ingredients.append({"ingredient": ing, "measure": meas})

            results.append({
                "source": "themealdb",
                "meal_id": meal_id,
                "title": meal.get("strMeal", ""),
                "category": meal.get("strCategory", ""),
                "area": meal.get("strArea", ""),
                "instructions": meal.get("strInstructions", ""),
                "ingredients": ingredients,
                "thumbnail": meal.get("strMealThumb", ""),
                "source_url": meal.get("strSource", ""),
                "video_url": meal.get("strYoutube", ""),
            })

            if len(results) >= limit:
                return results
        time.sleep(0.1)

    return results


# ─────────────────────────────────────────────────────────────────────────────
# Source 6: Edamam
# ─────────────────────────────────────────────────────────────────────────────

def search_edamam(query: str, limit: int, timeout: int) -> list[dict]:
    """Search Edamam Recipe API. Requires EDAMAM_APP_ID and EDAMAM_APP_KEY."""
    app_id = os.environ.get("EDAMAM_APP_ID", "")
    app_key = os.environ.get("EDAMAM_APP_KEY", "")

    if not app_id or not app_key:
        return [{
            "source": "edamam",
            "error": "Edamam requires credentials. Set EDAMAM_APP_ID and EDAMAM_APP_KEY env vars.",
        }]

    params = build_params({
        "type": "public",
        "q": query,
        "app_id": app_id,
        "app_key": app_key,
    })
    url = f"https://api.edamam.com/api/recipes/v2?{params}"
    data = fetch_json(url, "edamam", timeout, use_cache=False)

    if "_error" in data:
        return [{"source": "edamam", "error": data["_error"]}]

    results = []
    for hit in data.get("hits", [])[:limit]:
        recipe = hit.get("recipe", {})
        results.append({
            "source": "edamam",
            "title": recipe.get("label", ""),
            "image": recipe.get("image", ""),
            "source_site": recipe.get("source", ""),
            "url": recipe.get("url", ""),
            "yield": recipe.get("yield", 0),
            "ingredient_lines": recipe.get("ingredientLines", []),
            "cuisine_type": recipe.get("cuisineType", []),
            "meal_type": recipe.get("mealType", []),
            "dish_type": recipe.get("dishType", []),
            "total_time": recipe.get("totalTime", 0),
        })
    return results


# ─────────────────────────────────────────────────────────────────────────────
# Local Dataset Search (Recipe1M+, RecipeNLG, Open Recipes, etc.)
# ─────────────────────────────────────────────────────────────────────────────

def _text_blob(record: dict) -> str:
    """Flatten all string values in a record into one lowercase string."""
    values = []
    for v in record.values():
        if isinstance(v, str):
            values.append(v)
        elif isinstance(v, list):
            values.extend(str(p) for p in v)
    return " ".join(values).casefold()


def _iter_dataset(path: Path) -> Iterable[dict]:
    """Iterate over records in a CSV, JSON, or JSONL file."""
    suffix = path.suffix.casefold()
    with path.open("r", encoding="utf-8-sig", errors="replace") as handle:
        if suffix == ".csv":
            yield from csv.DictReader(handle)
        elif suffix in (".jsonl", ".ndjson"):
            for line in handle:
                if line.strip():
                    val = json.loads(line)
                    if isinstance(val, dict):
                        yield val
        elif suffix == ".json":
            val = json.load(handle)
            if isinstance(val, list):
                yield from (item for item in val if isinstance(item, dict))
            elif isinstance(val, dict):
                rows = val.get("recipes") or val.get("items") or val.get("data") or []
                yield from (item for item in rows if isinstance(item, dict))
        else:
            raise ValueError(f"Unsupported dataset format: {suffix}. Use .csv, .json, .jsonl, or .ndjson")


def search_local_dataset(path: Path, query: str, limit: int) -> list[dict]:
    """Search a local dataset file for records matching any query term.

    Query may be a single term, a phrase, or an OR-joined list created for dataset search.
    Splits on ' OR ' and matches if ANY term group is found. Within each term
    group, all words must be present (AND within a group, OR between groups).
    """
    # Parse query into term groups: "a b" OR "c" → [["a","b"], ["c"]]
    raw_groups = query.split(" OR ")
    term_groups = []
    for g in raw_groups:
        words = [w.strip().strip('"').casefold() for w in g.split() if w.strip().strip('"')]
        if words:
            term_groups.append(words)

    matches = []
    for idx, record in enumerate(_iter_dataset(path), 1):
        blob = _text_blob(record)
        # Match if ANY term group has all its words present
        for words in term_groups:
            if all(w in blob for w in words):
                matches.append({
                    "source": "local-dataset",
                    "row": idx,
                    "record": record,
                })
                break
        if len(matches) >= limit:
            break
    return matches


# ─────────────────────────────────────────────────────────────────────────────
# Provider registry
# ─────────────────────────────────────────────────────────────────────────────

PROVIDERS = {
    "internet-archive": search_internet_archive,
    "open-library": search_open_library,
    "google-books": search_google_books,
    "hathitrust": search_hathitrust,
    "themealdb": search_themealdb,
    "edamam": search_edamam,
}


# ─────────────────────────────────────────────────────────────────────────────
# Orchestration
# ─────────────────────────────────────────────────────────────────────────────

def merge_results(groups: list[list[dict]], limit: int) -> list[dict]:
    """Deduplicate provider results while preserving the first useful occurrence."""
    merged = []
    seen = set()
    for group in groups:
        for item in group:
            identity = (
                item.get("identifier") or item.get("work_key") or
                item.get("volume_id") or item.get("meal_id") or
                item.get("catalog_search_url") or item.get("url") or item.get("title")
            )
            marker = json.dumps(identity, sort_keys=True, ensure_ascii=False)
            if marker in seen:
                continue
            seen.add(marker)
            merged.append(item)
            if len(merged) >= limit:
                return merged
    return merged


def search_all(
    queries: list[str],
    sources: list[str],
    limit: int,
    timeout: int,
    dataset: Path | None = None,
) -> dict[str, Any]:
    """Search selected sources in parallel, plus optional local dataset."""
    print(f"Searching: {', '.join(queries)}", file=sys.stderr)
    print(f"Sources: {', '.join(sources)}{' + local-dataset' if dataset else ''}", file=sys.stderr)

    results: dict[str, Any] = {}
    errors: dict[str, str] = {}

    # Parallel API searches
    grouped: dict[str, list[list[dict]]] = {name: [] for name in sources}
    with ThreadPoolExecutor(max_workers=min(8, max(1, len(sources) * len(queries)))) as executor:
        future_to_name = {
            executor.submit(PROVIDERS[name], query, limit, timeout): (name, query)
            for name in sources
            if name in PROVIDERS
            for query in queries
        }
        for future in as_completed(future_to_name):
            name, query = future_to_name[future]
            try:
                result = future.result()
                grouped[name].append(result)
                print(f"  [{name}:{query}] {len(result)} results", file=sys.stderr)
            except Exception as e:
                errors[f"{name}:{query}"] = f"{type(e).__name__}: {e}"
                print(f"  [{name}:{query}] ERROR: {e}", file=sys.stderr)
    for name, groups in grouped.items():
        results[name] = merge_results(groups, limit)

    # Local dataset search (sequential, may be slow for large files)
    if dataset:
        try:
            dataset_query = " OR ".join(f'"{query}"' for query in queries)
            ds_results = search_local_dataset(dataset, dataset_query, limit)
            results["local-dataset"] = ds_results
            print(f"  [local-dataset] {len(ds_results)} results", file=sys.stderr)
        except Exception as e:
            errors["local-dataset"] = f"{type(e).__name__}: {e}"
            print(f"  [local-dataset] ERROR: {e}", file=sys.stderr)

    if errors:
        results["_errors"] = errors

    return results


# ─────────────────────────────────────────────────────────────────────────────
# CLI
# ─────────────────────────────────────────────────────────────────────────────

def main() -> int:
    parser = argparse.ArgumentParser(
        description="Federated cookbook/recipe search across public APIs and local datasets."
    )
    parser.add_argument("dish", help="Name of the dish to search for")
    parser.add_argument("--aliases", default="", help="Comma-separated alternate names/transliterations")
    parser.add_argument("--region", default="", help="Region/country of origin (for context, stored in output)")
    parser.add_argument("--sources", default=",".join(PUBLIC_SOURCES),
                        help=f"Comma-separated source list (default: {','.join(PUBLIC_SOURCES)}). "
                             f"Available: {','.join(ALL_SOURCES)}")
    parser.add_argument("--dataset", type=Path, default=None,
                        help="Path to local CSV/JSON/JSONL dataset (Recipe1M+, RecipeNLG, etc.)")
    parser.add_argument("--limit", type=int, default=10, help="Max results per source (default: 10)")
    parser.add_argument("--timeout", type=int, default=20, help="HTTP timeout in seconds (default: 20)")
    parser.add_argument("--output", default="-", help="Output file path (- for stdout)")
    parser.add_argument("--pretty", action="store_true", help="Pretty-print JSON output")
    args = parser.parse_args()

    if args.limit < 1:
        parser.error("--limit must be positive")

    aliases = [a.strip() for a in args.aliases.split(",") if a.strip()] if args.aliases else []
    queries = list(dict.fromkeys([args.dish, *aliases]))

    # Parse and validate sources
    sources = [s.strip() for s in args.sources.split(",") if s.strip()]
    unknown = sorted(set(sources) - set(ALL_SOURCES))
    if unknown:
        parser.error(f"Unknown sources: {', '.join(unknown)}. Available: {', '.join(ALL_SOURCES)}")

    results = search_all(queries, sources, args.limit, args.timeout, args.dataset)

    output = {
        "query": {
            "dish": args.dish,
            "aliases": aliases,
            "region": args.region,
            "search_queries": queries,
            "limit": args.limit,
            "sources": sources,
            "dataset": str(args.dataset) if args.dataset else None,
        },
        "timestamp": time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime()),
        "results": results,
        "total_results": sum(len(v) for k, v in results.items() if isinstance(v, list) and k != "_errors"),
    }

    indent = 2 if args.pretty else None
    output_json = json.dumps(output, indent=indent, ensure_ascii=False)

    if args.output == "-":
        print(output_json)
    else:
        with open(args.output, "w") as f:
            f.write(output_json)
        print(f"Results written to {args.output}", file=sys.stderr)
        print(f"Total results: {output['total_results']}", file=sys.stderr)

    return 0 if output["total_results"] > 0 else 1


if __name__ == "__main__":
    raise SystemExit(main())
