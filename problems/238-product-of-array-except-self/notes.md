## 1. Restate + clarify

Return `answer[i]` = product of all numbers except `nums[i]`, **without division**, in O(n).

Questions to ask:
- Zeros possible? Yes. Products fit in 32 bits (guaranteed).
- Follow-up: O(1) extra space (output array doesn't count).

## 2. Tiny example + edge case

`[1,2,3,4]` → **[24,12,8,6]**.

Edge cases: `[-1,1,0,-3,3]` → [0,0,9,0,0]. One zero → only that index is non-zero.

## 3. Brute force + complexity

For each i, multiply all the others: **O(n²)**.

## 4. Pattern trigger

"Everything except i" → **prefix product × suffix product**.

## 5. Plan before coding

- `res[0] = 1`; `res[i] = res[i-1] * nums[i-1]` (left products).
- `suffix = 1`; from the right: `res[i] *= suffix; suffix *= nums[i]`.

## 6. Code

See the approaches above.

## 7. Dry run

`[1,2,3,4]`

| pass | res |
|---|---|
| after pass 1 (left products) | [1, 1, 2, 6] |
| i = 3, suffix 1 | [1, 1, 2, 6] → suffix 4 |
| i = 2, suffix 4 | [1, 1, 8, 6] → suffix 12 |
| i = 1, suffix 12 | [1, 12, 8, 6] → suffix 24 |
| i = 0, suffix 24 | **[24, 12, 8, 6]** |

## 8. Final complexity + extension

**O(n) time, O(1) extra space.**

Extension: with division allowed, count zeros: two or more → all 0; one → only that index gets the product of the rest.

## What confused me / what clicked

- Answer = left × right. Two sweeps build it.
- Starting values are 1 ("nothing to multiply").
- No division, so zeros are handled naturally.
