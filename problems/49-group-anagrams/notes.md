## 1. Restate + clarify

Group the strings that are anagrams of each other. Any order of groups and of words inside a group.

Questions to ask:
- Lowercase a–z only? Yes. Empty strings? Allowed (`""` groups with other `""`).
- Up to 10⁴ words, each up to 100 letters.

## 2. Tiny example + edge case

`["eat","tea","tan","ate","nat","bat"]` → **[[eat,tea,ate],[tan,nat],[bat]]**.

Edge cases: `[""]` → [[""]]. `["a"]` → [["a"]].

## 3. Brute force + complexity

For each word, scan the rest with an anagram check: **O(n² · m)**.

## 4. Pattern trigger

"Group by an equivalence" → find a **canonical key** (letter counts or sorted word) → **hash map key → group**.

## 5. Plan before coding

- `signature(w)`: count 26 letters, join counts with `#`.
- `groups[signature(w)].push_back(w)` for each word.
- Copy each group into `ans`.

## 6. Code

See the approaches above.

## 7. Dry run

| word | key (non-zero letters) | group |
|---|---|---|
| eat | a1 e1 t1 | new → [eat] |
| tea | a1 e1 t1 | [eat, tea] |
| tan | a1 n1 t1 | new → [tan] |
| ate | a1 e1 t1 | [eat, tea, ate] |
| nat | a1 n1 t1 | [tan, nat] |
| bat | a1 b1 t1 | new → [bat] |

## 8. Final complexity + extension

**O(n · m) time, O(n · m) space.**

Extension: sorted-word key, `sort(w)` → O(m log m) per word; same idea.

## What confused me / what clicked

- Anagram = same counts → counts make a perfect key.
- `#` separators stop "1,11" and "11,1" from colliding.
- The map does the grouping; one pass over the words.
