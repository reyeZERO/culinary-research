---
name: culinary-research
description: "Use when the user asks to research, find, reconstruct, or authenticate a recipe, dish, or cooking technique from cookbooks or culinary history. Searches Internet Archive, Open Library, Google Books, HathiTrust, TheMealDB, Edamam, local datasets (Recipe1M+/RecipeNLG), and Eat Your Books across thousands of digitized cookbooks and recipe databases to find the most authentic versions with citations, page numbers, publication dates, and an authenticity-confidence rating."
version: 2.0.0
author: Hermes Agent
license: MIT
platforms: [linux, macos, windows]
metadata:
  hermes:
    tags: [recipes, cookbooks, culinary, research, food, cuisine, authenticity, history]
    related_skills: [arxiv, blogwatcher]
---

# Culinary Research

## Overview

A methodology for searching thousands of digitized cookbooks and recipe databases to find the most authentic version of a dish, recipe, or technique. Combines multiple source classes in parallel, preserves provenance, and explains uncertainty. Never equates the top search result, an old publication date, or a claimed national label with authenticity.

## Source Classes

1. **Internet Archive** — Millions of digitized books with full-text OCR search, including historical cookbook collections. Lucene queries, JSON metadata, inside-book full-text search.
2. **Open Library** — Bibliographic search, editions, author data, availability for millions of books.
3. **Google Books API** — Full-text book discovery with access-dependent previews. Set `GOOGLE_BOOKS_API_KEY` to identify supported public-data requests.
4. **HathiTrust** — 18M+ volumes from research libraries. Bibliographic API with JSON, rights codes for public domain vs in-copyright.
5. **TheMealDB** — Free, crowd-sourced recipe database covering international cuisines.
6. **Edamam Recipe API** — 2M recipes with faceted search. Requires `EDAMAM_APP_ID` and `EDAMAM_APP_KEY`.
7. **Eat Your Books** — Indexes 2.6M recipes from cookbooks. Manual browser search (no API). Use as a discovery layer, then find the actual book in IA/OL/HathiTrust.
8. **Local datasets** — Recipe1M+, RecipeNLG, Open Recipes. Download and search locally via `--dataset` flag. Use for pattern analysis, not cultural authority.
9. **Cultural institutions** — Slow Food Ark of Taste, UNESCO Intangible Cultural Heritage, national libraries, culinary historians' societies. Manual web search.

## When to Use

- User asks to find an "authentic" or "traditional" version of a recipe
- User wants to research a dish's history, origin, or evolution
- User asks to compare regional variations of a dish
- User provides a cookbook PDF or scan and wants it searched
- User asks "how do they really make X in [region]?"
- User wants to know what ingredients are traditional vs modern substitutions

## Don't Use For

- Simple "give me a recipe for cookies" — use web_search or TheMealDB directly
- Nutritional analysis — use Edamam's nutrition API separately
- Restaurant recommendations — this is cookbook research, not Yelp
- Grocery/shopping list generation

## The Methodology (8 Phases)

### Phase 1: Define the Target

Record:
- Dish name in original script (e.g., "борщ", "جولوف")
- All transliterations and romanizations (e.g., "borscht" / "borsch" / "borsht" / "борщ")
- Region, country, and community of origin
- Historical period of earliest known documentation
- Cuisine category (e.g., Ottoman court cuisine, Sichuan home cooking, Italian regional)
- Meal context (household, ceremonial, street, restaurant, diaspora)
- Dietary constraints if requested
- Diaspora variants (e.g., Jewish diaspora borscht vs Ukrainian borscht)

Ask the user only when an unresolved ambiguity would materially change the search. Use web_search to establish this baseline before querying cookbook databases.

### Phase 2: Build Query Variants

Include:
- Native and English names
- Historical spellings
- Characteristic technique (e.g., "fermented beet" for borscht)
- Distinctive ingredients (e.g., "kvass" for authentic borscht)

Keep adaptations separate from historical/traditional searches. Do not mix "quick weeknight borscht" into a search for traditional recipes.

### Phase 3: Select Sources

Read `references/api-endpoints.md` for the source matrix and routing logic. Search at least two independent source classes when assessing authenticity.

**Routing by question type:**
- **Historical origin** → Internet Archive, HathiTrust, national libraries, bibliographies, early editions
- **Published modern cookbook** → Eat Your Books, Google Books, Open Library, WorldCat, publisher/author
- **Community tradition** → Prioritize sources authored/edited/collected within the community; triangulate with oral histories, cultural institutions, regional cookbooks
- **Ingredient-based discovery** → Eat Your Books, Edamam, local datasets; then verify candidates in primary sources
- **Scale/pattern analysis** → Local datasets (Recipe1M+, RecipeNLG); deduplicate by normalized title, ingredient signature, source URL

### Phase 4: Run Discovery

Use the federated search script for all API-accessible sources:

```bash
python3 ~/.hermes/skills/research/culinary-research/scripts/search_cookbooks.py \
  "borscht" \
  --aliases "borsch,borsht,борщ,barszcz,bortsch" \
  --region "Ukraine" \
  --sources internet-archive,open-library,google-books,hathitrust,themealdb \
  --limit 20 \
  --pretty
```

Select specific sources:
```bash
python3 scripts/search_cookbooks.py "jollof rice" \
  --sources internet-archive,open-library,themealdb --pretty
```

Include a local dataset (Recipe1M+, RecipeNLG, etc.):
```bash
python3 scripts/search_cookbooks.py "borscht" \
  --dataset /path/to/recipes.jsonl --limit 20 --pretty
```

Environment variables:
- `GOOGLE_BOOKS_API_KEY` — expected for supported Google Books public-data requests
- `EDAMAM_APP_ID` + `EDAMAM_APP_KEY` — required for Edamam

For sources without API support (Eat Your Books, HathiTrust catalog, WorldCat, cultural institutions), use web_search or browser navigation. Treat discovery results as leads, not proof.

Internet Archive Advanced Search discovers item metadata; it does not prove that OCR contains the query. For full-text search inside a specific book, use the `ia_search_inside` function or the inside.php endpoint documented in `references/api-endpoints.md`.

### Phase 5: Extract Evidence

For each candidate recipe found, capture:
- Title, author, publication year, edition, publisher
- Language of the source
- Page number or location
- Stable URL or identifier (IA identifier, OL key, GB volume ID, HathiTrust htid)
- Access level (full text, preview, snippet, metadata only, index only)
- Recipe name as printed
- Ingredient pattern (original quantities and terminology)
- Technique description
- Whether the recipe was directly inspected or inferred from a snippet/index

Distinguish: source text (quotation), paraphrase, inference, and the researcher's reconstruction. Never claim a source contains full text unless the returned access metadata or opened item confirms it.

### Phase 6: Compare

Read and apply `references/authenticity.md` for the full comparison framework.

Key rules:
- **Cluster before comparing.** Group recipes by region, period, and social context before comparing ingredients.
- **Normalize units only in a separate comparison layer.** Retain original quantities and terminology.
- **Create a variant table** when three or more recipes differ materially.
- **Trace shared wording** to detect copying. Repeated text is not independent confirmation.
- **Identify:** stable core features, regional branches, chronological changes, substitutions, and likely OCR errors.
- **Avoid "oldest equals original."** Survival in print reflects literacy, publishing infrastructure, class, and colonial archives.
- **Diaspora authenticity is real.** Treat diaspora forms as authentic to their own communities. Do not grade them only by homeland conformity.
- **Modern substitutions are substitutions, not fraud.** Describe them honestly.
- **Preserve plurality** when the record supports multiple living variants.

Distinguish:
- **Historically documented ingredients** — occur in inspected sources from the claimed community, place, and period
- **Regional variations** — different across sub-regions but all claim authenticity
- **Later substitutions** — appear in diaspora or modern sources, replacing unavailable ingredients
- **Restaurant adaptations** — simplified or amplified for restaurant service
- **Modern household versions** — convenience shortcuts (e.g., canned beets, bouillon cubes)

### Phase 7: Evaluate Authenticity

Read and apply `references/authenticity.md`. Assess each of the 10 dimensions:

1. Provenance
2. Community proximity
3. Geographic specificity
4. Temporal fit
5. Linguistic evidence
6. Technique continuity
7. Ingredient context
8. Independent corroboration
9. Genre/context
10. Access integrity

Assign confidence per claim (not per dish):
- **High** — Directly inspected, community-proximate, independently corroborated
- **Moderate** — Credible inspected evidence, limited corroboration
- **Low** — Plausible lead, dominated by snippets/aggregators
- **Indeterminate** — Insufficient evidence to choose among competing claims

Do not collapse conflicting traditions into one canonical recipe. Never promote a tier 3-5 lead into a tier 1-2 claim without opening corroborating evidence (see evidence tiers in `references/api-endpoints.md`).

### Phase 8: Deliver

Use the template at `templates/research-report.md`. The report must include:

1. Research question and scope
2. Names, spellings, region, period, and context
3. Best evidence with full citations (author, title, publisher, date, page, URL)
4. Variant comparison (table when 3+ recipes differ)
5. Stable features and contested features
6. Authenticity assessment by dimension
7. Practical transcription / adaptation / reconstruction, if requested — label it as transcription, adaptation, or reconstruction
8. Confidence rating with justification
9. Access gaps and further leads
10. Copyright status for each source

## Guardrails

- **Do not claim full text** unless the returned access metadata or opened item confirms it.
- **Do not bypass paywalls**, borrowing controls, authentication, robots rules, or API terms.
- **Do not disable TLS** certificate or hostname verification.
- **Do not cache Edamam responses** unless the user's current plan and terms explicitly permit the retained fields and duration.
- **Do not reproduce copyrighted recipes at length.** Summarize facts and methods, quote minimally, and link/cite the source. Ingredient lists are facts (not copyrightable), but instructions are creative expression.
- **Flag OCR uncertainty**, missing pages, edition mismatch, translated terminology, and unattributed copying.
- **Keep safety adaptations explicit** when historic instructions conflict with modern food-safety guidance (e.g., historical raw egg, unpasteurized dairy, undercooked pork).
- **Separate descriptive authenticity** ("documented in this community/time") **from prescriptive authenticity** ("the only correct version"). The skill practices descriptive authenticity only.

## Copyright Guidelines

- **Public-domain or openly licensed works:** verify status for the relevant edition, jurisdiction, access location, and intended use before quoting extensively. Cite source and license/status evidence.
- **In-copyright works**: may summarize, compare, cite short portions. Do NOT reproduce full recipe instructions verbatim.
- **Google Books previews**: use for identifying relevant pages and brief excerpts only.
- **Internet Archive / HathiTrust Full View:** full view is an access signal, not by itself a worldwide copyright determination. Check the item's rights statement.
- When in doubt, summarize rather than quote.

## Common Pitfalls

1. **Labeling the first result as authentic.** Always cross-reference multiple sources before assigning confidence.

2. **Ignoring non-English sources.** The most authentic sources are often in the dish's original language. Use alternate names and transliterations to search IA and HathiTrust collections in other languages.

3. **Conflating restaurant and home versions.** Restaurant versions are frequently adapted (larger portions, richer ingredients, dramatic presentation). These are not the same as traditional household recipes.

4. **Missing diaspora variants.** Diaspora communities often preserve older forms of a dish that have since changed in the home country. Search for both.

5. **Over-relying on TheMealDB/Edamam.** These are modern crowd-sourced databases. Use them as a tertiary check, not a primary source.

6. **Forgetting to search by ingredient.** If searching by dish name fails, search Internet Archive full-text by key ingredients + "recipe" or "cookery" to find books that include the dish under a different name.

7. **Ignoring the publication date.** A 2023 "authentic" cookbook is a secondary source. A 1893 cookbook from Kyiv is a primary source. Weight accordingly.

8. **Treating scraped dataset frequency as cultural authority.** Recipe1M+ and RecipeNLG are web-scraped from food blogs. A recipe appearing 500 times in the dataset means 500 blogs copied it, not that it is authentic.

9. **Not checking IA collections.** Search within named collections for higher cookbook density: `collection:cookery`, `collection:americana`, `subject:"cooking"`, `subject:"cookery"`.

10. **Conflating copying with corroboration.** Trace shared wording across sources. If three sources use identical phrasing, they may all derive from one ancestor — that is one source, not three.

## Verification Checklist

- [ ] Searched at least 2 independent source classes
- [ ] Used original-language names and transliterations as search terms
- [ ] Identified at least 2 independent sources before assigning confidence rating
- [ ] Classified each found recipe into a variant category
- [ ] Separated traditional ingredients from modern substitutions
- [ ] Produced comparison table when 3+ recipes differ materially
- [ ] Assessed all 10 authenticity dimensions
- [ ] Assigned confidence rating (High/Moderate/Low/Indeterminate) per claim with justification
- [ ] Full citations with author, title, date, page numbers, URL for every source used
- [ ] Copyright status noted for each source (public domain vs in-copyright)
- [ ] Access gaps stated explicitly (which sources could not be fully inspected)
- [ ] Report follows the template structure
