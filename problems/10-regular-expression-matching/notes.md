## 1. Restate + clarify

Implement full-string regex matching with '.' (any one letter) and '*' (zero or more of the previous element).

## 2. Tiny example + edge case

"aa", "a" → **false**. "aa", "a*" → **true**. "ab", ".*" → **true**. "aab", "c*a*b" → **true**.

## 3. Brute force + complexity

Plain recursion branches at every *: exponential.

## 4. Pattern trigger

"Regex / wildcard matching" → **DP over (i, j)**; decide '*' on the letter before it.

## 5. Plan before coding

- dp[m][n] = true; dp[i][n] = false for i < m.
- For i = m..0, j = n − 1..0: first = i < m && (p[j] == s[i] || p[j] == '.').
- If p[j + 1] == '*': dp[i][j] = dp[i][j + 2] || (first && dp[i + 1][j]).
- Else dp[i][j] = first && dp[i + 1][j + 1].

## 6. Code

See the approaches above.

## 7. Dry run

"aa", "a*": dp[2][0] = skip → dp[2][2] = true. dp[1][0] = skip (false) or use 'a' → dp[2][0] = true. dp[0][0] uses 'a' → dp[1][0] = **true**.

## 8. Final complexity + extension

**O(m × n) time and space.** Related: LC 44 Wildcard Matching (simpler '*').

## What confused me / what clicked

- Decide the '*' while standing on the letter before it.
- Skip or use once and stay: that one rule covers zero or more repeats.
- I didn't paste code for this one; it's mine.
