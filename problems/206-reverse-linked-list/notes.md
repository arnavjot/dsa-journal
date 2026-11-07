## 1. Restate + clarify

Reverse a singly linked list and return the new head.

Questions to ask:
- Empty list or one node → return as is. Up to 5000 nodes.

## 2. Tiny example + edge case

`1 → 2 → 3 → 4 → 5` → `5 → 4 → 3 → 2 → 1`. `[1,2]` → `[2,1]`.
Edge cases: `[]` → `[]`; one node → itself.

## 3. Brute force + complexity

Copy the values into an array, write them back in reverse: **O(n)** time, **O(n)** space.

## 4. Pattern trigger

"Reverse links in place" → **three pointers** (prev, curr, next).

## 5. Plan before coding

- prev = NULL, curr = head.
- While curr: `next = curr->next` → `curr->next = prev` → `prev = curr` → `curr = next`.
- Return prev.

## 6. Code

See the approaches above.

## 7. Dry run

`1 → 2 → 3`

| step | next | flip | prev | curr |
|---|---|---|---|---|
| 1 | 2 | 1 → NULL | 1 | 2 |
| 2 | 3 | 2 → 1 | 2 | 3 |
| 3 | NULL | 3 → 2 | 3 | NULL |

Return **3** → 3 → 2 → 1 → NULL.

## 8. Final complexity + extension

**O(n) time, O(1) space** (recursion: O(n) stack space).

Extensions: **LC 92 Reverse Linked List II** (reverse a part), **LC 25 Reverse Nodes in k-Group**, and reversing the second half in **LC 143 Reorder List** / **LC 234 Palindrome Linked List**.

## What confused me / what clicked

- **Save next first**, otherwise the rest of the list is gone after the flip.
- The loop ends with curr = NULL, so the answer is **prev**.
- Recursive: `head->next->next = head` then `head->next = NULL` (or the first two nodes form a cycle).
