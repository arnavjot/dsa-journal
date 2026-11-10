## 1. Restate + clarify

Count the substrings of s that are palindromes. Substrings at different positions count separately even if they look the same; every single letter counts. 1 ≤ n ≤ 1000.

## 2. Tiny example + edge case

"abc" → 3 (just the letters). "aaa" → 6 (a, a, a, aa, aa, aaa). "a" → 1.

## 3. Brute force + complexity

Check every substring: O(n²) substrings × O(n) check = **O(n³)**.

## 4. Pattern trigger

"Count palindromic substrings" → **expand around center**, the same as LC 5 but counting.

## 5. Plan before coding

- expand(i, j): while in range and s[i] == s[j]: count++, i--, j++. Return count.
- Total = sum over centers of expand(c, c) + expand(c, c + 1).

## 6. Code

See the approaches above.

## 7. Dry run

"aaa":

| middle | palindromes | adds |
|---|---|---|
| (0,0) | a | 1 |
| (0,1) | aa | 1 |
| (1,1) | a, aaa | 2 |
| (1,2) | aa | 1 |
| (2,2) | a | 1 |
| (2,3) | none (past the end) | 0 |

Total **6**.

## 8. Final complexity + extension

**O(n²) time, O(1) extra space.** The DP table is O(n²) time and O(n²) space.

Extension: Manacher's algorithm counts them in O(n).

Related: **LC 5 Longest Palindromic Substring**.

## What confused me / what clicked

- Each successful step from a middle = exactly one palindrome, so count steps.
- My loop checks `i < s.length()`, but it should be `j < s.length()`. It worked anyway: i only goes down, and s[j] at the end is '\0', which never matches.
- Same skeleton as LC 5: learn it once, use it for both.
