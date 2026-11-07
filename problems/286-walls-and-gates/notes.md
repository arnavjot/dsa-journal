## 1. Restate + clarify

Grid: -1 wall, 0 gate, INF (2147483647) empty room. Fill each empty room with the distance to its nearest gate; unreachable rooms stay INF. Modify in place.

## 2. Tiny example + edge case

Example 1 → [[3,-1,0,1],[2,2,1,-1],[1,-1,2,-1],[0,-1,3,4]]. A room walled off from every gate stays INF.

## 3. Brute force + complexity

BFS from every empty room to its nearest gate: **O((m·n)²)**.

## 4. Pattern trigger

"Distance to the nearest of several sources" → **multi-source BFS** (same as Rotting Oranges, LC 994).

## 5. Plan before coding

- Queue every gate.
- Pop (r, c); for each neighbour that is INF: rooms[nr][nc] = rooms[r][c] + 1, queue it.
- Walls (-1), gates (0) and already-filled rooms are skipped because they aren't INF.

## 6. Code

See the approaches above.

## 7. Dry run

Row [0, INF, INF, INF, INF, 0]: both gates start → fill 1 and 1 → then 2 and 2 → **[0,1,2,2,1,0]**.

## 8. Final complexity + extension

**O(m·n) time and space.**

Same pattern: **LC 994 Rotting Oranges**, **LC 542 01 Matrix**.

## Why BFS instead of DFS

- **BFS** processes rooms in order of distance from the gates. The first value written into a room is already the smallest, so it never changes, and every room is handled once: O(m·n).
- **Plain DFS** (fill once, never revisit) can reach a room along a long winding path first and keep that too-big distance → **wrong answer**.
- **DFS that revisits** whenever a shorter distance arrives (added above as an approach) gives the right answer, but rooms can be redone many times: up to O((m·n)²).
- Rule of thumb: **shortest distance in an unweighted grid → BFS**; DFS is for "is it reachable?" or exploring/counting.
