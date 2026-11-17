## 1. Restate + clarify

Count how many distinct subsequences of s equal t (different index choices count separately).

## 2. Tiny example + edge case

"rabbbit", "rabbit" → **3**. "babgbag", "bag" → **5**. "abc", "d" → **0**.

## 3. Brute force + complexity

Try all 2^m subsequences: exponential.

## 4. Pattern trigger

"Count the ways t appears in s" → **DP over (i, j)**, one row.

## 5. Plan before coding

- dp[0] = 1.
- For each letter s[i − 1], for j = n..1: if s[i − 1] == t[j − 1], dp[j] += dp[j − 1].
- Return dp[n].

## 6. Code

See the approaches above.

## 7. Dry run

"rabbbit", "rbt": the 'r' gives dp[1] = 1. Each of the three b's adds 1 to dp[2], so dp[2] = 3. The 't' then makes dp[3] = **3**.

## 8. Final complexity + extension

**O(m × n) time, O(n) space.** Related: LC 1143 LCS, LC 72 Edit Distance, LC 940 Distinct Subsequences II.

## What confused me / what clicked

- Matching letter: ways that skip it plus ways that use it.
- Right to left keeps dp[j − 1] from the previous letter.
- LeetCode only promises the final answer fits, so I used unsigned.
- I didn't paste code for this one; it's mine.
