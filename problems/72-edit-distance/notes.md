## 1. Restate + clarify

Turn word1 into word2 using the fewest edits, where each edit is one insert, one delete or one replace of a single letter. Lengths 0 to 500, lowercase letters.

## 2. Tiny example + edge case

"horse" → "ros" = **3** (replace h → r, delete r, delete e). "intention" → "execution" = **5**. "" → "abc" = **3** (insert all). Same word → **0**.

## 3. Brute force + complexity

At every mismatch try all three edits: O(3^(n + m)).

## 4. Pattern trigger

"Fewest edits to turn one string into another" → **2-D DP over (i, j)**. It's the same shape as LCS, but with three choices on a mismatch.

## 5. Plan before coding

- dp[i][j] = fewest edits to turn word1[i..] into word2[j..].
- dp[n][j] = m − j (insert the rest), dp[i][m] = n − i (delete the rest).
- Match → dp[i + 1][j + 1]. Otherwise 1 + min(dp[i][j + 1] insert, dp[i + 1][j] delete, dp[i + 1][j + 1] replace).
- Each cell needs only its right, below and diagonal neighbours → two columns.

## 6. Code

See the approaches above.

## 7. Dry run

"horse" (rows) → "ros" (columns):

| | r | o | s | ∅ |
|---|---|---|---|---|
| h | **3** | 3 | 4 | 5 |
| o | 3 | **2** | 3 | 4 |
| r | 2 | 2 | **2** | 3 |
| s | 3 | 2 | **1** | 2 |
| e | 3 | 2 | 1 | **1** |
| ∅ | 3 | 2 | 1 | **0** |

The path in bold:
- (h, r) → replace h with r.
- (o, o) → match.
- (r, s) → delete r.
- (s, s) → match.
- e → delete.

That's 3 edits.

## 8. Final complexity + extension

**O(n × m) time, O(n) space.** With j as the outer loop the arrays are size n + 1; swap the loops to get O(m).

Extension: to list the actual edits, keep the full table and walk from (0, 0) following the choice that gave each minimum. Related: LC 1143 LCS, LC 583 Delete Operation for Two Strings, LC 161 One Edit Distance.

## What confused me / what clicked

- Edits are on word1. Insert puts word2[j] in front of word1[i], so j moves on and i stays.
- Delete removes word1[i], so i moves on and j stays.
- Replace turns word1[i] into word2[j], so both move on.
- A match is free, and taking it is never worse than editing.
- Base cases aren't 0: if one word is used up, every letter left in the other costs one edit.
- My recursion and memo pass the strings by `&`; by value copies them on every call and blows the memory, which is what my comment says.
- My space-optimised loop is column by column (j outside), so `curr[a.length()]` has to be reset to m − j for every new column.
