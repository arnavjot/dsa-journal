## 1. Restate + clarify

Each minute, every rotten orange rots its fresh 4-neighbours. Return the minutes until no fresh orange is left, or −1 if that never happens.

## 2. Tiny example + edge case

[[2,1,1],[1,1,0],[0,1,1]] → **4**. [[2,1,1],[0,1,1],[1,0,1]] → **−1**. [[0,2]] → 0.

## 3. Brute force + complexity

Simulate minute by minute, rescanning the grid each time: **O((n·m)²)** worst case.

## 4. Pattern trigger

"Spread from many sources at once, earliest time" → **multi-source BFS**.

## 5. Plan before coding

- Queue every rotten orange with time 0.
- Pop (cell, t): each fresh neighbour → rotten, push with t + 1, minTime = max(minTime, t + 1).
- Any fresh left → −1, else minTime.

## 6. Code

See the approaches above.

## 7. Dry run

Example 1: t0 (0,0) → t1 (0,1),(1,0) → t2 (0,2),(1,1) → t3 (2,1) → t4 (2,2) → **4**.

## 8. Final complexity + extension

**O(n·m) time and space.**

Related: **LC 286 Walls and Gates**, **LC 542 01 Matrix**.

## Does DFS work here? (my question)

- **Plain DFS (mark a cell once, never revisit): no.** It may reach an orange first along a long path and record a time that is too big; a shorter path found later is ignored.
- **DFS that revisits a cell whenever a shorter time arrives: yes, it's correct** (added above as an approach and tested on 5,000 random grids). But a cell can be re-explored many times, so it can cost O((n·m)²).
- **BFS is the natural fit**: rot spreads in parallel, minute by minute, which is exactly BFS layer by layer. The first time BFS reaches a cell is already the earliest time, so nothing is ever revisited.
