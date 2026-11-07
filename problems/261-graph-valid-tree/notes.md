## 1. Restate + clarify

n nodes (0 to n − 1), undirected edges. Do they form a valid tree?

Questions to ask:
- No duplicate edges or self-loops. n = 1 with no edges is a tree.

## 2. Tiny example + edge case

n = 5, [[0,1],[0,2],[0,3],[1,4]] → true. n = 5, [[0,1],[1,2],[2,3],[1,3],[1,4]] → false (cycle).
Tricky: n = 4, [[0,1],[1,2],[2,0]] has n − 1 edges but a cycle and an isolated node → false.

## 3. Brute force + complexity

Check "connected" with one DFS and "no cycle" with another: **O(n + E)**; combining them is the same cost.

## 4. Pattern trigger

"Is it a tree?" → **edges == n − 1 + one connectivity/cycle check** (DFS with parent, or Union-Find).

## 5. Plan before coding

- edges.size() != n − 1 → false.
- Build adjacency; DFS from 0 with parent; visited non-parent neighbour → false.
- Any node not visited → false; else true.

## 6. Code

See the approaches above.

## 7. Dry run

Example 1: 4 edges = n − 1 ✓; DFS 0 → 1 → 4 (back to 1 is the parent, skipped) → 2 → 3; all 5 visited → **true**.

## 8. Final complexity + extension

**O(n + E) time and space.**

Related: **LC 323 Number of Connected Components**, **LC 684 Redundant Connection**.

## What confused me / what clicked

- Tree = connected + no cycle; n − 1 edges is necessary but not enough alone.
- Skip the parent when looking for cycles in an undirected graph.
