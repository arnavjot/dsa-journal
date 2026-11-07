## 1. Restate + clarify

A tree with n nodes got one extra edge. Return an edge that can be removed to make it a tree again; if several work, return the one that appears last in the input.

## 2. Tiny example + edge case

[[1,2],[1,3],[2,3]] → [2,3]. [[1,2],[2,3],[3,4],[1,4],[1,5]] → [1,4].

## 3. Brute force + complexity

Before adding each edge, DFS to see whether its ends are already connected: **O(n²)**.

## 4. Pattern trigger

"Edges arrive one at a time; are these two nodes already connected?" → **Union-Find (DSU)**.

## 5. Plan before coding

- parent[i] = i.
- For each edge (u, v): pu = find(u), pv = find(v). Equal → return the edge. Else parent[pu] = pv.
- find with path compression.

## 6. Code

See the approaches above.

## 7. Dry run

[[1,2],[1,3],[2,3]]: 1-2 merges {1,2} → 1-3 merges {1,2,3} → 2-3: find(2) = find(3) → **[2,3]**.

## 8. Final complexity + extension

**O(n · α(n)) ≈ O(n) time, O(n) space.**

Add **union by rank/size** to keep trees shallow. Related: **LC 323 Number of Connected Components**, **LC 685 Redundant Connection II** (directed).

## What confused me / what clicked

- Same root before the union = already connected = this edge makes the cycle.
- Path compression: `parent[x] = find(parent[x])`.
- Processing in order automatically returns the last cycle edge.
