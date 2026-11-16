## 1. Restate + clarify

Insert newInterval into a sorted, non-overlapping list of intervals, merging where needed, and keep the result sorted and non-overlapping.

## 2. Tiny example + edge case

[[1,3],[6,9]] + [2,5] → **[[1,5],[6,9]]**. [[1,2],[3,5],[6,7],[8,10],[12,16]] + [4,8] → **[[1,2],[3,10],[12,16]]**. Empty list + [5,7] → **[[5,7]]**.

## 3. Brute force + complexity

Add it, sort, then merge: O(n log n).

## 4. Pattern trigger

"Already sorted intervals, insert one" → **three phases in one pass**.

## 5. Plan before coding

- Copy while intervals[i][1] < new[0].
- Merge while intervals[i][0] ≤ new[1]: new = [min starts, max ends].
- Push new; copy the rest.

## 6. Code

See the approaches above.

## 7. Dry run

Example 2: [1,2] copy (2 < 4). [3,5], [6,7], [8,10] merge → [3,10] (8 ≤ 8). Push [3,10]. Copy [12,16]. **[[1,2],[3,10],[12,16]]**.

## 8. Final complexity + extension

**O(n) time, O(n) space.** Binary search can find the two boundaries in O(log n), but building the output is still O(n). Related: LC 56 Merge Intervals.

## What confused me / what clicked

- Three runs: before, overlapping, after.
- The second condition works because phase 1 already removed everything that ends before newInterval starts.
- newInterval is pushed once, after the overlap phase, even if nothing overlapped.
