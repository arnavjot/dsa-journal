## 1. Restate + clarify

Merge all overlapping intervals and return the non-overlapping result. Intervals that touch ([1,4] and [4,5]) count as overlapping.

## 2. Tiny example + edge case

[[1,3],[2,6],[8,10],[15,18]] → **[[1,6],[8,10],[15,18]]**. [[1,4],[4,5]] → **[[1,5]]**. [[1,10],[2,3]] → **[[1,10]]**.

## 3. Brute force + complexity

Merge any overlapping pair and repeat until nothing changes: O(n²) or worse.

## 4. Pattern trigger

"Overlapping intervals" → **sort by start**, then one sweep.

## 5. Plan before coding

- Sort.
- For each interval: if ans is empty or it starts after ans.back() ends → push it.
- Else ans.back()[1] = max(ans.back()[1], its end).

## 6. Code

See the approaches above.

## 7. Dry run

[1,3] push → [2,6] overlaps (2 ≤ 3), end 6 → [8,10] push → [15,18] push → **[[1,6],[8,10],[15,18]]**.

## 8. Final complexity + extension

**O(n log n) time, O(n) space** for the answer (plus the sort's stack). Related: LC 57 Insert Interval, LC 435 Non-overlapping Intervals, LC 252/253 Meeting Rooms.

## What confused me / what clicked

- After sorting, only the last merged interval can overlap the current one.
- `>` (not `>=`) is what makes touching intervals merge.
- max on the end handles one interval sitting inside another.
