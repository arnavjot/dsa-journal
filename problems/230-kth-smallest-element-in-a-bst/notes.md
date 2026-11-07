## 1. Restate + clarify

Given a BST and k, return the **k-th smallest** value (1-indexed).

Questions to ask:
- k is always valid (1 ≤ k ≤ n). Values are unique, 0…10⁴.

## 2. Tiny example + edge case

`[3,1,4,null,2]`, k = 1 → **1**. `[5,3,6,2,4,null,null,1]`, k = 3 → **3**.
Edge case: k = n → the biggest value (the rightmost node).

## 3. Brute force + complexity

In-order into a vector (it's sorted), return `vals[k − 1]`: **O(n)** time and space.

## 4. Pattern trigger

BST + "k-th smallest / sorted order" → **in-order traversal** (left, node, right), counting as you go.

## 5. Plan before coding

- Recurse left first. If it returns a real value (not −1), pass it up.
- Otherwise this node is the next smallest: `k--`; if `k == 0`, return its value.
- Else recurse right and return what it gives.
- NULL → −1 ("not found here").

## 6. Code

See the approaches above.

## 7. Dry run

`[5,3,6,2,4,null,null,1]`, k = 3

| visit | k after | |
|---|---|---|
| 1 | 2 | (deepest left) |
| 2 | 1 | |
| 3 | 0 | **return 3**, passed up through 5 |

Nodes 4, 5, 6 are never counted.

## 8. Final complexity + extension

**O(h + k) time, O(h) space** (call stack).

Follow-up (LeetCode): if the BST is modified often and kthSmallest is called a lot, store the **size of each subtree** in the node; then go left/right by comparing k with the left size: O(h) per query.

## What confused me / what clicked

- In-order of a BST = sorted.
- `int& k` so every call counts on the **same** k.
- −1 as "not found" is safe only because values are never negative.
- `return left;` stops the search early: nothing after the answer is visited.
