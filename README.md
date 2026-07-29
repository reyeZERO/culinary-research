# Culinary Research Skill

A [Hermes Agent](https://hermes-agent.nousresearch.com) skill that searches thousands of digitized cookbooks and recipe databases to find the most authentic versions of dishes, recipes, and cooking techniques — with citations, page numbers, publication dates, and an authenticity-confidence rating.

## What It Does

Given a dish name, the skill:

1. Identifies the dish's original language, region, historical period, and all known transliterations
2. Searches **6 online databases** + **local datasets** in parallel across thousands of cookbooks
3. Compares multiple independent sources, tracing ingredient lists and techniques
4. Classifies recipes by variant type (historical, regional, diaspora, restaurant, modern, fusion)
5. Reconstructs a recommended version with a confidence rating (High / Moderate / Low / Indeterminate)
6. Produces a cited research report with page numbers, URLs, and copyright status

The skill does **not** label the first recipe it finds as "authentic." It follows a disciplined 8-phase methodology that compares multiple independent sources before producing a recommendation.

## Data Sources

| Source | Type | API | Best For |
|--------|------|-----|----------|
| **Internet Archive** | Digitized books | Advanced Search + inside-book full-text OCR | Historical cookbooks, primary sources, pre-1928 public domain |
| **Open Library** | Book catalog | Search API (JSON) | Editions, bibliographic data, availability |
| **Google Books** | Published books | Volumes API | Modern cookbooks, copyrighted preview search |
| **HathiTrust** | Research library | Bibliographic API + catalog search | 18M+ volumes, rights-coded access |
| **TheMealDB** | Recipe database | Free public API | International cuisine cross-checking |
| **Edamam** | Recipe database | API (free tier 1K/mo) | Ingredient/diet filtering, 2M recipes |
| **Eat Your Books** | Cookbook index | Manual (no API) | 2.6M indexed cookbook recipes |
| **Local datasets** | Recipe1M+, RecipeNLG, Open Recipes | `--dataset` flag | Pattern analysis, bulk mining |
| **Cultural institutions** | UNESCO, Slow Food, national libraries | Manual web search | Endangered traditions, heritage lists |

## Installation

### As a Hermes Agent Skill

```bash
# Clone into your Hermes skills directory
git clone https://github.com/reyeZERO/culinary-research.git \
  ~/.hermes/skills/research/culinary-research
```

The skill is automatically discovered by Hermes Agent on the next session start.

### Standalone Usage

The search script works independently — no Hermes required:

```bash
git clone https://github.com/reyeZERO/culinary-research.git
cd culinary-research
python3 scripts/search_cookbooks.py "borscht" --aliases "borsch,borsht,борщ" --pretty
```

## Usage

### Basic Search

```bash
python3 scripts/search_cookbooks.py "borscht" \
  --aliases "borsch,borsht,борщ,barszcz,bortsch" \
  --region "Ukraine" \
  --limit 20 \
  --pretty
```

### Select Specific Sources

```bash
python3 scripts/search_cookbooks.py "jollof rice" \
  --sources internet-archive,open-library,themealdb \
  --pretty
```

### Include a Local Dataset (Recipe1M+, RecipeNLG, etc.)

```bash
python3 scripts/search_cookbooks.py "borscht" \
  --dataset /path/to/recipes.jsonl \
  --limit 20 \
  --pretty
```

### Full Options

```bash
python3 scripts/search_cookbooks.py "borscht" \
  --aliases "borsch,борщ" \
  --region "Ukraine" \
  --sources internet-archive,open-library,google-books,hathitrust,themealdb,edamam \
  --dataset /path/to/recipes.jsonl \
  --timeout 30 \
  --limit 20 \
  --output results.json \
  --pretty
```

### Environment Variables

| Variable | Required | Description |
|----------|----------|-------------|
| `GOOGLE_BOOKS_API_KEY` | Optional | Increases Google Books API quota (free tier is rate-limited) |
| `EDAMAM_APP_ID` | For Edamam | Edamam application ID (register at [developer.edamam.com](https://developer.edamam.com)) |
| `EDAMAM_APP_KEY` | For Edamam | Edamam application key |

Without `GOOGLE_BOOKS_API_KEY`, Google Books may return HTTP 429 (rate limited). The script handles this gracefully — other sources continue working.

Without Edamam credentials, the script skips Edamam and reports a clear message.

### CLI Reference

```
usage: search_cookbooks.py [-h] [--aliases ALIASES] [--region REGION]
                           [--sources SOURCES] [--dataset DATASET]
                           [--limit LIMIT] [--timeout TIMEOUT]
                           [--output OUTPUT] [--pretty]
                           dish

positional:
  dish                   Name of the dish to search for

options:
  --aliases              Comma-separated alternate names/transliterations
  --region               Region/country of origin (stored in output metadata)
  --sources              Comma-separated source list
                         Default: internet-archive,open-library,google-books,hathitrust,themealdb
                         Available: internet-archive,open-library,google-books,hathitrust,themealdb,edamam
  --dataset              Path to local CSV/JSON/JSONL dataset
  --limit                Max results per source (default: 10)
  --timeout              HTTP timeout in seconds (default: 20)
  --output               Output file path (- for stdout)
  --pretty               Pretty-print JSON output
```

## How Authenticity Is Evaluated

The skill assesses each recipe across **10 dimensions**, rating each as strong, moderate, weak, conflicting, or unknown:

1. **Provenance** — Named author/collector, edition, page, traceable publication history
2. **Community proximity** — Creator connected to the represented community
3. **Geographic specificity** — Locality is precise and supported, not marketing
4. **Temporal fit** — Source date and recipe features fit the claimed period
5. **Linguistic evidence** — Original name, terminology, translation choices documented
6. **Technique continuity** — Characteristic process survives beyond a generic ingredient list
7. **Ingredient context** — Ingredients and substitutions fit local availability and historical trade
8. **Independent corroboration** — Multiple sources don't merely copy the same ancestor
9. **Genre/context** — Household, ceremonial, street, restaurant, diaspora, or famine cooking identified
10. **Access integrity** — The recipe was inspected, not inferred from a snippet or index

### Confidence Labels

| Label | Criteria |
|-------|----------|
| **High** | Directly inspected, community-proximate, independently corroborated |
| **Moderate** | Credible inspected evidence, limited corroboration |
| **Low** | Plausible lead, dominated by snippets/aggregators |
| **Indeterminate** | Insufficient evidence to choose among competing claims |

### Evidence Tiers

1. **Tier 1** — Directly inspected recipe in a primary/community source with edition and page
2. **Tier 2** — Directly inspected recipe in a reputable secondary cookbook
3. **Tier 3** — Reliable catalog/index record pointing to a recipe not fully inspected
4. **Tier 4** — Aggregated/crowd-sourced recipe with identifiable original source
5. **Tier 5** — Unattributed aggregator, snippet, or dataset row

Tier 3–5 leads are never promoted to tier 1–2 claims without opening corroborating evidence.

## Internet Archive Inside-Book Search

A unique feature: the script can search **inside** digitized books on Internet Archive for specific phrases, returning the matching text with page numbers. This goes beyond metadata search to actual recipe content in public-domain books.

```python
from scripts.search_cookbooks import ia_search_inside

# Search inside a specific book for a phrase
result = ia_search_inside("klinovetska", "борщ")
# Returns: page_count, match_count, and matches with text + page numbers
```

Example output from searching inside "Страви й напитки на Україні" (1913 Ukrainian cookbook):

```
Pages: 223
Matches: 47

  p.[5]: 1. Сирівець на борщ.          (Cold starter for borscht)
  p.[5]: 2. Буряковий квас на борщ.     (Beet kvass for borscht)
  p.[5]: 3. Борщ гетьманський.         (Hetman's borscht)
  p.[6]: 4. Борщ волинський.           (Volyn borscht)
```

## Local Dataset Format

The `--dataset` flag supports CSV, JSON, and JSONL/NDJSON files:

**JSONL format** (one JSON object per line):
```json
{"title": "Borscht", "ingredients": ["beets", "cabbage", "beef broth"], "source": "traditional"}
{"title": "Jollof Rice", "ingredients": ["rice", "tomato", "pepper"], "source": "Nigerian"}
```

**CSV format:**
```csv
title,ingredients,source
Borscht,"beets, cabbage, beef broth",traditional
Jollof Rice,"rice, tomato, pepper",Nigerian
```

**JSON format** (array or nested):
```json
{"recipes": [{"title": "Borscht", "ingredients": [...], ...}]}
```

### Where to Get Datasets

- [Recipe1M+ (MIT)](https://pic2recipe.csail.mit.edu/) — 1M recipes from online sources
- [RecipeNLG (Kaggle)](https://www.kaggle.com/datasets/saldenisov/recipenlg) — Expanded Recipe1M+
- [Open Recipes (GitHub)](https://github.com/fictive-kin/openrecipes) — Open recipe bookmarks
- [open-recipe-data (GitHub)](https://github.com/jakevdp/open-recipe-data) — Python-friendly recipe data

## Output Format

The script outputs JSON with results from each source:

```json
{
  "query": {
    "dish": "borscht",
    "aliases": ["borsch", "borsht", "борщ"],
    "region": "Ukraine",
    "sources": ["internet-archive", "open-library", ...],
    "dataset": null
  },
  "timestamp": "2026-07-29T15:13:14Z",
  "results": {
    "internet-archive": [
      {
        "source": "internet-archive",
        "identifier": "klinovetska",
        "title": "Страви й напитки на Україні",
        "creator": "З. Клиновецька",
        "date": "1913-01-01T00:00:00Z",
        "language": "ukr",
        "downloads": 10859,
        "subjects": ["Cuisine", "Ukrainian cuisine", "Borscht", ...],
        "url": "https://archive.org/details/klinovetska"
      }
    ],
    "open-library": [...],
    "themealdb": [...],
    "local-dataset": [...]
  },
  "total_results": 14
}
```

## Skill Structure

```
culinary-research/
├── SKILL.md                        # 8-phase methodology, source classes, guardrails
├── references/
│   ├── api-endpoints.md            # Complete API docs for all 10 source types
│   └── authenticity.md              # 10-dimension authenticity framework
├── scripts/
│   └── search_cookbooks.py         # Federated multi-source search script
└── templates/
    └── research-report.md          # Output report template
```

## The 8-Phase Methodology

1. **Define the Target** — Record dish name in original script, transliterations, region, period, community, meal context
2. **Build Query Variants** — Native names, historical spellings, distinctive techniques and ingredients
3. **Select Sources** — Route by question type (historical origin → IA/HathiTrust; modern cookbook → EYB/GB/OL)
4. **Run Discovery** — Federated search script across all sources in parallel
5. **Extract Evidence** — Capture title, author, year, edition, page, URL, access level, ingredient pattern, technique
6. **Compare** — Cluster by region/period/context, trace shared wording, identify stable vs contested features
7. **Evaluate Authenticity** — Assess all 10 dimensions, assign confidence per claim
8. **Deliver** — Cited report with variant comparison, reconstruction, confidence rating, access gaps

## Guardrails

- Does not claim full text unless access metadata confirms it
- Does not bypass paywalls, borrowing controls, or API terms
- Does not reproduce copyrighted recipes at length (summarizes and cites)
- Flags OCR uncertainty, missing pages, edition mismatch
- Keeps safety adaptations explicit when historic instructions conflict with modern food-safety guidance
- Practices descriptive authenticity ("documented in this community/time"), not prescriptive ("the only correct version")

## Caching

API responses are cached to `~/.hermes/cache/culinary-research/` as JSON files. Repeated searches for the same dish hit the cache instead of re-querying APIs. Clear the cache with:

```bash
rm -rf ~/.hermes/cache/culinary-research/
```

## Requirements

- Python 3.10+ (uses `from __future__ import annotations`)
- Internet connection for API sources
- Optional: `GOOGLE_BOOKS_API_KEY` for Google Books quota
- Optional: `EDAMAM_APP_ID` + `EDAMAM_APP_KEY` for Edamam
- No pip dependencies — uses only Python stdlib

## License

MIT — see [LICENSE](LICENSE)

## Acknowledgments

This skill combines the methodology and source coverage from multiple approaches to culinary research, including federated cookbook search, provenance-based authenticity evaluation, and historical recipe reconstruction.
