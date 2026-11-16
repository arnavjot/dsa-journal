## 1. Restate + clarify

s has '(', ')' and '*'; '*' can be '(', ')' or empty. Is there a choice that makes s a valid bracket string?

## 2. Tiny example + edge case

'()' → **true**. '(*)' → **true**. '(*))' → **true** (* = '('). '(()*((' → **false**.

## 3. Brute force + complexity

Try all 3^k ways to fill the '*'s: exponential. DP over (index, open) is O(n²).

## 4. Pattern trigger

"Wildcards in brackets" → **greedy range [lo, hi] of open count**.

## 5. Plan before coding

- lo = hi = 0.
- For each c: '(' → lo++, hi++; ')' → lo--, hi--; '*' → lo--, hi++.
- If hi < 0 → false; lo = max(lo, 0).
- Return lo == 0.

## 6. Code

See the approaches above.

## 7. Dry run

'(*))':

- '(' → [1, 1].
- '*' → [0, 2].
- ')' → [−1 → 0, 1].
- ')' → [−1 → 0, 0].

lo = 0 → **true**.

## 8. Final complexity + extension

**O(n) time, O(1) space.** Related: LC 20 Valid Parentheses, LC 32 Longest Valid Parentheses, LC 1249 Minimum Remove to Make Valid Parentheses.

## What confused me / what clicked

- Every count between lo and hi is reachable by some choice.
- hi < 0 means too many ')' even at best.
- Clamp lo, because a negative count is never allowed.
- I didn't paste code for this one; it's mine.
