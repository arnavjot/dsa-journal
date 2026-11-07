## 1. Restate + clarify

Return true if some **contiguous** substring of `s2` is a permutation of `s1` (same letters, any order).

Questions to ask:
- Lowercase only; lengths up to 10⁴.
- s1 longer than s2 → false.

## 2. Tiny example + edge case

`"ab"` in `"eidbaooo"` → "ba" → **true**. `"ab"` in `"eidboaoo"` → **false**.

Edge case: the very first window can match (`"abc"` in `"cbaxyz"`).

## 3. Brute force + complexity

Sort every window of length m and compare with sorted s1: **O(n · m log m)**.

## 4. Pattern trigger

"Anagram of s1 inside s2" → **fixed-size sliding window** of letter counts.

## 5. Plan before coding

- If m > n → false.
- Count s1 and the first m letters of s2; equal → true.
- For i = m … n − 1: remove s2[i − m], add s2[i]; equal → true.
- Return false.

## 6. Code

See the approaches above.

## 7. Dry run

`"ab"` in `"eidbaooo"`

| window | counts equal? |
|---|---|
| "ei" | no |
| "id" | no |
| "db" | no |
| "ba" | **yes → true** |

## 8. Final complexity + extension

**O(26 · n) = O(n) time, O(1) space.**

Extensions: keep a count of how many of the 26 letters match to make each step O(1); **LC 438 Find All Anagrams in a String** (same window, collect every start).

## What confused me / what clicked

- Permutation = same counts → compare count arrays.
- The window size never changes; only two counts move per step.
- `vector == vector` compares all 26 slots, which is still constant work.
