## 1. Restate + clarify

A node X is **good** if no node on the path from the root to X has a value greater than X. Count the good nodes.

Questions to ask:
- The root is always good. Values can be negative (−10⁴…10⁴).

## 2. Tiny example + edge case

`[3,1,4,3,null,1,5]` → **4** (3, 3, 4, 5). `[3,3,null,4,2]` → **3**. `[1]` → **1**.
Edge case: equal values count as good: `[2,2,2]` → 3.

## 3. Brute force + complexity

For every node, walk its whole root path and compare: **O(n·h)**.

## 4. Pattern trigger

"A condition about the path from the root" → **DFS that carries information down** (here: the path max).

## 5. Plan before coding

- dfs(node, maxValue): NULL → 0.
- count = (val >= maxValue).
- maxValue = max(maxValue, val); add dfs(left) + dfs(right).
- Start with dfs(root, INT_MIN).

## 6. Code

See the approaches above.

## 7. Dry run

`[3,1,4,3,null,1,5]`

| node | maxValue coming in | good? | passes down |
|---|---|---|---|
| 3 (root) | −∞ | yes | 3 |
| 1 | 3 | no | 3 |
| 3 (under 1) | 3 | yes | 3 |
| 4 | 3 | yes | 4 |
| 1 (under 4) | 4 | no | 4 |
| 5 | 4 | yes | 5 |

Total **4**.

## 8. Final complexity + extension

**O(n) time, O(h) space.**

Same idea, carrying something down: **LC 98 Validate BST** (carry a range), **LC 112 Path Sum** (carry the remaining sum).

## What confused me / what clicked

- One number (the path max) replaces checking the whole path.
- `>=`: equal values are good.
- Information flows **down** (parameters) and counts flow **up** (return values).
