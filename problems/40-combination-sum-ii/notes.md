## 1. Restate + clarify

Candidates may contain **duplicates**; each element can be used **once**; the answer must not contain the same combination twice.

## 2. Tiny example + edge case

`[10,1,2,7,6,1,5]`, 8 → [[1,1,6],[1,2,5],[1,7],[2,6]]. `[2,5,2,1,2]`, 5 → [[1,2,2],[5]].

## 3. Brute force + complexity

All 2ⁿ subsets, keep the right sums in a set: **O(n·2ⁿ·log)** and lots of repeated work.

## 4. Pattern trigger

"Combinations, each once, input has duplicates" → **sort + backtracking + skip equal values at the same level**.

## 5. Plan before coding

- Sort.
- dfs(index, target): target == 0 → save.
- for i from index: skip if i > index and equal to i − 1; break if too big; push, dfs(i + 1, target − c), pop.

## 6. Code

See the approaches above.

## 7. Dry run

Sorted `[1,1,2,5,6,7,10]`, 8: level 0 tries 1 (→ [1,1,6], [1,2,5], [1,7]), **skips the second 1**, tries 2 (→ [2,6]), 5 (nothing), 6, 7, then breaks at 10.

## 8. Final complexity + extension

O(2ⁿ) worst case; far less with the skip and the break. Recursion O(n).

Same skip rule as **LC 90 Subsets II**.

## What confused me / what clicked

- `i > index`, not `i > 0`: one copy per level is fine.
- Sorted → `break` instead of `continue`.
- `i + 1` = no reuse.
