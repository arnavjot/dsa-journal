## 1. Restate + clarify

Return the length of the longest **substring** (contiguous) with no repeated characters.

Questions to ask:
- Substring, not subsequence? Yes.
- Characters: letters, digits, symbols, spaces. Empty string → 0.
- Up to 5·10⁴ characters.

## 2. Tiny example + edge case

`"abcabcbb"` → "abc" → **3**. `"bbbbb"` → **1**. `"pwwkew"` → "wke" → **3** ("pwke" isn't contiguous).

## 3. Brute force + complexity

From each start, extend with a fresh set until a repeat: **O(n²)** worst case.

## 4. Pattern trigger

"Longest contiguous stretch obeying a rule" → **sliding window** with a set (or last-index map).

## 5. Plan before coding

- left = 0, maxi = 0, empty set.
- For each right: while `s[right]` in set → erase `s[left]`, left++. Insert `s[right]`. maxi = max(maxi, right − left + 1).

## 6. Code

See the approaches above.

## 7. Dry run

`"pwwkew"`

| right | char | shrink | window | maxi |
|---|---|---|---|---|
| 0 | p | — | p | 1 |
| 1 | w | — | pw | 2 |
| 2 | w | erase p, erase w | w | 2 |
| 3 | k | — | wk | 2 |
| 4 | e | — | wke | **3** |
| 5 | w | erase w | kew | 3 |

## 8. Final complexity + extension

**O(n) time, O(min(n, alphabet)) space.**

Extensions: store each character's last index and jump `left = max(left, last[c] + 1)`; **LC 424**, **LC 76** use the same window shape.

## What confused me / what clicked

- The window always stays repeat-free; it only grows on the right and shrinks on the left.
- `while`, not `if`: the old copy may be deep inside.
- left never moves back, so the total work is O(n).
