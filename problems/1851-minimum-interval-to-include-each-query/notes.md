## 1. Restate + clarify

For each query q, find the size (right − left + 1) of the smallest interval with left ≤ q ≤ right, or −1 if none. Up to 10⁵ intervals and queries.

## 2. Tiny example + edge case

Intervals [1,4],[2,4],[3,6],[4,4], queries [2,3,4,5] → **[3,3,1,4]**. A query no interval covers → **−1**.

## 3. Brute force + complexity

For each query scan every interval: O(n · q), too slow at 10⁵ × 10⁵.

## 4. Pattern trigger

"Many queries over intervals, answer order doesn't matter while computing" → **offline: sort queries + sweep + heap**.

## 5. Plan before coding

- Sort intervals by left; sort query indexes by value.
- For each query: push (size, right) of every interval with left ≤ q.
- Pop while top.right < q.
- ans[index] = top.size or −1.

## 6. Code

See the approaches above.

## 7. Dry run

Query 2: push [1,4] (4) and [2,4] (3). Top (3, 4) → **3**.

Query 3: push [3,6] (4). Top (3, 4) → **3**.

Query 4: push [4,4] (1). Top (1, 4) → **1**.

Query 5: pop (1, 4) and (3, 4), which have ended. The next top is (4, 4), also ended → pop. Then (4, 6) → **4**.

## 8. Final complexity + extension

**O(n log n + q log q) time, O(n + q) space.** Related: LC 253 Meeting Rooms II (heap of ends), LC 2251 Number of Flowers in Full Bloom (offline sweep).

## What confused me / what clicked

- Answering in sorted order means intervals only enter and leave once.
- Pops are lazy: only the top must still cover q.
- Keep each query's original index to put the answer back in place.
- I didn't paste code for this one; it's the standard solution.
