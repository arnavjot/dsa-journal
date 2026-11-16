## 1. Restate + clarify

Connect all points (any pair can be joined, cost = |x1 − x2| + |y1 − y2|) with the minimum total cost. Up to 1000 points.

## 2. Tiny example + edge case

[[0,0],[2,2],[3,10],[5,2],[7,0]] → **20**. [[3,12],[−2,5],[−4,1]] → **18**. One point → **0**.

## 3. Brute force + complexity

Try every spanning tree: exponentially many.

## 4. Pattern trigger

"Connect all nodes at minimum total cost" → **minimum spanning tree**; dense graph → **Prim's with an array**.

## 5. Plan before coding

- minDist all ∞, minDist[0] = 0.
- n times: u = closest outside point; total += minDist[u]; mark it.
- For every outside v: minDist[v] = min(minDist[v], dist(u, v)).

## 6. Code

See the approaches above.

## 7. Dry run

Example 2: points (3,12), (−2,5), (−4,1).

- Add p0: minDist p1 = 12, p2 = 18.
- Add p1 (12): p2 = min(18, 6) = 6.
- Add p2 (6).

Total **18**.

## 8. Final complexity + extension

**O(n²) time, O(n) space.** Kruskal's with union-find would be O(n² log n), because all n² edges have to be sorted. Related: LC 1135 Connecting Cities With Minimum Cost, LC 1489 Critical Edges in an MST.

## What confused me / what clicked

- It's an MST on a complete graph, so the dense version of Prim's fits best.
- minDist holds the cheapest edge into the tree, not the distance from the start.
- I didn't paste code for this one; it's mine.
