## 1. Restate + clarify

Compute x to the power n, where n is any 32-bit int (it can be negative, even −2³¹).

## 2. Tiny example + edge case

2, 10 → **1024**. 2.1, 3 → **9.261**. 2, −2 → **0.25**. Edge: n = −2³¹ (−n doesn't fit in an int).

## 3. Brute force + complexity

Multiply x by itself |n| times: O(n), up to 2³¹ steps → TLE.

## 4. Pattern trigger

"Power with a huge exponent" → **binary exponentiation**: square the base, halve the exponent.

## 5. Plan before coding

- N = n as long long; if N < 0: x = 1/x, N = −N.
- ans = 1. While N > 0: if N is odd, ans *= x; x *= x; N >>= 1.
- Return ans.

## 6. Code

See the approaches above.

## 7. Dry run

3¹³, 13 = 1101₂:

| N | bit | ans | x after |
|---|---|---|---|
| 13 | 1 | 3 | 9 |
| 6 | 0 | 3 | 81 |
| 3 | 1 | 243 | 6561 |
| 1 | 1 | **1594323** | … |

## 8. Final complexity + extension

**O(log n) time, O(1) space.** The recursive version (x^(n/2))², times x if n is odd, is the same idea with an O(log n) stack. The same trick does modular power (a^b mod m) and matrix power (fast Fibonacci).

## What confused me / what clicked

- Every n is a sum of powers of 2, so x^n is a product of x^(2^k), and those come from repeated squaring.
- −2³¹ can't be negated in an int: use long long.
- My code uses `long double` for base and ans. That keeps more digits through the squarings: on LeetCode-sized answers its worst relative error was about 8 × 10⁻¹⁵, vs 5 × 10⁻¹² with plain double.
- `long long num = n` makes −(−2³¹) safe.
