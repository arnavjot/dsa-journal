## 1. Restate + clarify

digits is a large number, most significant digit first. Return the digits of that number plus one.

## 2. Tiny example + edge case

[1,2,3] → **[1,2,4]**. [4,3,2,1] → **[4,3,2,2]**. [9] → **[1,0]**.

## 3. Brute force + complexity

Turning it into an int overflows: up to 100 digits.

## 4. Pattern trigger

"Add to a number stored as digits" → **carry from the end**.

## 5. Plan before coding

- For i from the last digit down: if digits[i] < 9 → ++, return.
- Else digits[i] = 0.
- After the loop: insert 1 at the front.

## 6. Code

See the approaches above.

## 7. Dry run

[1,9,9]: 9 → 0, 9 → 0, 1 → 2 → **[2,0,0]**.

## 8. Final complexity + extension

**O(n) time, O(1) extra space.** Related: LC 67 Add Binary, LC 989 Add to Array-Form of Integer, LC 43 Multiply Strings.

## What confused me / what clicked

- Stop as soon as there's no carry.
- Only all 9s makes the number longer.
- I didn't paste code for this one; it's mine.
