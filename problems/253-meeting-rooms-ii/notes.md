## 1. Restate + clarify

Given meeting times, return the minimum number of conference rooms needed so no two meetings in the same room overlap.

## 2. Tiny example + edge case

[[0,30],[5,10],[15,20]] → **2**. [[7,10],[2,4]] → **1**.

## 3. Brute force + complexity

At every time point count running meetings: O(n · range), or compare all pairs in O(n²).

## 4. Pattern trigger

"Most intervals active at the same time" → **sort by start + min-heap of end times** (or a sweep over sorted starts and ends).

## 5. Plan before coding

- Sort by start.
- For each meeting: if heap.top() ≤ start, pop (reuse that room).
- Push its end; rooms = max(rooms, heap size).

## 6. Code

See the approaches above.

## 7. Dry run

[0,30]: heap {30}. [5,10]: 30 > 5 → new room, {10, 30}. [15,20]: 10 ≤ 15 → reuse, {20, 30}. **2 rooms.**

## 8. Final complexity + extension

**O(n log n) time, O(n) space.** Related: LC 252 Meeting Rooms, LC 1851, LC 2402 Meeting Rooms III.

## What confused me / what clicked

- The heap holds when each busy room frees up.
- Only the top matters: if it's still busy, every room is.
- I didn't paste code for this one; it's the standard heap solution.
