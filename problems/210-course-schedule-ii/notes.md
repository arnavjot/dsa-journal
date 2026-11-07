## 1. Restate + clarify

Same as Course Schedule, but return one valid order (any), or [] if impossible.

## 2. Tiny example + edge case

2, [[1,0]] → [0,1]. 4, [[1,0],[2,0],[3,1],[3,2]] → [0,1,2,3] (or [0,2,1,3]). Cycle → [].

## 3. Brute force + complexity

Try orders until one works: O(n!).

## 4. Pattern trigger

"Order with dependencies" → **topological sort** (Kahn's BFS or DFS post-order).

## 5. Plan before coding

- Build b → a edges and indegrees.
- Queue indegree-0 courses; pop → append to topo; lower dependents; queue new zeros.
- topo.size() == n ? topo : {}.

## 6. Code

See the approaches above.

## 7. Dry run

4 courses: queue {0} → take 0 (1 and 2 drop to 0) → take 1 (3 drops to 1) → take 2 (3 drops to 0) → take 3 → **[0,1,2,3]**.

## 8. Final complexity + extension

**O(V + E) time and space.**

Related: **LC 207**, **LC 269 Alien Dictionary**.

## What confused me / what clicked

- Kahn's pop order *is* the answer.
- DFS version: push after the neighbours, then reverse (pop the stack).
- Fewer than n taken → cycle → [].
