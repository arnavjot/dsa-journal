## 1. Restate + clarify

Design `serialize(root) → string` and `deserialize(string) → tree` so that deserialize(serialize(t)) gives back the same tree. Any format is allowed.

Questions to ask:
- Values can be negative or multi-digit, so use a separator (comma). Up to 10⁴ nodes.

## 2. Tiny example + edge case

`[1,2,3,null,null,4,5]` → `"1,2,#,#,3,4,#,#,5,#,#,"`.
Edge case: empty tree → `"#,"`.

## 3. Brute force + complexity

Write both preorder and inorder and rebuild with LC 105: works (if values are unique), but twice the data and needs unique values.

## 4. Pattern trigger

"Tree ↔ string" → **preorder DFS with a NULL marker**; read it back with the same recursion and a queue of tokens.

## 5. Plan before coding

- serialize(node): NULL → "#,"; else val + "," then left, then right.
- deserialize: split on commas into a queue.
- helper: pop; "#" → NULL; else make a node, node->left = helper(), node->right = helper().

## 6. Code

See the approaches above.

## 7. Dry run

`[1,null,2]` → serialize: `1,` then left `#,` then right `2,#,#,` → **"1,#,2,#,#,"**.

Deserialize: pop 1 → node; left: pop # → NULL; right: pop 2 → node, its left # and right # → NULL. Same tree.

## 8. Final complexity + extension

**O(n) time, O(n) space.**

Alternative: **level-order (BFS)** with null markers, like LeetCode's own format. Related: **LC 449** (BST: no markers needed, since the BST order fixes the shape).

## What confused me / what clicked

- The `#` markers make preorder alone enough: the shape is written down.
- Deserialize must read in **exactly** the order serialize wrote.
- Separators matter: "-12" is one token, not three.
