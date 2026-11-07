## 1. Restate + clarify

In a **BST**, find the lowest node that has both `p` and `q` in its subtree (a node is in its own subtree).

Questions to ask:
- BST guaranteed? Yes.
- p and q exist and are different? Yes.
- Up to 10⁵ nodes.

## 2. Tiny example + edge case

`[6,2,8,0,4,7,9,null,null,3,5]`, p = 2, q = 8 → **6** (they split at the root).
p = 2, q = 4 → **2** (p is an ancestor of q).

Edge case: `[2,1]`, p = 2, q = 1 → 2.

## 3. Brute force + complexity

Ignore the BST order: search both subtrees, pass found nodes up (the plain binary tree method). **O(n) time.**

## 4. Pattern trigger

"BST" + "find a node by values" → **walk one path using comparisons**.

## 5. Plan before coding

- Both values < root → go left.
- Both values > root → go right.
- Otherwise (split, or root equals one of them) → return root.

## 6. Code

See the approaches above.

## 7. Dry run

p = 3, q = 5

| node | compare | move |
|---|---|---|
| 6 | 3, 5 < 6 | left |
| 2 | 3, 5 > 2 | right |
| 4 | 3 < 4 < 5 | **split → return 4** |

## 8. Final complexity + extension

**O(h) time, O(h) space** (O(1) as a loop).

Extension: **LC 236** (plain binary tree): the second approach, which searches both sides.

## What confused me / what clicked

- The BST order tells you which side **both** nodes are on, so you never search the other side.
- "Split" (one smaller, one bigger) means this node is the LCA.
- If root equals p or q, it's the answer (a node is its own ancestor).
