## 1. Restate + clarify

Find the length of the longest sequence of letters that appears, in order (not necessarily next to each other), in both text1 and text2. Lowercase letters, lengths 1 to 1000.

## 2. Tiny example + edge case

"abcde", "ace" → **3** ("ace"). "abc", "abc" → **3**. "abc", "def" → **0**.

## 3. Brute force + complexity

Every subsequence of text1 (2ⁿ of them), each checked against text2 in O(m): O(2ⁿ × m). The plain recursion is O(2^(n + m)).

## 4. Pattern trigger

"Two strings, keep the order, longest common / fewest edits" → **2-D DP over (i, j)**, one index per string.

## 5. Plan before coding

- dp[i][j] = LCS of text1[i..] and text2[j..]; dp[n][·] = dp[·][m] = 0.
- Match → 1 + dp[i + 1][j + 1]. Mismatch → max(dp[i + 1][j], dp[i][j + 1]).
- Fill i from n − 1 down, j from m − 1 down. Answer dp[0][0].
- Only row i + 1 and the current row are needed → two rows.

## 6. Code

See the approaches above.

## 7. Dry run

"abcde" vs "ace" (rows = text1 letters, columns = text2 letters, last row and column 0):

| | a | c | e | end |
|---|---|---|---|---|
| a | **3** | 2 | 1 | 0 |
| b | 2 | 2 | 1 | 0 |
| c | 2 | **2** | 1 | 0 |
| d | 1 | 1 | 1 | 0 |
| e | 1 | 1 | **1** | 0 |
| end | 0 | 0 | 0 | 0 |

Bold cells are the matches used: e = e, c = c, a = a → 3.

## 8. Final complexity + extension

**O(n × m) time, O(m) space.**

Extension: to print the subsequence, keep the full table and walk from (0, 0): on a match take the letter and go diagonally, otherwise move toward the larger neighbour. Related: LC 72 Edit Distance, LC 583 Delete Operation for Two Strings, LC 1092 Shortest Common Supersequence.

## What confused me / what clicked

- On a match, there's no need to also try skipping: taking the pair is never worse.
- On a mismatch, one of the two letters is unused, so skip one or the other and keep the max.
- Two rows work because cell (i, j) only looks at (i + 1, j + 1), (i + 1, j) and (i, j + 1). The last one is in the current row, already filled because j goes right to left.
- My recursion takes `string text1, string text2` by value, so each call copies both strings. The memo takes them by `&`, which is why it's fast.
- The `i` and `j` parameters of solveTab and solveTabSO are never used (the loops use i_index and j_index).
