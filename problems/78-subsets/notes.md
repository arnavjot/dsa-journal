## 1. Restate + clarify

Return all subsets (the power set) of an array of **distinct** integers, in any order.

## 2. Tiny example + edge case

`[1,2,3]` → 8 subsets: [], [1], [2], [3], [1,2], [1,3], [2,3], [1,2,3]. `[0]` → [], [0].

## 3. Brute force + complexity

Each number is in or out: 2ⁿ subsets, O(n) to copy each → **O(n·2ⁿ)**. Nothing can do better, since that's the output size.

## 4. Pattern trigger

"Generate all subsets / combinations" → **backtracking** (or a bitmask for subsets).

## 5. Plan before coding

- solve(start): for i from start: push nums[i], solve(i + 1), pop.
- After the loop, save path.

## 6. Code

See the approaches above.

## 7. Dry run

`[1,2]`: solve(0) → push 1 → solve(1) → push 2 → solve(2) saves [1,2] → pop → solve(1) saves [1] → pop 1 → push 2 → solve(2) saves [2] → pop → solve(0) saves [].

## 8. Final complexity + extension

**O(n·2ⁿ) time, O(n) recursion.**

Extensions: **LC 90 Subsets II** (duplicates), **LC 77 Combinations** (fixed size k).

## What confused me / what clicked

- `i + 1` = only later numbers, so no subset appears in two orders.
- Push → recurse → pop is the backtracking pattern.
- Saving after the loop gives the same subsets in a different order than saving first.
