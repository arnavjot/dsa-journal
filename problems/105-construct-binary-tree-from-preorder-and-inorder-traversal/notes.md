## 1. Restate + clarify

Given the preorder and inorder traversals of a binary tree with **unique** values, rebuild the tree.

Questions to ask:
- Values are unique (needed to find positions). Both arrays describe the same tree.

## 2. Tiny example + edge case

pre `[3,9,20,15,7]`, in `[9,3,15,20,7]` → root 3, left 9, right 20 (children 15, 7).
Edge case: one node `[-1]`; a chain (all left or all right).

## 3. Brute force + complexity

Same recursion, but scan inorder to find each root: **O(n²)** for a chain.

## 4. Pattern trigger

"Rebuild a tree from traversals" → **preorder gives the root, inorder splits left/right**, plus a **value → index map**.

## 5. Plan before coding

- Map each inorder value to its index.
- `solve(start, end)`: empty range → NULL. root = preorder[preIndex++]; pos = map[root].
- root->left = solve(start, pos − 1); root->right = solve(pos + 1, end).

## 6. Code

See the approaches above.

## 7. Dry run

| call range | root (preIndex) | pos | left range | right range |
|---|---|---|---|---|
| 0..4 | 3 (0) | 1 | 0..0 | 2..4 |
| 0..0 | 9 (1) | 0 | empty | empty |
| 2..4 | 20 (2) | 3 | 2..2 | 4..4 |
| 2..2 | 15 (3) | 2 | empty | empty |
| 4..4 | 7 (4) | 4 | empty | empty |

## 8. Final complexity + extension

**O(n) time, O(n) space** (map + O(h) recursion).

Extensions: **LC 106** (postorder + inorder: take roots from the **end**, build **right** first), **LC 889** (preorder + postorder).

## What confused me / what clicked

- preIndex is shared (`int&`): every call takes the next preorder value.
- Left before right because preorder is root → left → right.
- The `preIndex >= preorder.size()` check is just a safety net; the empty range is what really stops it.
