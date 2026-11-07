## 1. Restate + clarify

Return `true` if `t` is an **anagram** of `s`: the same letters, each used the same number of times, in any order.

Questions to ask:
- Only lowercase a–z? Yes (follow-up asks about Unicode).
- Length? 1 to 5·10⁴.
- Different lengths? Then it can't be an anagram.

## 2. Tiny example + edge case

`s = "anagram"`, `t = "nagaram"` → **true** (a×3, n, g, r, m in both).
`s = "rat"`, `t = "car"` → **false** (s has 't', t has 'c').

Edge cases:
- Different lengths: `"ab"`, `"abc"` → false straight away.
- Same letters, wrong counts: `"aacc"`, `"ccac"` → false (s has two 'a', t has one).

## 3. Brute force + complexity

Sort both strings and compare. Anagrams become identical once sorted. **O(n log n) time, O(1) extra space.**

## 4. Pattern trigger

"Same letters, same counts" → **frequency counting**. Small fixed alphabet (26 letters) → an **array of 26** instead of a hash map.

## 5. Plan before coding

- Lengths differ → return false.
- `int freq[26] = {0}`. For each i: `freq[s[i]-'a']++`, `freq[t[i]-'a']--`.
- Any slot not 0 → false. Otherwise → true.

## 6. Code

See the approaches above.

## 7. Dry run

`s = "rat"`, `t = "car"`

| i | s[i] | freq change | t[i] | freq change | non-zero slots after |
|---|---|---|---|---|---|
| 0 | r | r: +1 | c | c: −1 | c:−1, r:+1 |
| 1 | a | a: +1 | a | a: −1 | c:−1, r:+1 |
| 2 | t | t: +1 | r | r: −1 | c:−1, t:+1 |

Check loop: a = 0 ✓, b = 0 ✓, **c = −1 ≠ 0 → return false**. (t has an extra 'c'.)

`"anagram"` / `"nagaram"`: every +1 meets a −1 for the same letter, all 26 slots end at 0 → **true**.

## 8. Final complexity + extension

**O(n) time, O(1) space** (26 ints, whatever n is).

Extensions:
- **Unicode follow-up:** swap `freq[26]` for an `unordered_map` of counts (see the hash map approach).
- **LC 49 Group Anagrams:** use the 26 counts (or the sorted string) as a key to group words.

## What confused me / what clicked

- `s[i] - 'a'` turns a letter into its slot: 'a' → 0 … 'z' → 25.
- **One array, +1 and −1**, is enough: "same letters" becomes "everything is 0".
- A positive slot = extra in s, a negative slot = extra in t.
- The length check isn't just a shortcut: the loop runs over `s.length()`, so equal lengths keep `t[i]` in range.
