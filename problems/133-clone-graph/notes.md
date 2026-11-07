## 1. Restate + clarify

Return a deep copy of a connected undirected graph, given one node (val = 1). No copy may point to an original node.

Questions to ask:
- Can it be empty (nullptr)? Yes. Cycles are normal (undirected edges go both ways).

## 2. Tiny example + edge case

Square [[2,4],[1,3],[2,4],[1,3]] → same shape, new nodes. [[]] → one node. [] → empty.

## 3. Brute force + complexity

Copying without remembering copies loops forever on the first cycle. A map is required: **O(V + E)**.

## 4. Pattern trigger

"Copy a structure with cycles / shared nodes" → **DFS/BFS + map original → copy** (same idea as LC 138).

## 5. Plan before coding

- nullptr → nullptr.
- In mp → return mp[node].
- copy = new Node(val); mp[node] = copy (before recursing!).
- For each neighbour: copy->neighbors.push_back(cloneGraph(neighbour)).

## 6. Code

See the approaches above.

## 7. Dry run

Triangle: clone(1) makes 1' → clone(2) makes 2' → its neighbour 1 is in mp → 2'→1' → clone(3) makes 3' → 3'→1', 3'→2' → back in 2: 2'→3' → back in 1: 1'→2', 1'→3'.

## 8. Final complexity + extension

**O(V + E) time, O(V) space.**

Same pattern: **LC 138 Copy List with Random Pointer**.

## What confused me / what clicked

- Record the copy in the map **before** visiting neighbours (that's what makes cycles work).
- The map is both "visited" and "where is the copy".
