## 1. Restate + clarify

You may change at most `k` characters to any letter. Return the length of the longest substring that can be made of **one repeated letter**.

Questions to ask:
- Uppercase A–Z only; 1 ≤ n ≤ 10⁵; 0 ≤ k ≤ n.

## 2. Tiny example + edge case

`"ABAB"`, k = 2 → change both B's (or A's) → **4**.
`"AABABBA"`, k = 1 → "AABA" → **4**.

Edge case: k = 0 → longest run of one letter.

## 3. Brute force + complexity

Every window with a 26-count array: **O(n²)**.

## 4. Pattern trigger

"Longest substring under a budget" → **sliding window**; the window's cost = length − most frequent count.

## 5. Plan before coding

- For each j: `freq[s[j]]++`, update maxCount.
- While `(j − i + 1) − maxCount > k`: `freq[s[i]]--`, i++.
- maxLen = max(maxLen, j − i + 1).

## 6. Code

See the approaches above.

## 7. Dry run

`"AABABBA"`, k = 1

| j | add | maxCount | window | cost | action | maxLen |
|---|---|---|---|---|---|---|
| 0 | A | 1 | A | 0 | — | 1 |
| 1 | A | 2 | AA | 0 | — | 2 |
| 2 | B | 2 | AAB | 1 | — | 3 |
| 3 | A | 3 | AABA | 1 | — | **4** |
| 4 | B | 3 | AABAB | 2 | slide → ABAB | 4 |
| 5 | B | 3 | ABABB | 2 | slide → BABB | 4 |
| 6 | A | 3 | BABBA | 2 | slide → ABBA | 4 |

## 8. Final complexity + extension

**O(n) time, O(26) space.**

Extensions: same "window with a budget" shape as **LC 1004 Max Consecutive Ones III**.

## What confused me / what clicked

- Replacements needed = length − count of the most common letter.
- `maxCount` is never decreased; a stale value just means the window slides at the same size, so the answer is still right.
- Because of that, the while runs at most once per j.
