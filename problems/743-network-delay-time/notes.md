## 1. Restate + clarify

A signal starts at node k and travels along directed edges (u, v, w) taking time w. Return the time until all n nodes have received it, or −1 if some never do.

## 2. Tiny example + edge case

[[2,1,1],[2,3,1],[3,4,1]], n = 4, k = 2 → **2**. [[1,2,1]], n = 2, k = 2 → **−1**.

## 3. Brute force + complexity

Bellman-Ford: O(V × E). Floyd-Warshall: O(V³).

## 4. Pattern trigger

"Shortest path from one source, weights ≥ 0" → **Dijkstra**.

## 5. Plan before coding

- adj[u] = {v, w}.
- dist all ∞, dist[k] = 0, heap {0, k}.
- Pop {d, u}; skip if d > dist[u]; for each edge, if d + w < dist[v], update it and push.
- Answer = max dist, or −1 if any is ∞.

## 6. Code

See the approaches above.

## 7. Dry run

1→2 (9), 1→3 (1), 3→2 (2), 2→4 (1), k = 1:

- Pop 1: dist2 = 9, dist3 = 1.
- Pop 3: dist2 = min(9, 3) = 3.
- Pop 2 (3): dist4 = 4.
- Pop 4.
- Pop {9, 2}: stale, skip.

The largest time is **4**.

## 8. Final complexity + extension

**O(E log V) time, O(V + E) space.** Related: LC 787 Cheapest Flights Within K Stops (limited stops → Bellman-Ford), LC 1514 Path with Maximum Probability, LC 778 Swim in Rising Water.

## What confused me / what clicked

- Dijkstra needs non-negative weights.
- Stale heap entries are cheaper to skip than to delete.
- The answer is the slowest node, not the sum.
- I didn't paste code for this one; it's mine.
