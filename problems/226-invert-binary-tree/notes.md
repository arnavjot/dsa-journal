## 1. Restate + clarify

Mirror the tree: every node's left and right subtrees trade places. Return the root.

Questions to ask:
- Empty tree? Return NULL.
- Change the tree in place or build a new one? In place is fine.
- Up to 100 nodes.

## 2. Tiny example + edge case

`[4,2,7,1,3,6,9]` → **`[4,7,2,9,6,3,1]`**.

Edge cases: `[]` → `[]`. `[1]` → `[1]`. A chain `[1,2,null,3]` becomes a chain leaning the other way.

## 3. Brute force + complexity

There's no slower "brute force" really; every node has to be touched once. BFS with a queue is the main alternative: **O(n) time, O(width) space**.

## 4. Pattern trigger

"Same small job at every node" → **recursion (DFS)**. The job here: swap the two children.

## 5. Plan before coding

- `root == NULL` → return NULL.
- Swap `root->left` and `root->right` using `temp`.
- `invertTree(root->left)`, `invertTree(root->right)`.
- Return `root`.

## 6. Code

See the approaches above.

## 7. Dry run

`[4,2,7,1,3,6,9]`

| call | swap | tree after (level order) |
|---|---|---|
| invertTree(4) | 2 ↔ 7 | 4 · 7 2 · 6 9 1 3 |
| invertTree(7) | 6 ↔ 9 | 4 · 7 2 · 9 6 1 3 |
| invertTree(9), (6) | leaves: nothing | same |
| invertTree(2) | 1 ↔ 3 | 4 · 7 2 · 9 6 3 1 |
| invertTree(3), (1) | leaves: nothing | same |

Result **`[4,7,2,9,6,3,1]`**.

## 8. Final complexity + extension

**O(n) time, O(h) space** (call stack; h = height).

Extensions:
- **LC 101 Symmetric Tree**: is the tree equal to its own mirror? Compare left and right subtrees recursively.
- **LC 100 Same Tree**: same recursive shape.

## What confused me / what clicked

- One job per node: swap its children. Recursion handles the rest.
- `temp` is just a normal swap; `swap(root->left, root->right)` does the same.
- Swap before or after the calls: both work, every node gets swapped once.
- Space is the recursion depth, not n (unless the tree is a chain).
