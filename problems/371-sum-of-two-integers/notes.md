## 1. Restate + clarify

Return a + b without using the + or − operators. −1000 ≤ a, b ≤ 1000.

## 2. Tiny example + edge case

1 + 2 → **3**. 2 + 3 → **5**. −2 + 3 → **1**.

## 3. Brute force + complexity

Increment or decrement one at a time: O(|b|), and it still needs ++.

## 4. Pattern trigger

"Add without +" → **XOR for the sum bits, AND << 1 for the carry**.

## 5. Plan before coding

- While b != 0: carry = (a & b) << 1 (on unsigned); a = a ^ b; b = carry.
- Return a.

## 6. Code

See the approaches above.

## 7. Dry run

7 + 1:

| a | b | a ^ b | carry |
|---|---|---|---|
| 0111 | 0001 | 0110 | 0010 |
| 0110 | 0010 | 0100 | 0100 |
| 0100 | 0100 | 0000 | 1000 |
| 0000 | 1000 | **1000** | 0 |

## 8. Final complexity + extension

**O(1) time and space (at most 32 rounds).** Subtraction: a + (~b + 1). Related: LC 67 Add Binary, LC 2 Add Two Numbers (same carry idea).

## What confused me / what clicked

- XOR is addition without carrying; AND finds the columns that carry.
- In C++, shift the carry as unsigned to avoid undefined behaviour.
- For negative numbers the carry runs up to bit 31 and falls off.
- I didn't paste code for this one; it's mine.
