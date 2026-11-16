## 1. Restate + clarify

Letters map to 1..26. Count the ways to decode a digit string. '0' can only appear as part of 10 or 20.

## 2. Tiny example + edge case

"12" → **2** (AB, L). "226" → **3** (BZ, VF, BBF). "06" → **0**. "11106" → **2**.

## 3. Brute force + complexity

Recursion choosing 1 or 2 digits: O(2ⁿ).

## 4. Pattern trigger

"Count ways, each step uses 1 or 2 characters" → **1-D DP like Climbing Stairs**.

## 5. Plan before coding

- next = 1, next2 = 0.
- From the end: cur = 0 if s[i] is '0'; else cur = next, plus next2 if s[i..i+1] is 10..26.
- Shift: next2 = next, next = cur.

## 6. Code

See the approaches above.

## 7. Dry run

"226" from the end:

- i = 2: '6' → 1.
- i = 1: '2' → 1, and "26" → + 1 → 2.
- i = 0: '2' → 2, and "22" → + 1 → **3**.

## 8. Final complexity + extension

**O(n) time, O(1) space.** Related: LC 70 Climbing Stairs, LC 639 Decode Ways II (with '*').

## What confused me / what clicked

- It's Climbing Stairs where some steps are blocked.
- A '0' makes its own position 0 ways, but it can still be the second digit of 10 or 20.
- I didn't paste code for this one; it's mine.
