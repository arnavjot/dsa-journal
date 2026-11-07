## 1. Restate + clarify

`tokens` is a valid expression in **Reverse Polish Notation**: each operator (`+ - * /`) comes after its two operands. Return the integer result. Division truncates toward zero.

Questions to ask:
- Always valid? Yes, no division by zero.
- Number range? Fits in a 32-bit int, including every intermediate result.
- Up to 10⁴ tokens.

## 2. Tiny example + edge case

`["2","1","+","3","*"]` → (2 + 1) × 3 = **9**.
`["4","13","5","/","+"]` → 4 + 13 / 5 = 4 + 2 = **6**.

Edge cases:
- `["4","2","-"]` → **2**. Order matters: it's a − b with b popped first.
- `["7","-3","/"]` → **−2** (truncates toward zero, not −3).
- A single number: `["5"]` → 5.

## 3. Brute force + complexity

There's no real brute force. An alternative is recursion from the last token: **O(n) time, O(n) call stack**.

## 4. Pattern trigger

"Operator applies to the two most recent values" → **stack**.

## 5. Plan before coding

- For each token:
  - Number → `push(stoi(token))`.
  - Operator → `b = pop`, `a = pop`, `push(a op b)`.
- Return `top`.

## 6. Code

See the approaches above.

## 7. Dry run

`["4","13","5","/","+"]`

| token | action | stack after (bottom → top) |
|---|---|---|
| 4 | push | 4 |
| 13 | push | 4 13 |
| 5 | push | 4 13 5 |
| / | b = 5, a = 13, push 13 / 5 = 2 | 4 2 |
| + | b = 2, a = 4, push 4 + 2 = 6 | 6 |

Return **6**.

## 8. Final complexity + extension

**O(n) time, O(n) space.**

Extensions:
- **LC 224 / 227 Basic Calculator**: evaluate normal (infix) expressions with a stack, or convert to RPN first (shunting-yard).

## What confused me / what clicked

- **b is popped first** because the right operand was pushed last. a − b and a / b depend on it.
- C++ `/` on ints truncates toward zero: 7 / −3 = −2.
- Every operator turns two numbers into one, so a valid expression leaves exactly one number.
- `stoi` handles negative numbers like `"-11"`; only a token that is exactly `"-"` is the operator.
