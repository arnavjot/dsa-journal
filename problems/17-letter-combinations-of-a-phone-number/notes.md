## 1. Restate + clarify

Given digits 2–9, return every letter string they could spell on a phone keypad.

Questions to ask:
- Empty input → empty list. Up to 4 digits.

## 2. Tiny example + edge case

"23" → ad, ae, af, bd, be, bf, cd, ce, cf. "" → []. "2" → a, b, c.

## 3. Brute force + complexity

There's no shortcut: the answer itself has up to 4ⁿ strings of length n → **O(n·4ⁿ)**.

## 4. Pattern trigger

"One choice per position, all combinations" → **recursion / backtracking** (processed + unprocessed).

## 5. Plan before coding

- gen(p, up): up empty → return {p}.
- digit = up[0]; for each letter ch: append gen(p + ch, up.substr(1)) to the list.
- letterCombinations: empty digits → {}; else gen("", digits).

## 6. Code

See the approaches above.

## 7. Dry run

"23": gen("", "23") → 'a' → gen("a", "3") → returns [ad, ae, af] → 'b' → [bd, be, bf] → 'c' → [cd, ce, cf] → 9 strings.

## 8. Final complexity + extension

**O(n·4ⁿ) time and output.**

Same pattern: **LC 78 Subsets**, **LC 46 Permutations**; a queue (BFS) can build the list level by level too.

## What confused me / what clicked

- p = done, up = to do: the recursion moves one digit from up into p.
- Returning lists means no shared state, so nothing to undo.
- Handle "" separately (it should give [], not [""]).
