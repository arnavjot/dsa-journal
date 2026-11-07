## 1. Restate + clarify

Split s into pieces so that every piece is a palindrome. Return all such partitions.

Questions to ask:
- Single characters are palindromes, so at least one partition always exists. n ≤ 16.

## 2. Tiny example + edge case

"aab" → [a,a,b], [aa,b]. "a" → [a]. "abba" → [a,b,b,a], [a,bb,a], [abba].

## 3. Brute force + complexity

Each of the n − 1 gaps is cut or not: 2ⁿ⁻¹ partitions, check each piece in O(n) → **O(n·2ⁿ)**. Backtracking does the same work but stops early at non-palindromes.

## 4. Pattern trigger

"All ways to split into valid pieces" → **backtracking on where the next piece ends**.

## 5. Plan before coding

- backtrack(start): start == n → save curr.
- for i from start: if s[start..i] is a palindrome → push it, backtrack(i + 1), pop.

## 6. Code

See the approaches above.

## 7. Dry run

"aab": start 0: "a" ✓ → start 1: "a" ✓ → start 2: "b" ✓ → **save a|a|b**; back at start 1: "ab" ✗. Back at start 0: "aa" ✓ → start 2: "b" ✓ → **save aa|b**; "aab" ✗.

## 8. Final complexity + extension

**O(n·2ⁿ) time, O(n) recursion** (+ O(n²) for the optional table).

Extension: **LC 132 Palindrome Partitioning II** (fewest cuts → DP instead of listing all).

## What confused me / what clicked

- The loop picks **where the first piece ends**; recursion handles the rest.
- Cut a branch as soon as a piece isn't a palindrome.
- A table pal[i][j] turns each O(n) check into O(1).
