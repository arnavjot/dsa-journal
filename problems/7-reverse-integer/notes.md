## 1. Restate + clarify

Reverse the digits of a 32-bit signed integer. If the result doesn't fit in 32 bits, return 0. 64-bit integers aren't allowed.

## 2. Tiny example + edge case

123 → **321**. −123 → **−321**. 120 → **21**. 1534236469 → **0** (9646324351 overflows).

## 3. Brute force + complexity

Convert to a string, reverse it, parse it as a long and check the range. That works but uses 64 bits, which isn't allowed.

## 4. Pattern trigger

"Reverse digits, watch overflow" → **pop % 10 / push × 10, check before multiplying**.

## 5. Plan before coding

- sum = 0.
- While x != 0: if |sum| > INT_MAX / 10 → return 0; sum = sum × 10 + x % 10; x /= 10.
- Return sum.

## 6. Code

See the approaches above.

## 7. Dry run

1534236469: sum grows 9 → 96 → 964 → … → 964632435. With x = 1 still left, |sum| > 214748364 → **0**.

## 8. Final complexity + extension

**O(log x) time, O(1) space.** Related: LC 9 Palindrome Number (reverse half the digits), LC 8 String to Integer (same overflow check).

## What confused me / what clicked

- I first wrote this in Java; the C++ is the same logic with abs and INT_MAX.
- The check comes before the push, so sum itself never overflows.
- % on a negative x gives a negative digit, so negatives need no special case.
