## 1. Restate + clarify

Return `true` if `s` reads the same forwards and backwards **after** removing everything that isn't a letter or digit and ignoring upper/lower case.

Questions to ask:
- Do digits count? Yes (they're alphanumeric).
- Is 'A' the same as 'a'? Yes.
- Empty after cleaning (like `" "`)? Counts as a palindrome → true.
- Length? Up to 2·10⁵ printable ASCII characters.

## 2. Tiny example + edge case

`"A man, a plan, a canal: Panama"` → `amanaplanacanalpanama` → **true**.
`"race a car"` → `raceacar` → **false**.

Edge cases:
- `" "` → nothing left → **true**.
- `"0P"` → '0' vs 'p' → **false**. Digits are compared, not skipped.

## 3. Brute force + complexity

Build a cleaned, lower-cased copy and compare it with its reverse. **O(n) time, O(n) space.**

## 4. Pattern trigger

"Reads the same from both ends" → **two pointers from the outside in**. Skip junk in place → no copy → O(1) space.

## 5. Plan before coding

- `left = 0`, `right = n - 1`.
- While `left < right`:
  - Move `left` right past non-alphanumerics (stop if it reaches `right`).
  - Move `right` left past non-alphanumerics (same stop).
  - `tolower(s[left]) != tolower(s[right])` → return false.
  - `left++`, `right--`.
- Return true.

## 6. Code

See the approaches above.

## 7. Dry run

`s = "race a car"` (indices 0–9; index 4 and 6 are spaces)

| left | right | s[left] | s[right] | result |
|---|---|---|---|---|
| 0 | 9 | r | r | match → 1, 8 |
| 1 | 8 | a | a | match → 2, 7 |
| 2 | 7 | c | c | match → 3, 6 |
| 3 | 6 → skip space → 5 | e | a | **'e' ≠ 'a' → return false** |

`" "`: left = right = 0, the loop never runs → **true**.

## 8. Final complexity + extension

**O(n) time, O(1) space.**

Extension: **LC 680 Valid Palindrome II**, where you may delete at most one character. On the first mismatch, try skipping either `left` or `right` once and check if the rest is a palindrome.

## What confused me / what clicked

- Skip inside the loop instead of building a cleaned copy: same answer, O(1) space.
- The skip loops need `left < right` too, or `"..."` would run `left` off the end.
- `tolower` on **both** sides; digits are unchanged by it.
- `"0P"` is the trap: digits are kept and compared.
- Nested whiles but still O(n): each pointer only moves inward, so every character is passed once.
