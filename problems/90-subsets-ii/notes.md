## 1. Restate + clarify

Like Subsets, but nums may contain **duplicates**; the answer must not contain the same subset twice.

## 2. Tiny example + edge case

`[1,2,2]` → [], [1], [1,2], [1,2,2], [2], [2,2]. `[0]` → [], [0].

## 3. Brute force + complexity

Sort, generate all 2ⁿ subsets, dedupe with a set: **O(n·2ⁿ·log)**.

## 4. Pattern trigger

"Subsets with duplicates, no repeated answers" → **sort + backtracking + skip equal values at the same level**.

## 5. Plan before coding

- Sort. dfs(index): save current.
- for i from index: if i > index and nums[i] == nums[i − 1] → skip.
- push, dfs(i + 1), pop.

## 6. Code

See the approaches above.

## 7. Dry run

`[1,2,2]`: save [] → add 1: save [1] → add 2: save [1,2] → add 2: save [1,2,2] → (the second 2 at the [1] level is skipped) → add 2: save [2] → add 2: save [2,2] → the second 2 at the top level is skipped.

## 8. Final complexity + extension

**O(n·2ⁿ) time, O(n) recursion.**

Same skip rule as **LC 40 Combination Sum II**.

## What confused me / what clicked

- Save first: every call is a new subset.
- Skip only repeats **at the same level** (`i > index`).
- Sorting makes equal values adjacent so one comparison finds them.
