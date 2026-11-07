## 1. Restate + clarify

Reverse the nodes of the list k at a time. A last group with fewer than k nodes stays as it is. Change links, not values.

Questions to ask:
- 1 ≤ k ≤ n. k = 1 → unchanged. O(1) extra space is the follow-up.

## 2. Tiny example + edge case

`[1,2,3,4,5]`, k = 2 → `[2,1,4,3,5]`; k = 3 → `[3,2,1,4,5]`. k = n → the whole list reversed.

## 3. Brute force + complexity

Copy values to an array, reverse each full chunk, write back: **O(n)** time, **O(n)** space.

## 4. Pattern trigger

"Reverse parts of a list in place" → **dummy node + bef pointer + in-place group reversal**.

## 5. Plan before coding

- dummy → head, bef = dummy.
- Walk kthNode k steps from bef; NULL → stop.
- start = bef->next, curr = start->next; k − 1 times: `start->next = curr->next; curr->next = bef->next; bef->next = curr; curr = start->next;`
- bef = start. Repeat. Return dummy->next.

## 6. Code

See the approaches above.

## 7. Dry run

`[1,2,3,4,5]`, k = 3, group 1 (bef = D, start = 1):

| move | curr taken | list after |
|---|---|---|
| 1 | 2 | D → 2 → 1 → 3 → 4 → 5 |
| 2 | 3 | D → 3 → 2 → 1 → 4 → 5 |

bef = 1. Next: only 4, 5 remain (< 3) → stop. Answer **3 → 2 → 1 → 4 → 5**.

## 8. Final complexity + extension

**O(n) time, O(1) space.**

The commented recursive version is correct but calls getLength on the **whole remaining list** in every call: O(n²/k) time, O(n/k) stack. Counting just k nodes ahead fixes it to O(n).

## What confused me / what clicked

- Check that k nodes exist **before** touching any link.
- The 3-line "move curr to the front" trick reverses a group with one pass.
- `bef = start`: the old first node is now the group's last.
