## 1. Restate + clarify

Standing to the right of the tree, return the values you can see, top to bottom: the **rightmost node at each depth**.

Questions to ask:
- Empty tree → `[]`.
- Up to 100 nodes.

## 2. Tiny example + edge case

`[1,2,3,null,5,null,4]` → **`[1,3,4]`**.
`[1,2,3,4]` → **`[1,3,4]`**: the 4 is on the **left** side but nothing on the right is that deep.

## 3. Brute force + complexity

Level order, keep the last node of each level: **O(n) time, O(width) space**.

## 4. Pattern trigger

"One node per depth" → **DFS with depth**, or BFS by levels.

## 5. Plan before coding

- `solve(node, level)`: NULL → return.
- If `level == rightView.size()` → push `node->val`.
- Recurse right, then left, with `level + 1`.

## 6. Code

See the approaches above.

## 7. Dry run

`[1,2,3,null,5,null,4]`

| call | level | size before | action |
|---|---|---|---|
| solve(1) | 0 | 0 | push 1 |
| solve(3) | 1 | 1 | push 3 |
| solve(4) | 2 | 2 | push 4 |
| solve(2) | 1 | 3 | skip |
| solve(5) | 2 | 3 | skip |

Return **`[1,3,4]`**.

## 8. Final complexity + extension

**O(n) time, O(h) space.**

Extensions: left view (left first), and LC 102 / 103 style level problems.

## What confused me / what clicked

- `rightView.size()` = how many depths are already covered.
- Right-first order makes the **first** node at a depth the rightmost one.
- The visible node can come from a left branch.
