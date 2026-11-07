## 1. Restate + clarify

Return true if the two trees have the **same shape** and the **same value** at every position.

Questions to ask:
- Both empty? Same → true.
- Up to 100 nodes each.

## 2. Tiny example + edge case

`[1,2,3]` vs `[1,2,3]` → **true**.
`[1,2]` vs `[1,null,2]` → **false** (shape).
`[1,2,1]` vs `[1,1,2]` → **false** (values).

## 3. Brute force + complexity

Serialize both trees with null markers and compare the strings: **O(n) time, O(n) space**. Works, but recursion is simpler.

## 4. Pattern trigger

"Compare two trees position by position" → **recursion on pairs** (p, q).

## 5. Plan before coding

- Both NULL → true.
- One NULL → false.
- Values differ → false.
- Else → `same(left, left) && same(right, right)`.

## 6. Code

See the approaches above.

## 7. Dry run

`[1,2,1]` vs `[1,1,2]`

| pair | check | result |
|---|---|---|
| (1, 1) | equal → recurse | … |
| (2, 1) left | 2 ≠ 1 | **false** |
| right pair | skipped by `&&` | — |

Return **false**.

## 8. Final complexity + extension

**O(n) time, O(h) space.**

Extensions:
- **LC 572 Subtree of Another Tree**: run isSameTree from every node of the big tree.
- **LC 101 Symmetric Tree**: compare left with right, mirrored.

## What confused me / what clicked

- Order of checks: both NULL → one NULL → values.
- Same values isn't enough, **shape** must match too.
- `&&` short-circuits: one difference ends the search.
