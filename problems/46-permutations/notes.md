## 1. Restate + clarify

Return all permutations of an array of **distinct** integers, any order.

## 2. Tiny example + edge case

`[1,2,3]` → 6 permutations. `[0,1]` → [[0,1],[1,0]]. `[1]` → [[1]].

## 3. Brute force + complexity

There are n! permutations, each of length n → **O(n·n!)** is the minimum.

## 4. Pattern trigger

"All orderings" → **backtracking**: fix one position at a time.

## 5. Plan before coding

- recurPermute(index): index == n → save nums.
- for i from index: swap(index, i), recurPermute(index + 1), swap back.

## 6. Code

See the approaches above.

## 7. Dry run

`[1,2]`: index 0, i 0 → [1,2] → save → swap back; i 1 → swap → [2,1] → save → swap back → [1,2].

## 8. Final complexity + extension

**O(n·n!) time, O(n) recursion.**

Extensions: **LC 47 Permutations II** (duplicates: skip values already placed at this position), building with a `used[]` array instead of swaps.

## What confused me / what clicked

- By reference → must swap back (backtrack).
- By value → each call has its own copy, so no swap back, but more copying.
- index = the position being decided.
