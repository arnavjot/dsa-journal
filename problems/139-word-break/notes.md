## 1. Restate + clarify

Can s be split into a sequence of dictionary words (words can be reused)?

## 2. Tiny example + edge case

"leetcode", [leet, code] → **true**. "applepenapple", [apple, pen] → **true**. "catsandog", [cats, dog, sand, and, cat] → **false**.

## 3. Brute force + complexity

Recursion: try each word as the first piece. Exponential on inputs like "aaaa…b".

## 4. Pattern trigger

"Split a string into dictionary words" → **dp over prefixes**.

## 5. Plan before coding

- dp[0] = true.
- For i = 1..n: for each word w: if |w| ≤ i, dp[i − |w|] and s ends with w at i → dp[i] = true.
- Return dp[n].

## 6. Code

See the approaches above.

## 7. Dry run

"leetcode": dp[4] = true ("leet" with dp[0]). dp[8] = true ("code" with dp[4]) → **true**.

## 8. Final complexity + extension

**O(n × W × L) time, O(n) space.** Related: LC 140 Word Break II (list all splits), LC 472 Concatenated Words.

## What confused me / what clicked

- dp[i] looks back one word.
- Memoising each prefix stops the exponential retries.
- I didn't paste code for this one; it's mine.
