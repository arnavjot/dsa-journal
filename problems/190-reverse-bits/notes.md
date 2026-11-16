## 1. Restate + clarify

Reverse the bits of a 32-bit unsigned integer.

## 2. Tiny example + edge case

43261596 (00000010100101000001111010011100) → **964176192** (00111001011110000010100101000000). 1 → **2147483648**.

## 3. Brute force + complexity

Turn it into a 32-character string, reverse it, parse it: O(32) too, just clumsier.

## 4. Pattern trigger

"Reverse bits" → **move bits one at a time: n >> 1 out, ans << 1 in**.

## 5. Plan before coding

- ans = 0.
- 32 times: ans = (ans << 1) | (n & 1); n >>= 1.
- Return ans.

## 6. Code

See the approaches above.

## 7. Dry run

n = 6 (…0110), the first 3 steps:

- Bit 0 is 0 → ans = 0.
- Bit 1 is 1 → ans = 1.
- Bit 2 is 1 → ans = 11 (binary).

The remaining 29 shifts move 011 to the top → **0110000…0**.

## 8. Final complexity + extension

**O(1) time and space (32 steps).** Follow-up: if it's called many times, cache the reverse of each byte and combine four lookups; or swap halves, then quarters, and so on with masks.

## What confused me / what clicked

- Use unsigned so right shifts bring in 0s.
- Every one of the 32 positions matters, including the leading zeros.
- I didn't paste code for this one; it's mine.
