## 1. Restate + clarify

Return the number of **nodes** on the longest path from the root down to a leaf.

Questions to ask:
- Counted in nodes, not edges? Yes.
- Empty tree? Depth 0.
- Up to 10⁴ nodes.

## 2. Tiny example + edge case

`[3,9,20,null,null,15,7]` → 3 → 20 → 15 → **3**.

Edge cases: `[]` → 0. `[1,null,2]` → 2. A chain of n nodes → n.

## 3. Brute force + complexity

BFS, counting levels: **O(n) time, O(width) space**. Same work, different order.

## 4. Pattern trigger

"A node's answer comes from its children's answers" → **post-order recursion** (return a value up).

## 5. Plan before coding

- NULL → 0.
- `lh = maxDepth(left)`, `rh = maxDepth(right)`.
- Return `1 + max(lh, rh)`.

## 6. Code

See the approaches above.

## 7. Dry run

`[3,9,20,null,null,15,7]`

| call | lh | rh | returns |
|---|---|---|---|
| maxDepth(9) | 0 | 0 | 1 |
| maxDepth(15) | 0 | 0 | 1 |
| maxDepth(7) | 0 | 0 | 1 |
| maxDepth(20) | 1 | 1 | 2 |
| maxDepth(3) | 1 | 2 | **3** |

## 8. Final complexity + extension

**O(n) time, O(h) space.**

Extensions:
- **LC 111 Minimum Depth**: careful, a node with one NULL child isn't a leaf.
- **LC 543 Diameter** and **LC 110 Balanced** reuse this exact height function.

## What confused me / what clicked

- Answers come back **up** the tree (post-order).
- NULL → 0 makes leaves return 1 with no special case.
- This height function is the template for Diameter and Balanced.
