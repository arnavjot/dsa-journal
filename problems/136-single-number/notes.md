## 1. Restate + clarify

Every number appears twice except one. Find it in O(n) time and O(1) extra space.

## 2. Tiny example + edge case

[2,2,1] → **1**. [4,1,2,1,2] → **4**. [1] → **1**.

## 3. Brute force + complexity

Hash map of counts: O(n) time, O(n) space. Or sort and compare neighbours: O(n log n).

## 4. Pattern trigger

"Pairs cancel, find the odd one out" → **XOR**.

## 5. Plan before coding

- ans = 0.
- ans ^= each number.
- Return ans.

## 6. Code

See the approaches above.

## 7. Dry run

[4,1,2,1,2]: 0 ^ 4 = 4 → ^1 = 5 → ^2 = 7 → ^1 = 6 → ^2 = **4**.

## 8. Final complexity + extension

**O(n) time, O(1) space.** Related: LC 268 Missing Number (XOR indexes and values), LC 137 Single Number II (count each bit mod 3), LC 260 Single Number III (split by one differing bit).

## What confused me / what clicked

- x ^ x = 0 and x ^ 0 = x.
- Order doesn't matter, so the pairs don't need to be next to each other.
- Each bit of the answer is just the parity of that bit across all numbers.
