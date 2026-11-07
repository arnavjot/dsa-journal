## 1. Restate + clarify

Return true if following `next` pointers ever comes back to a node already visited.

Questions to ask:
- `pos` is only used to build the test; the function just gets `head`. Empty list → false.

## 2. Tiny example + edge case

`[3,2,0,-4]`, tail → index 1 → **true**. `[1,2]`, tail → index 0 → **true**. `[1]` → **false**.

## 3. Brute force + complexity

Remember every visited node in a hash set: **O(n)** time, **O(n)** space.

## 4. Pattern trigger

"Detect a loop" with O(1) memory → **fast and slow pointers** (Floyd).

## 5. Plan before coding

- slow = fast = head.
- While fast && fast->next: fast moves 2, slow moves 1; if they're the same node → true.
- Loop ends → false.

## 6. Code

See the approaches above.

## 7. Dry run

`[3,2,0,-4]`, tail → #1

| step | slow | fast |
|---|---|---|
| 1 | #1 (2) | #2 (0) |
| 2 | #2 (0) | #1 (2) |
| 3 | #3 (−4) | #3 (−4) → **true** |

## 8. Final complexity + extension

**O(n) time, O(1) space.**

Extension: **LC 142** returns where the cycle starts (reset one pointer to head after they meet, move both by 1).

## What confused me / what clicked

- Check `fast && fast->next` before jumping two nodes.
- Compare **nodes**, not values.
- In the loop, the gap shrinks by 1 per step, so fast can't skip over slow.
