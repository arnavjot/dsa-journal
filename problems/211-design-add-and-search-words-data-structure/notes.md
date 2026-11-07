## 1. Restate + clarify

Support `addWord(word)` and `search(pattern)`, where the pattern may contain `.` meaning "any one letter". search returns true if any added word matches the whole pattern.

Questions to ask:
- Lowercase letters only; at most 2 dots per search (LeetCode). A match must use the whole word (same length).

## 2. Tiny example + edge case

add bad, dad, mad → search pad **false**, bad **true**, .ad **true**, b.. **true**.
Edge case: search a prefix of a word ("ba") → false (no flag).

## 3. Brute force + complexity

Keep a list of words; compare the pattern with each word of the same length: **O(n·L)** per search.

## 4. Pattern trigger

"Many words + prefix-style lookups + a wildcard" → **Trie + DFS** (branch only at dots).

## 5. Plan before coding

- addWord: same as Trie insert.
- dfs(i, node): i == length → return flag.
- `.` → for each non-NULL child: if dfs(i + 1, child) → true. None → false.
- letter → missing link → false; else dfs(i + 1, that child).

## 6. Code

See the approaches above.

## 7. Dry run

Words at, and, an, add; search **a.d**:

| step | node | char | action |
|---|---|---|---|
| 1 | root | a | follow a |
| 2 | a | . | try d (the "add" branch) |
| 3 | ad | d | follow d → end, flag true → **true** |

The other children (n, t) are never tried.

## 8. Final complexity + extension

**addWord O(L); search O(L) without dots, worse with dots** (each dot branches up to 26 ways).

Extension: **LC 212 Word Search II** (trie + DFS on a grid).

## What confused me / what clicked

- Same trie as LC 208; only search changes.
- A dot = "try every child" = recursion with backtracking.
- Return true early; return false only after all children fail.
