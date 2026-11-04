## 1. Restate + clarify

A path is any sequence of connected nodes (each used once); it doesn't have to pass through the root. Return the maximum sum of any path.

Questions to ask:
- At least one node. Values can be negative (−1000…1000).

## 2. Tiny example + edge case

`[1,2,3]` → **6** (2 → 1 → 3). `[-10,9,20,null,null,15,7]` → **42** (15 → 20 → 7).
Edge case: all negative `[-3,-2,-1]` → **−1** (a single node).

## 3. Brute force + complexity

Try every pair of nodes as path ends and add up the path between them: **O(n²)** or worse.

## 4. Pattern trigger

"Best path in a tree" → **post-order DFS that returns a one-side value and records a two-side answer** (same shape as LC 543 Diameter).

## 5. Plan before coding

- helper(node): NULL → 0.
- left = max(helper(left), 0), right = max(helper(right), 0).
- maxi = max(maxi, val + left + right) (path bending here).
- return val + max(left, right) (path continuing up one side).

## 6. Code

See the approaches above.

## 7. Dry run

`[-10,9,20,null,null,15,7]`

| node | left | right | path here | maxi | returns |
|---|---|---|---|---|---|
| 9 | 0 | 0 | 9 | 9 | 9 |
| 15 | 0 | 0 | 15 | 15 | 15 |
| 7 | 0 | 0 | 7 | 15 | 7 |
| 20 | 15 | 7 | 42 | **42** | 35 |
| −10 | 9 | 35 | 34 | 42 | 25 |

## 8. Final complexity + extension

**O(n) time, O(h) space.**

Same pattern: **LC 543 Diameter** (count edges instead of sums), **LC 687 Longest Univalue Path**.

## What confused me / what clicked

- Return **one side** (the parent can only continue one way); record **both sides** in maxi.
- Clip negative gains to 0: skipping a branch is allowed.
- maxi starts at INT_MIN because the answer can be negative.
