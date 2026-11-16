## 1. Restate + clarify

An n × n grid has heights 0..n² − 1. At time t you can swim through any cell with height ≤ t (4 directions, instantly). Return the least time to get from (0, 0) to (n − 1, n − 1).

## 2. Tiny example + edge case

[[0,2],[1,3]] → **3** (you need the corner itself). The 5 × 5 spiral → **16**.

## 3. Brute force + complexity

For t = 0, 1, …, BFS over cells ≤ t until the corner is reachable: O(n⁴).

## 4. Pattern trigger

"Minimise the maximum on a path" → **Dijkstra with max instead of +** (or binary search + BFS, or union-find by height).

## 5. Plan before coding

- Heap {grid[0][0], 0, 0}; mark seen.
- Pop {t, r, c}; if it's the corner, return t.
- For each unseen neighbour: mark it and push {max(t, height), r', c'}.

## 6. Code

See the approaches above.

## 7. Dry run

[[0,2],[1,3]]:

- Pop {0, 0, 0}. Push (1,0) with time 1 and (0,1) with time 2.
- Pop {1, 1, 0}. Push (1,1) with time max(1, 3) = 3.
- Pop {2, 0, 1}. Nothing new.
- Pop {3, 1, 1}: it's the corner → **3**.

## 8. Final complexity + extension

**O(n² log n) time, O(n²) space.** Binary search + BFS is O(n² log n) too. Related: LC 1631 Path With Minimum Effort (minimise the largest step), LC 743 Network Delay Time.

## What confused me / what clicked

- A path's cost is its highest cell, and that never drops as the path gets longer, so Dijkstra still works.
- Mark cells when they're pushed; their key can't improve later.
- I didn't paste code for this one; it's mine.
