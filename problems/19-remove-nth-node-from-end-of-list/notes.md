## 1. Restate + clarify

Remove the n-th node from the **end** and return the head.

Questions to ask:
- n is always valid (1 ≤ n ≤ length). The head itself may be removed.

## 2. Tiny example + edge case

`[1,2,3,4,5]`, n = 2 → `[1,2,3,5]`. `[1]`, n = 1 → `[]`. `[1,2]`, n = 1 → `[1]`.

## 3. Brute force + complexity

Count the length, then walk to node `len − n` and skip the next one: **O(n)**, two passes.

## 4. Pattern trigger

"n-th from the end in one pass" → **two pointers with a gap of n**.

## 5. Plan before coding

- fast moves n steps ahead.
- fast == NULL → n is the length: remove the head.
- Else move both until fast->next == NULL; slow->next = slow->next->next.

## 6. Code

See the approaches above.

## 7. Dry run

`[1,2,3,4,5]`, n = 2

| step | slow | fast |
|---|---|---|
| head start | 1 | 3 |
| move | 2 | 4 |
| move | 3 | 5 (last) |

slow->next = 5 → `[1,2,3,5]`.

## 8. Final complexity + extension

**O(n) time, O(1) space.**

A **dummy node** before head removes the `fast == NULL` special case: start slow at the dummy.

## What confused me / what clicked

- The gap of n is what puts slow **right before** the target.
- `while (fast->next != NULL)`: fast stops **on** the last node.
- Removing the head is the edge case (or use a dummy).
