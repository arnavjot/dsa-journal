## 1. Restate + clarify

Is s3 an interleaving of s1 and s2, using all their letters and keeping each one's order?

## 2. Tiny example + edge case

"aabcc", "dbbca", "aadbbcbcac" → **true**. Same s1, s2 with "aadbbbaccc" → **false**. "", "", "" → **true**.

## 3. Brute force + complexity

Recursion choosing s1 or s2 for each letter: O(2^(m + n)).

## 4. Pattern trigger

"Merge two sequences keeping order" → **DP over (i, j)**.

## 5. Plan before coding

- If m + n ≠ |s3| → false.
- dp[0][0] = true; dp[i][j] = (dp[i − 1][j] && s1[i − 1] == s3[i + j − 1]) || (dp[i][j − 1] && s2[j − 1] == s3[i + j − 1]).
- Keep one row.

## 6. Code

See the approaches above.

## 7. Dry run

"aab", "axy", "aaxaby": the first two 'a's can come from either string; the DP keeps both options, and the path a (s1), a (s2), x (s2), a (s1), b (s1), y (s2) works → **true**.

## 8. Final complexity + extension

**O(m × n) time, O(n) space.**

## What confused me / what clicked

- The last letter of the prefix came from one string or the other; that's the whole recurrence.
- One row works because dp[j] still holds the row above when it's read.
- I didn't paste code for this one; it's mine.
