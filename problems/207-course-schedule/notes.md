## 1. Restate + clarify

numCourses courses, pairs [a, b] = take b before a. Can you finish all of them?

## 2. Tiny example + edge case

2, [[1,0]] → true. 2, [[1,0],[0,1]] → false (cycle). No prerequisites → true.

## 3. Brute force + complexity

Try every order: O(n!).

## 4. Pattern trigger

"Dependencies, can we order them?" → **cycle detection in a directed graph** (Kahn's topological sort, or DFS).

## 5. Plan before coding

- Edges b → a, indegree[a]++.
- Queue all indegree-0 courses. Pop, count it, lower its dependents' indegrees, queue any that hit 0.
- Answer: count == numCourses.

## 6. Code

See the approaches above.

## 7. Dry run

4 courses, edges 0→1, 1→2, 2→3, 3→1: indegrees 0,2,1,1. Queue {0} → take 0, indeg[1] = 1 → queue empty. Only 1 taken → **false** (1, 2, 3 form a cycle).

## 8. Final complexity + extension

**O(V + E) time and space.**

Next: **LC 210 Course Schedule II** (return the order).

## What confused me / what clicked

- [a, b]: the edge goes **b → a**.
- A cycle = some courses never reach indegree 0.
- DFS: "on the current path" (dfstrack) is different from "visited".
