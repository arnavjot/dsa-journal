# DSA Journal

My NeetCode 150 journal: every problem written up with the 8-step interview script, brute force → optimal code, step-by-step visualizers, and pattern-wise timed revision.

**Live site:** `https://<your-username>.github.io/dsa-journal/`

## What's on the site

- **Patterns** (home): all 18 NeetCode categories with progress, a "spot it" hint for each, and what's due for revision.
- **Problem pages:** key idea, every approach with time/space (tap **i** for why), code, a visualizer where there is one, the 8 steps, and a quick quiz.
- **Revise:** pick a pattern, get its most overdue problem, solve it against a timer (Easy 15 / Medium 25 / Hard 40 min), rate yourself. The gap grows 1 → 3 → 7 → 14 → 30 → 60 days. At most 4 problems are scheduled per day (`DAILY_CAP` in `assets/app.js`); dates shift a little to the quietest nearby day and patterns are mixed, so reviews never pile up on one day.
- **History:** every timed attempt, average time per pattern.
- **i button** (top right): the 8-step script, the never-stuck protocol, and a constraints → complexity table.

## One-time setup

1. Create a new **empty** repo on GitHub called `dsa-journal` (no README).
2. In this folder:
   ```bash
   git remote add origin https://github.com/<your-username>/dsa-journal.git
   git push -u origin main
   ```
3. On GitHub: **Settings → Pages → Build and deployment → Source: GitHub Actions**.
4. Open the **Actions** tab, wait for "Deploy site" to go green, and your site is live.

## Adding a problem

1. Copy `problems/_template` to `problems/<id>-<slug>`, e.g. `problems/1-two-sum`.
   The slug is the LeetCode URL name.
2. Fill in:
   - `meta.json`: id, title, key idea, one entry per approach (file, time, space, why), quiz.
   - `brute.cpp`, `optimal.cpp` (add more files for more approaches, and list them in `meta.json`).
   - `notes.md`: the 8 steps + "what confused me".
3. If it's a new solve, set `"solved": true` for it in `data/catalog.json`.
4. Push. The site rebuilds itself.

To add a visualizer, put an HTML file in `viz/` and set `"viz": "viz/your-file.html"` on that approach.

## Revisions across devices

Revisions save in your browser. To sync: **History → Copy**, paste into `data/revisions.json`, push. On another device, the site starts from that file.

## Run locally

```bash
npx serve .
```

(Double-clicking `index.html` won't work, because the page loads its data files with `fetch`.)
