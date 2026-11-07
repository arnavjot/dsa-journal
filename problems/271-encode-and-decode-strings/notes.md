## 1. Restate + clarify

Design `encode` (list of strings → one string) and `decode` (back to the same list). Strings can contain **any** characters.

Questions to ask:
- Any characters, including `#` and digits? Yes.
- Empty strings or an empty list? Must round-trip too.

## 2. Tiny example + edge case

`["neet","code","love","you"]` → `"4#neet4#code4#love3#you"`.

Edge cases: `["a#b","12","#"]` → `"3#a#b2#121##"`, still decodes. `["hi","","yo"]` → `"2#hi0#2#yo"`.

## 3. Brute force + complexity

Join with a separator and escape it inside words: works but fiddly and error-prone.

## 4. Pattern trigger

"Serialize a list of arbitrary strings" → **length-prefixed** (self-describing) format.

## 5. Plan before coding

- encode: `len + "#" + s` for each s.
- decode: from i, move j to the first `#`; length = number in `s[i..j)`; word = next `length` chars; `i = j + 1 + length`.

## 6. Code

See the approaches above.

## 7. Dry run

`"3#a#b2#121##"`

| i | j (first #) | length | word | next i |
|---|---|---|---|---|
| 0 | 1 | 3 | "a#b" | 5 |
| 5 | 6 | 2 | "12" | 9 |
| 9 | 10 | 1 | "#" | 12 |

## 8. Final complexity + extension

**O(total characters) time and space.**

Extension: a fixed 4-byte length (no `#` needed) is how real network protocols do it.

## What confused me / what clicked

- The length tells you exactly how many characters to take, so the word can contain anything.
- The first `#` after a length is always the real separator, because decoding jumps over whole words.
- Empty strings encode as `0#`.
