## 1. Restate + clarify

Multiply two non-negative integers given as strings and return the product as a string, without converting them to integers.

## 2. Tiny example + edge case

"2" × "3" → **"6"**. "123" × "456" → **"56088"**. "0" × "52" → **"0"**.

## 3. Brute force + complexity

Repeated addition: O(value). Hopeless for 200-digit numbers.

## 4. Pattern trigger

"Arithmetic on numbers stored as strings" → **grade-school multiplication, positions i + j and i + j + 1**.

## 5. Plan before coding

- pos of size m + n, all 0.
- For i from m − 1 down, j from n − 1 down: sum = d1 × d2 + pos[i + j + 1]; pos[i + j + 1] = sum % 10; pos[i + j] += sum / 10.
- Skip leading zeros; empty → "0".

## 6. Code

See the approaches above.

## 7. Dry run

99 × 99, places 0..3:

- 9 × 9 = 81 → pos[3] = 1, pos[2] = 8.
- Next 81 + 8 = 89 → pos[2] = 9, pos[1] = 8.
- Next 81 + 9 = 90 → pos[2] = 0, pos[1] = 17.
- Next 81 + 17 = 98 → pos[1] = 8, pos[0] = 9.

Result **9801**.

## 8. Final complexity + extension

**O(m × n) time, O(m + n) space.** Karatsuba is O(n^1.58); FFT is O(n log n). Related: LC 415 Add Strings, LC 66 Plus One, LC 2 Add Two Numbers.

## What confused me / what clicked

- Place i + j + 1 comes from the place values: 10^(m−1−i) × 10^(n−1−j).
- The carry can briefly push pos[i + j] above 9; the next step fixes it.
- I didn't paste code for this one; it's mine.
