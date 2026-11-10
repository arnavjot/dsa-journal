## 1. Restate + clarify

Return the longest substring of s that reads the same both ways. If there are several of the same length, any one is fine. 1 ≤ n ≤ 1000.

## 2. Tiny example + edge case

"babad" → "bab" (or "aba"). "cbbd" → "bb" (even length, two-letter middle). "a" → "a".

## 3. Brute force + complexity

Check every substring for being a palindrome: O(n²) substrings × O(n) check = **O(n³)**.

## 4. Pattern trigger

"Palindromic substring" → **expand around center** (or a 2-D DP table on s[i..j]).

## 5. Plan before coding

- expand(i, j): while in range and s[i] == s[j], move i left and j right; return s[i + 1 .. j − 1].
- For each center: odd = expand(c, c), even = expand(c, c + 1). Keep the longer one in maxi.

## 6. Code

See the approaches above.

## 7. Dry run

"cbbd":

| middle | expands to | length |
|---|---|---|
| (0,0) "c" | "c" | 1 |
| (1,2) "bb" | "bb", then c ≠ d stops | **2** |
| others | single letters | 1 |

Answer **"bb"**.

## 8. Final complexity + extension

**O(n²) time, O(1) extra space** for expanding. The DP table is O(n²) time and **O(n²) space**.

Extension: Manacher's algorithm finds it in **O(n)** by reusing palindromes already found (rarely expected in interviews).

Related: **LC 647 Palindromic Substrings** (same expansion, count instead of keep the longest).

## What confused me / what clicked

- Two middles per index: (c, c) for odd, (c, c + 1) for even.
- When the loop stops, the palindrome is s[i + 1 .. j − 1], one step back in.
- My `j <= s.length()` works because s[s.length()] is the end character '\0', which never matches a letter; `j < s.length()` is clearer.
- Passing `string s` by value copies it each call; `const string& s` avoids that.
