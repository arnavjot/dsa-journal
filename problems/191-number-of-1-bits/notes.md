## 1. Restate + clarify

Return the number of 1 bits in the binary form of n (the Hamming weight). 1 ≤ n ≤ 2³¹ − 1.

## 2. Tiny example + edge case

11 (1011) → **3**. 128 (10000000) → **1**. 2147483645 → **30**.

## 3. Brute force + complexity

Check all 32 bits with n & 1 and shifts: always 32 steps.

## 4. Pattern trigger

"Count / clear set bits" → **n & (n − 1) drops the lowest 1**.

## 5. Plan before coding

- count = 0.
- While n != 0: n &= n − 1; count++.
- Return count.

## 6. Code

See the approaches above.

## 7. Dry run

44 = 101100 → 101000 → 100000 → 0: **3** steps.

## 8. Final complexity + extension

**O(k) time where k is the number of 1 bits (≤ 32), O(1) space.** Related: LC 338 Counting Bits (dp[i & (i − 1)] + 1), LC 231 Power of Two.

## What confused me / what clicked

- n − 1 flips the lowest 1 and every 0 below it, so the AND clears exactly that 1.
- I didn't paste code for this one; both versions are mine.
