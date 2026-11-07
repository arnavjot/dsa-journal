## 1. Restate + clarify

The **diameter** is the number of **edges** on the longest path between any two nodes. The path doesn't have to go through the root.

Questions to ask:
- Edges, not nodes? Yes.
- One node → 0.
- Up to 10⁴ nodes.

## 2. Tiny example + edge case

`[1,2,3,4,5]` → path 4 → 2 → 1 → 3 (or 5 → 2 → 1 → 3) → **3**.

Edge cases: `[1,2]` → 1. A tree whose longest path bends **below** the root.

## 3. Brute force + complexity

At every node compute both heights from scratch and check lh + rh, then recurse. **O(n²) time.**

## 4. Pattern trigger

"Longest path anywhere in a tree" → every path has a highest node where it bends → **post-order heights + a global best** (same shape as Max Depth).

## 5. Plan before coding

- `height(node, diameter)`: NULL → 0.
- `lh`, `rh` from the children.
- `diameter = max(diameter, lh + rh)`.
- Return `1 + max(lh, rh)`.

## 6. Code

See the approaches above.

## 7. Dry run

`[1,2,3,4,5]`

| call | lh | rh | lh + rh | diameter | returns |
|---|---|---|---|---|---|
| height(4) | 0 | 0 | 0 | 0 | 1 |
| height(5) | 0 | 0 | 0 | 0 | 1 |
| height(2) | 1 | 1 | 2 | 2 | 2 |
| height(3) | 0 | 0 | 0 | 2 | 1 |
| height(1) | 2 | 1 | **3** | **3** | 3 |

Return **3**.

## 8. Final complexity + extension

**O(n) time, O(h) space.**

Extension: **LC 124 Binary Tree Maximum Path Sum**: same "return one side, record both sides" pattern, with sums instead of heights.

## What confused me / what clicked

- Heights count nodes below a node, which is the number of edges going down from it, so the path through a node is exactly `lh + rh`.
- The function **returns** one thing (height) and **records** another (diameter) by reference.
- The best path can bend anywhere, not just at the root.
