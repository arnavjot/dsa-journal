## 1. Restate + clarify

`s` has only `()[]{}`. It's valid if every opener is closed by the **same type**, in the **right order**, and every closer has an opener.

Questions to ask:
- Other characters? No.
- Length? 1 to 10⁴.
- Is an odd length ever valid? No (a quick early exit, optional).

## 2. Tiny example + edge case

`"()[]{}"` → **true**. `"{[()]}"` → **true** (nested).
`"(]"` → **false**. `"([)]"` → **false**: the `)` arrives while `[` is still open.

Edge cases:
- `")("` → false straight away (closer, empty stack).
- `"(()"` → false at the end (one `(` left over).

## 3. Brute force + complexity

Keep deleting adjacent `()`, `[]`, `{}` until nothing changes; valid → empty. **O(n²) time, O(n) space.**

## 4. Pattern trigger

"Match the most recent unmatched opener" → **last in, first out** → **stack**.

## 5. Plan before coding

- For each char:
  - Opener → push.
  - Closer: stack empty → false. Top isn't its partner → false. Else pop.
- After the loop: stack empty → true, else false.

## 6. Code

See the approaches above.

## 7. Dry run

`s = "{[()]}"`

| i | char | action | stack after (bottom → top) |
|---|---|---|---|
| 0 | { | push | { |
| 1 | [ | push | { [ |
| 2 | ( | push | { [ ( |
| 3 | ) | top ( matches → pop | { [ |
| 4 | ] | top [ matches → pop | { |
| 5 | } | top { matches → pop | (empty) |

End: empty → **true**.

`"([)]"`: after `( [`, the `)` meets top `[` → **false**.

## 8. Final complexity + extension

**O(n) time, O(n) space.**

Extensions:
- **LC 32 Longest Valid Parentheses**: push indices instead of chars.
- **LC 22 Generate Parentheses**: build only valid strings with open/close counts.

## What confused me / what clicked

- **Three ways to fail**: wrong partner, closer with an empty stack, openers left at the end.
- Counting brackets isn't enough; order matters, and only a stack tracks order.
- Check `!st.empty()` **before** `st.top()`, or `")"` would crash.
