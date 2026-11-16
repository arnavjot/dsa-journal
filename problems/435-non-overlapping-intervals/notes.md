## 1. Restate + clarify

Return the minimum number of intervals to remove so that the rest don't overlap. Touching intervals like [1,2] and [2,3] are fine.

## 2. Tiny example + edge case

[[1,2],[2,3],[3,4],[1,3]] → **1**. [[1,2],[1,2],[1,2]] → **2**. [[1,2],[2,3]] → **0**.

## 3. Brute force + complexity

Try every subset of intervals to keep: O(2ⁿ · n).

## 4. Pattern trigger

"Fewest removals so the rest don't overlap" = "most intervals kept" → **activity selection: sort by end**.

## 5. Plan before coding

- Sort by end.
- prevEnd = first end, count = 0.
- For the rest: start < prevEnd → count++; else prevEnd = its end.
- Return count.

## 6. Code

See the approaches above.

## 7. Dry run

Your trap, sorted by end: [1,11], [2,12], [11,22], [1,100].

- Keep [1,11].
- [2,12]: 2 < 11 → remove.
- [11,22]: 11 ≥ 11 → keep, prevEnd = 22.
- [1,100]: 1 < 22 → remove.

**2 removed.** Keeping [1,100] first would have cost 3.

## 8. Final complexity + extension

**O(n log n) time, O(1) extra space.** Related: LC 452 Minimum Number of Arrows to Burst Balloons (same greedy), LC 56 Merge Intervals.

## What confused me / what clicked

- Removals = n − kept, and the earliest-end greedy keeps the most.
- Sorting by start can be trapped by a huge interval like [1,100] (my comment's example).
- Use `<` so touching intervals are not counted as overlapping.
