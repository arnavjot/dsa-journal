## 1. Restate + clarify

A tree is **height-balanced** if at **every** node the left and right subtree heights differ by at most 1.

Questions to ask:
- Every node, not just the root? Yes.
- Empty tree → true.
- Up to 5000 nodes.

## 2. Tiny example + edge case

`[3,9,20,null,null,15,7]` → **true**.
`[1,2,2,3,3,null,null,4,4]` → **false** (at the root: left height 3, right height 1).

Edge cases: `[]` → true. A chain of 3 → false.

## 3. Brute force + complexity

Top-down: at each node compute both heights from scratch, check, recurse. **O(n²) time** on a chain.

## 4. Pattern trigger

"A property that depends on subtree heights at every node" → **post-order**: compute heights bottom-up and check as you return.

## 5. Plan before coding

- `maxDepth(node, isBalanced)`: NULL → 0.
- `left`, `right` from the children.
- `abs(right - left) > 1` → `isBalanced = false`.
- Return `1 + max(left, right)`.

## 6. Code

See the approaches above.

## 7. Dry run

`[1,2,2,3,3,null,null,4,4]`

| call | left | right | diff | returns |
|---|---|---|---|---|
| node 4, 4 | 0 | 0 | 0 | 1 |
| node 3 (with 4, 4) | 1 | 1 | 0 | 2 |
| node 3 (leaf) | 0 | 0 | 0 | 1 |
| node 2 (left) | 2 | 1 | 1 | 3 |
| node 2 (right leaf) | 0 | 0 | 0 | 1 |
| node 1 | 3 | 1 | **2 > 1** | 4 → **false** |

## 8. Final complexity + extension

**O(n) time, O(h) space.**

Extension: return −1 as soon as a subtree is unbalanced and pass it up, to stop early.

## What confused me / what clicked

- "Balanced" is checked at **every** node, not just the root.
- Same height function as Max Depth with one extra line.
- Top-down recomputes heights → O(n²); bottom-up reuses them → O(n).
