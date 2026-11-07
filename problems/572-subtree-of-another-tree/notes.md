## 1. Restate + clarify

Return true if some node of `root` starts a subtree that is **exactly** `subRoot`: same shape and values, including everything below it.

Questions to ask:
- A subtree is a node plus **all** its descendants? Yes.
- Sizes? root up to 2000 nodes, subRoot up to 1000.

## 2. Tiny example + edge case

`root = [3,4,5,1,2]`, `subRoot = [4,1,2]` → **true** (the 4 on the left).
Add a 0 under the 2: `[3,4,5,1,2,null,null,null,null,0]` → **false**, because root's 4 now has an extra node.

Edge cases: `[1,1]` vs `[1]` → true (the leaf 1). `[1,2,3,4]` vs `[2]` → false (root's 2 has a child).

## 3. Brute force + complexity

Run isSameTree from every node of root: **O(m × n) time**. That *is* the standard solution; the faster one serializes both trees.

## 4. Pattern trigger

"Is tree B inside tree A?" → reuse **isSameTree (LC 100)** at every node of A.

## 5. Plan before coding

- `isSameTree(p, q)`: both NULL → true; one NULL → false; values differ → false; else left && right.
- `isSubtree(root, sub)`: sub NULL → true; root NULL → false; `isSameTree(root, sub)` → true; else `isSubtree(left) || isSubtree(right)`.

## 6. Code

See the approaches above.

## 7. Dry run

`root = [3,1,4,1,null,1,2]`, `subRoot = [4,1,2]`

| start at | isSameTree | why |
|---|---|---|
| 3 | false | 3 ≠ 4 |
| 1 (left) | false | 1 ≠ 4 |
| 1 (leaf) | false | 1 ≠ 4 |
| 4 | **true** | 4 = 4, 1 = 1, 2 = 2, all NULLs line up |

Return **true**.

## 8. Final complexity + extension

**O(m × n) time, O(h) space.** Serialize + KMP: **O(m + n)**.

Extension: **LC 1367 Linked List in Binary Tree**: same "try every start, then match downward" shape.

## What confused me / what clicked

- It's two recursions: one walks root looking for a start, the other (isSameTree) checks a full match.
- Matching must go **all the way down**: an extra child in root breaks it.
- `||` stops as soon as one side finds it; `&&` in isSameTree stops at the first difference.
