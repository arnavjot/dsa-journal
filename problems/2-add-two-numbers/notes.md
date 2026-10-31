## 1. Restate + clarify

Two non-empty linked lists each hold a non-negative number, **one digit per node, ones digit first**. Return their sum as a list in the same backwards format.

Questions to ask:
- Can the lists have different lengths? Yes.
- Leading zeros? No, except the number 0 itself (`[0]`).
- Size: 1 to 100 nodes each, every value 0–9. 100 digits is far too big for any integer type.

## 2. Tiny example + edge case

`[2,4,3] + [5,6,4]` → 342 + 465 = 807 → **`[7,0,8]`**.

Edge cases:
- Different lengths: `[9,9,1] + [1]` → 199 + 1 = 200 → `[0,0,2]`.
- Carry left over at the end: `[5] + [5]` → 10 → `[0,1]`. The answer is **longer** than both inputs.
- `[0] + [0]` → `[0]`.

## 3. Brute force + complexity

Read each list into a `long long`, add, write the sum back out digit by digit. **O(m + n) time, O(1) extra space**, but it **overflows**: 100 digits won't fit in 64 bits. Say it, then drop it.

## 4. Pattern trigger

"Digits in reverse order" + "add" → **column addition with a carry**, like on paper. "Build a new list" → **dummy head node** so the first append isn't a special case.

## 5. Plan before coding

- `dummy` node, `temp = dummy`, `carry = 0`.
- Loop while `carry != 0 || l1 != NULL || l2 != NULL`:
  - `sum = carry`, add `l1->val` if l1 exists (then move l1), same for l2.
  - `carry = sum / 10`, append `new ListNode(sum % 10)`, move `temp`.
- Return `dummy->next`.

## 6. Code

See the approaches above.

## 7. Dry run

`l1 = [2,4,3]`, `l2 = [5,6,4]`

| column | carry in | l1 | l2 | sum | write (sum % 10) | carry out (sum / 10) | answer so far |
|---|---|---|---|---|---|---|---|
| ones | 0 | 2 | 5 | 7 | 7 | 0 | [7] |
| tens | 0 | 4 | 6 | 10 | 0 | 1 | [7,0] |
| hundreds | 1 | 3 | 4 | 8 | 8 | 0 | [7,0,8] |

Next check: carry 0, l1 NULL, l2 NULL → stop. Return **`[7,0,8]`** = 807 ✅

Edge case `[5] + [5]`:

| column | carry in | l1 | l2 | sum | write | carry out | answer so far |
|---|---|---|---|---|---|---|---|
| ones | 0 | 5 | 5 | 10 | 0 | 1 | [0] |
| tens | 1 | NULL → 0 | NULL → 0 | 1 | 1 | 0 | [0,1] |

The second column only runs because of `carry != 0` in the while condition.

## 8. Final complexity + extension

**O(max(m, n)) time, O(1) extra space** (the answer list itself is output).

Extension: **LC 445 Add Two Numbers II** stores digits in normal order (most significant first). Push both lists onto two stacks (or reverse them), then do the same column addition, building the answer by adding each new node at the **front**.

## What confused me / what clicked

- Reverse order isn't a twist, it's a gift: the ones digits come first, exactly where hand addition starts.
- When one list runs out, just skip it. A missing digit is the same as a 0, so no padding is needed.
- The carry is only ever 0 or 1 (max column = 9 + 9 + 1 = 19).
- `carry != 0` in the loop condition is what creates the extra final node for 999 + 1 or 5 + 5.
- `dummy` saves an "is the answer empty?" check; return `dummy->next` to skip it.
