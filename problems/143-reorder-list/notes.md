## 1. Restate + clarify

Reorder L0 → L1 → … → Ln into L0 → Ln → L1 → Ln−1 → …, in place (relink nodes, don't change values).

Questions to ask:
- 0, 1 or 2 nodes → nothing changes. Must use the existing nodes.

## 2. Tiny example + edge case

`[1,2,3,4]` → `[1,4,2,3]`. `[1,2,3,4,5]` → `[1,5,2,4,3]`.

## 3. Brute force + complexity

Put all nodes in an array, link front/back with two indices: **O(n)** time, **O(n)** space.

## 4. Pattern trigger

"Alternate front and back of a list in O(1) space" → **middle (fast/slow) + reverse second half + merge**.

## 5. Plan before coding

- `mid = middleNode(head)` (the second middle for even length).
- `hs = reverseList(mid)`, `hf = head`.
- While both: save hf->next, hf->next = hs, hf moves; save hs->next, hs->next = hf, hs moves.
- If hf is left over, `hf->next = NULL`.

## 6. Code

See the approaches above.

## 7. Dry run

`[1,2,3,4]`: mid = 3, reversed half 4 → 3 (2 still points to 3).

| round | links made | hf | hs |
|---|---|---|---|
| 1 | 1 → 4, 4 → 2 | 2 | 3 |
| 2 | 2 → 3, 3 → 3 (for a moment) | 3 | NULL |
| end | 3 → NULL | | |

Result **1 → 4 → 2 → 3**.

## 8. Final complexity + extension

**O(n) time, O(1) space.**

It reuses **LC 876** (middle), **LC 206** (reverse) and the weaving from **LC 21** (merge).

## What confused me / what clicked

- Save `temp` before every relink, or the rest of that half is lost.
- The last node can briefly point to itself; the final `hf->next = NULL` fixes it.
- Break a hard problem into problems you've already solved.
