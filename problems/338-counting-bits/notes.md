## 1. Restate + clarify

Return an array ans of length n + 1 where ans[i] is the number of 1 bits in i, for 0 ≤ i ≤ n.

## 2. Tiny example + edge case

n = 2 → **[0,1,1]**. n = 5 → **[0,1,1,2,1,2]**. n = 0 → **[0]**.

## 3. Brute force + complexity

Count the bits of every i (n & (n − 1) loop or 32 shifts): O(n log n).

## 4. Pattern trigger

"Answer for every i up to n, built from smaller i" → **DP over bits**.

## 5. Plan before coding

- dp[0] = 0, offset = 1.
- For i = 1..n: if offset * 2 == i, offset = i; dp[i] = 1 + dp[i − offset].

## 6. Code

See the approaches above.

## 7. Dry run

n = 5:

| i | binary | offset | dp |
|---|---|---|---|
| 1 | 1 | 1 | 1 + dp[0] = 1 |
| 2 | 10 | 2 | 1 + dp[0] = 1 |
| 3 | 11 | 2 | 1 + dp[1] = 2 |
| 4 | 100 | 4 | 1 + dp[0] = 1 |
| 5 | 101 | 4 | 1 + dp[1] = **2** |

## 8. Final complexity + extension

**O(n) time, O(1) extra space.** Other forms of the same idea: dp[i >> 1] + (i & 1), or dp[i & (i − 1)] + 1.

## What confused me / what clicked

- i is its top bit plus a smaller number, and the smaller number is already solved.
- offset doubles exactly at powers of two.
