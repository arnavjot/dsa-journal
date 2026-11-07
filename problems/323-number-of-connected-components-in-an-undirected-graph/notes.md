## 1. Restate + clarify

n nodes (0 to n − 1) and undirected edges. Return how many connected components there are.

Questions to ask:
- Isolated nodes count as their own component. No duplicate edges (LeetCode), but the code handles them.

## 2. Tiny example + edge case

n = 5, [[0,1],[1,2],[3,4]] → **2**. n = 5, a chain → 1. No edges → n.

## 3. Brute force + complexity

DFS/BFS from each unvisited node: **O(n + E)**, already optimal. Union-Find is the other standard way.

## 4. Pattern trigger

"How many groups once pairs are joined?" → **Union-Find** (or DFS flood like Number of Islands).

## 5. Plan before coding

- parent[i] = i; components = n.
- For each edge: pu = find(u), pv = find(v); if different → parent[pu] = pv, components--.
- Return components.

## 6. Code

See the approaches above.

## 7. Dry run

n = 6, edges 0-1, 1-2, 2-0, 4-5: 6 → 0-1 merges (5) → 1-2 merges (4) → 2-0 same root (4) → 4-5 merges (**3**): {0,1,2}, {3}, {4,5}.

## 8. Final complexity + extension

**O(n + E · α(n)) time, O(n) space.**

Related: **LC 684 Redundant Connection**, **LC 261 Graph Valid Tree** (exactly 1 component and n − 1 edges), **LC 200 Number of Islands**.

## What confused me / what clicked

- Count down from n: each real merge removes one component.
- Same root = already connected = no change.
