# Source Reference

Complete API documentation, source matrix, routing logic, and evidence tiers for all data sources.

---

## Source Matrix

| Source | Best use | Automation/access | Main limitation |
|--------|----------|-------------------|-----------------|
| Internet Archive | Public-domain/historical cookbooks, metadata, OCR, page scans | Advanced Search API; item metadata and search-inside services | OCR errors; some items access-restricted |
| Open Library | Editions, identifiers, subjects, borrowing/discovery | Public Search API | Metadata uneven; not an authenticity authority |
| Google Books | Discover books and matching terms; inspect permitted previews | Volumes API; identify public requests with an API key or OAuth token | Search snippets don't guarantee readable full text |
| HathiTrust | Historical catalog and full-text discovery at collection scale | Browser/catalog search; Bibliographic API for metadata | Many volumes search-only or limited view |
| TheMealDB | Quick international candidate discovery | Public API, no key | Crowd-sourced, shallow provenance |
| Edamam | Ingredient/diet filtering across large web index | API credentials and plan required | Aggregated web recipes; attribution and caching restrictions |
| Eat Your Books | Locate recipes across 2.6M indexed cookbooks + user's library | Manual account/browser; no public API | Index, not recipe text; membership required |
| Recipe1M+/RecipeNLG | Large-scale pattern discovery and candidate mining | Downloaded dataset, subject to license | Web-derived; duplicates, weak cultural provenance |
| Open Recipes / open-recipe-data | Local exploratory recipe search | Download and search locally | Older scraped data; links/licenses vary |
| WorldCat / library catalogs | Find physical library holdings, editions, bibliographic records | OCLC API or browser search | Metadata only, no recipe content |
| Cultural institutions | Regional, community, archival, and bibliographic evidence | Web/catalog/manual; sometimes APIs | Fragmented interfaces and access rules |
| Pepesto / URL parsers | Extract structured fields from known recipe pages | Service-specific API | Extraction does not establish authenticity |

## Routing — Which Sources to Use for Which Question

- **Historical origin** → Internet Archive, HathiTrust, national libraries, bibliographies, early editions
- **Published modern cookbook** → Eat Your Books, Google Books, Open Library, WorldCat, publisher/author
- **Community tradition** → Prioritize sources authored/edited/collected within the community; triangulate with oral histories, cultural institutions, regional cookbooks
- **Ingredient-based discovery** → Eat Your Books, Edamam, local datasets; then verify candidates in primary sources
- **Scale / pattern analysis** → Local datasets (Recipe1M+, RecipeNLG); deduplicate by normalized title, ingredient signature, source URL

## Evidence Tiers

1. **Tier 1** — Directly inspected recipe in a primary/community-proximate source with edition and page.
2. **Tier 2** — Directly inspected recipe in a reputable secondary cookbook or institutional collection.
3. **Tier 3** — Reliable catalog/index record pointing to a recipe not fully inspected.
4. **Tier 4** — Aggregated or crowd-sourced recipe with identifiable original source.
5. **Tier 5** — Unattributed aggregator, snippet, or dataset row.

Never promote a tier 3–5 lead into a tier 1–2 claim without opening corroborating evidence.

---

## 1. Internet Archive (archive.org)

### Advanced Search API (metadata + collection search)

**Endpoint:**
```
https://archive.org/advancedsearch.php
```

**Parameters:**
- `q` — Lucene query string
- `fl[]` — fields to return (repeat parameter for each field)
- `output` — `json`, `xml`, or `python`
- `rows` — number of results (max 10,000 per page)
- `page` — page number (1-indexed)
- `sort[]` — sort field + direction, e.g. `downloads desc`, `date asc`

**Cookbook-specific queries:**
```
# Discover cookbook-like text items whose metadata mentions a dish
q=mediatype:texts AND subject:"borscht" AND (subject:cooking OR subject:cookery)

# Historical cookbooks (pre-1900)
q=borscht AND mediatype:texts AND date:[null TO 1900]

# By language
q=borscht AND mediatype:texts AND language:ukr
```

**Example:**
```
https://archive.org/advancedsearch.php?q=borscht+AND+mediatype%3Atexts&fl[]=identifier&fl[]=title&fl[]=creator&fl[]=date&fl[]=downloads&output=json&rows=20&sort[]=downloads+desc
```

**Response format:**
```json
{
  "response": {
    "numFound": 82,
    "start": 0,
    "docs": [
      {
        "identifier": "klinovetska",
        "title": "Страви й напитки на Україні",
        "creator": "З. Клиновецька",
        "date": "1913-01-01T00:00:00Z",
        "downloads": 10859,
        "language": "ukr",
        "subject": ["Cuisine", "Ukrainian cuisine", "Borscht", ...]
      }
    ]
  }
}
```

### Item Metadata API

**Endpoint:**
```
https://archive.org/metadata/{identifier}
```

Returns: metadata (title, creator, date, language, subject, collection, pages), files list, and `server` (datanode hostname for full-text search).

Key fields:
- `metadata.title`, `metadata.creator`, `metadata.date`, `metadata.language`
- `server` — datanode hostname (e.g., `ia800204.us.archive.org`)
- `dir` — path to files (e.g., `/27/items/{identifier}`)
- `files` — array with `name`, `format`, `size`

### Full-Text Search Inside a Book

**Endpoint:**
```
https://{datanode}/fulltext/inside.php?item_id={identifier}&doc={identifier}&path={dir}&q={search+phrase}
```

Get `{datanode}`, `{dir}`, `{identifier}` from the Item Metadata API response.

**Response format:**
```json
{
  "ia": "identifier",
  "q": "\"borscht recipe\"",
  "page_count": 224,
  "matches": [
    {
      "text": "paragraph with {{{matched}}} {{{words}}} highlighted...",
      "par": [
        { "page": 42, "page_width": 2134, "page_height": 3328, ... }
      ]
    }
  ]
}
```

Matched words are surrounded by `{{{triple braces}}}`. The `par` array gives page numbers and coordinates.

### Scrape API (bulk retrieval)

```
https://archive.org/services/search/v1/scrape?fields=title,creator,date&q={query}
```

Returns 100 items per request. Use `cursor` for pagination.

### Useful IA Collections

| Collection | Description |
|------------|-------------|
| `cookery` | Historical cookbooks |
| `americana` | American Libraries |
| `opensource_media` | Community-uploaded |
| `ucldc` | California Digital Library |
| `smithsonian` | Smithsonian Libraries |
| `fedlink` | Federal libraries |

---

## 2. Open Library (openlibrary.org)

### Search API

**Endpoint:**
```
https://openlibrary.org/search.json
```

**Parameters:**
- `q` — Solr query (supports `title:`, `author:`, `subject:` qualifiers)
- `fields` — comma-separated list (special: `*` for all, `availability` for lendable status)
- `sort` — `new`, `old`, `random`, `key`, `rating`, `editions`
- `lang` — ISO 639-1 language code
- `limit` / `offset` — pagination

**Example:**
```
https://openlibrary.org/search.json?q=borscht&fields=key,title,author_name,first_publish_year,has_fulltext,availability&limit=20
```

### Search Inside API

```
https://openlibrary.org/search/inside.json?q={phrase}
```

Searches inside the full text of all indexed books.

### Work/Edition/Author APIs

```
https://openlibrary.org/works/{OL_ID}.json
https://openlibrary.org/books/{OL_ID}.json
https://openlibrary.org/authors/{OL_ID}.json
https://openlibrary.org/subjects/{subject}.json?limit=50
```

### Rate Limits

- Default: 1 req/sec. With User-Agent header: 3 req/sec.
- Always include: `User-Agent: CulinaryResearch/1.0 (contact@example.com)`

---

## 3. Google Books API

### Volume Search

**Endpoint:**
```
https://www.googleapis.com/books/v1/volumes
```

**Parameters:**
- `q` — search query with optional field qualifiers: `intitle:`, `inauthor:`, `subject:`, `isbn:`, `lccn:`, `oclc:`
- `maxResults` — max 40 (default 10)
- `startIndex` — pagination (0-indexed)
- `printType` — `books`, `magazines`, `all`
- `orderBy` — `relevance` or `newest`
- `langRestrict` — ISO 639-1 language code
- `filter` — `partial`, `full`, `free-ebooks`, `paid-ebooks`, `ebooks`
- `key` — API key (optional, increases quota)

Current Google documentation requires public-data requests to be identified with an API key or OAuth token. Set `GOOGLE_BOOKS_API_KEY`.

**Example:**
```
https://www.googleapis.com/books/v1/volumes?q=borscht+cooking&maxResults=20&printType=books
```

**Response fields:**
- `volumeInfo.title`, `volumeInfo.authors[]`, `volumeInfo.publishedDate`
- `volumeInfo.categories[]`, `volumeInfo.language`
- `volumeInfo.previewLink` — clickable preview
- `searchInfo.textSnippet` — text around search match
- `accessInfo.viewability` — `PARTIAL`, `FULL_PAGE`, `NO_PAGES`
- `accessInfo.publicDomain` — boolean

---

## 4. HathiTrust

### Bibliographic API

**Endpoint:**
```
https://catalog.hathitrust.org/api/volumes/brief/{return_type}/{search_ids}
https://catalog.hathitrust.org/api/volumes/full/{return_type}/{search_ids}
```

- `{return_type}`: `json` or `xml`
- `{search_ids}`: pipe-separated `|` list, format `{type}:{value}`
  - `isbn:1234567890`, `oclc:12345678`, `lccn:22005610`, `htid:uva.x000023213`

**Rights codes:**
- `pdus` / `pd` — public domain, Full View (can quote freely)
- `ic` / `ic-world` — in copyright, Limited search only
- `und` — undetermined

### Full-Text Catalog Search

No public REST API. Use the catalog search URL:
```
https://babel.hathitrust.org/cgi/ls?q1={query};a=srchls;lmt=ft
```

Or the HathiTrust Research Center for bulk analysis:
```
https://analytics.hathitrust.org/
```

---

## 5. TheMealDB

### Search by Name
```
https://www.themealdb.com/api/json/v1/1/search.php?s={dish}
```

### Lookup by ID
```
https://www.themealdb.com/api/json/v1/1/lookup.php?i={meal_id}
```

### List / Filter
```
https://www.themealdb.com/api/json/v1/1/list.php?a=list    # cuisine areas
https://www.themealdb.com/api/json/v1/1/list.php?c=list    # categories
https://www.themealdb.com/api/json/v1/1/filter.php?a={cuisine}
https://www.themealdb.com/api/json/v1/1/filter.php?i={ingredient}
```

The public key `1` is documented for development or educational use. Public production applications may require supporter access. Returns: name, category, area, instructions, ingredients (up to 20) with measurements, thumbnail, source URL, and video URL.

---

## 6. Edamam Recipe API

**Endpoint:**
```
https://api.edamam.com/api/recipes/v2
```

**Parameters:**
- `type` — `public` (free tier)
- `q` — search query
- `app_id`, `app_key` — credentials (register at developer.edamam.com)
- `cuisineType`, `mealType`, `dishType`, `diet`, `health` — filters
- `_links.next.href` — follow the returned link for pagination; v2 removed `from` / `to`

Set `EDAMAM_APP_ID` and `EDAMAM_APP_KEY`. Check the current plan for call limits, attribution, allowed fields, and caching; do not hard-code a universal free-tier quota.

---

## 7. Eat Your Books (eatyourbooks.com)

No public API. Manual browser workflow:
1. Create account (30-day free trial, ~$3-5/month)
2. Add cookbooks you own to your "bookshelf"
3. Search across 2.6M indexed recipes by ingredient, recipe type, cuisine, author, title
4. Results show: book title, author, page number, recipe name — not full recipe text
5. Use as a discovery/index layer, then find the actual book in IA/Open Library/HathiTrust

Best for: identifying which cookbooks contain a recipe, across a massive indexed collection.

---

## 8. WorldCat (worldcat.org)

### Search
```
https://search.worldcat.org/search?q={query}
```

### OCLC API (requires key)
```
https://americas.api.oclc.org/worldcat/search/v2/briefBibs?q={query}
```

Use WorldCat to find physical library holdings, rare editions, and bibliographic records. No recipe content — metadata only.

---

## 9. Local Datasets (Recipe1M+, RecipeNLG, Open Recipes)

Download and search locally. Pass file path to `--dataset` flag in the search script.

**Supported formats:** CSV, JSON, JSONL/NDJSON

**Sources:**
- Recipe1M+ (MIT) — 1M recipes from online sources: https://pic2recipe.csail.mit.edu/
- RecipeNLG (Kaggle) — expanded Recipe1M+: https://www.kaggle.com/datasets/saldenisov/recipenlg
- Open Recipes (GitHub) — https://github.com/fictive-kin/openrecipes
- jakevdp/open-recipe-data — https://github.com/jakevdp/open-recipe-data

**Caveat:** These are web-scraped from food blogs and Allrecipes, not from published cookbooks. Use for pattern analysis and candidate discovery, NOT as cultural authority.

---

## 10. Cultural Institutions

Search these manually via web/browser:
- **Slow Food Ark of Taste** — catalog of endangered food traditions: https://www.fondazioneslowfood.com/ark-of-taste/
- **UNESCO Intangible Cultural Heritage** — recognized food traditions: https://ich.unesco.org
- **National libraries** — country-specific cookbook archives
- **Culinary historians' societies** — publications and bibliographies
- **Regional museum collections** — food history exhibits and publications

---

## Rate Limiting Strategy

| Source | Rate Limit | Strategy |
|--------|-----------|----------|
| Internet Archive | No hard limit | 1 req/sec |
| Open Library | 1-3 req/sec | Use User-Agent header |
| Google Books | Project-specific | Use an API key; respect project quota |
| HathiTrust | No documented limit | 1 req/sec |
| TheMealDB | Terms/access tier vary | Keep development queries small |
| Edamam | Plan-specific | Do not cache unless the plan explicitly permits it |
| WorldCat/OCLC | Varies by plan | Check API docs |

## Caching

Public bibliographic/discovery responses are cached to `~/.hermes/cache/culinary-research/` as JSON files named by query hash. Edamam responses are not cached by default because its terms restrict persistence by plan.
