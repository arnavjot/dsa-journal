## 1. Restate + clarify

Return true if the tree is a valid **BST**: every node is strictly greater than everything in its left subtree and strictly smaller than everything in its right subtree.

Questions to ask:
- Duplicates? Not allowed (strict).
- Values can be INT_MIN / INT_MAX? Yes, so bounds need `long`.
- 1 to 10⁴ nodes.

## 2. Tiny example + edge case

`[2,1,3]` → **true**. `[5,1,4,null,null,3,6]` → **false** (4 is in 5's right subtree).

Trap: `[5,4,6,null,null,3,7]` → **false**. Every parent–child pair is fine, but 3 < 5 sits in 5's right subtree.

## 3. Brute force + complexity

For each node, compare it with the max of its left subtree and the min of its right subtree: **O(n²)** on a chain.

## 4. Pattern trigger

"BST property" → **in-order is sorted**, or pass **(low, high) bounds** down.

## 5. Plan before coding

- `inorder(node)`: left, push value, right.
- Check `ans[i] < ans[i + 1]` for every i.

## 6. Code

See the approaches above.

## 7. Dry run

`[5,1,4,null,null,3,6]`

In-order: 1, 5, 3, 4, 6.

| i | ans[i], ans[i+1] | ok? |
|---|---|---|
| 0 | 1, 5 | ✓ |
| 1 | 5, 3 | **5 ≥ 3 → false** |

## 8. Final complexity + extension

**O(n) time, O(n) space** (list) / **O(h)** with bounds.

Extensions: keep only the previous in-order value instead of the whole list (O(h) space); **LC 230 Kth Smallest in a BST** uses the same in-order idea.

## What confused me / what clicked

- Comparing a node only with its children misses grandparent violations.
- In-order of a BST = sorted, so checking neighbours is enough.
- Strict `<`: equal values are invalid.
- `ans.size() - 1` is unsigned; fine here because there's always at least one node.
