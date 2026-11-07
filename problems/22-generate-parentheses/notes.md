## 1. Restate + clarify

Given n pairs of parentheses, return every well-formed combination.

Questions to ask:
- 1 ≤ n ≤ 8. Any order is fine.

## 2. Tiny example + edge case

n = 3 → `((()))`, `(()())`, `(())()`, `()(())`, `()()()`. n = 1 → `()`.

## 3. Brute force + complexity

Generate all 2^(2n) strings of `(` and `)`, keep the balanced ones: **O(2^(2n) · n)**.

## 4. Pattern trigger

"Generate all valid strings" → **backtracking that only makes valid moves**.

## 5. Plan before coding

- backtrack(open, close, curr): length 2n → save.
- open < n → recurse with curr + '('.
- close < open → recurse with curr + ')'.

## 6. Code

See the approaches above.

## 7. Dry run

n = 2: "" → "(" → "((" → "(()" → "(())" **save** → back to "(" → "()" → "()(" → "()()" **save**.

## 8. Final complexity + extension

**O(4ⁿ / √n)**: the number of answers (Catalan number) times their length. Recursion **O(n)**.

Related: **LC 20 Valid Parentheses** (checking), **LC 301** (remove invalid parentheses).

## What confused me / what clicked

- Two rules keep every prefix valid: `open < n` and `close < open`.
- So nothing needs checking at the end.
- `curr + '('` passes a new string, so no pop is needed.
