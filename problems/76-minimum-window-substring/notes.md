## 1. Restate + clarify

Return the shortest substring of `s` that contains every character of `t` **including duplicates**. If none, return `""`.

Questions to ask:
- Case-sensitive? Yes. The answer is unique.
- Lengths up to 10⁵.

## 2. Tiny example + edge case

`s = "ADOBECODEBANC"`, `t = "ABC"` → **"BANC"**.

Edge cases: `"a"`, `"a"` → `"a"`; `"a"`, `"aa"` → `""`.

## 3. Brute force + complexity

From each start, extend until the window covers t: **O(m²)**.

## 4. Pattern trigger

"Shortest substring containing all of …" → **sliding window**: expand until valid, then shrink.

## 5. Plan before coding

- Count t into `freqT`.
- For each right: add s[right]; if `freqS ≤ freqT` for it → found++.
- When `found == t.length()`: while `freqS[s[left]] > freqT[s[left]]` → drop it, left++. Record if shorter.
- Return the best window, or "".

## 6. Code

See the approaches above.

## 7. Dry run

`"ADOBECODEBANC"`, `"ABC"` (windows that get recorded)

| right | window after trimming | length | best |
|---|---|---|---|
| 5 (C) | ADOBEC | 6 | ADOBEC |
| 10 (A) | DOBECODEBA → trimmed to CODEBA | 6 | ADOBEC |
| 12 (C) | trimmed to BANC | **4** | **BANC** |

## 8. Final complexity + extension

**O(m + n) time, O(m + n) space** (O(52) for letters).

Extensions: same skeleton as LC 3 / 424 / 567; **LC 30** (concatenation of all words).

## What confused me / what clicked

- `found` counts only **useful** letters (no extra copies).
- Left drops only letters the window has extra of, so it stays valid and `found` never decreases.
- Record the window after trimming, when it's as short as it can be for this right.
