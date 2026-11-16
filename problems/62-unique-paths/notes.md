## 1. Restate + clarify

A robot starts at the top-left of an m × n grid and moves only right or down. How many different paths reach the bottom-right? 1 ≤ m, n ≤ 100, and the answer is at most 2 × 10⁹.

## 2. Tiny example + edge case

m = 3, n = 2 → **3** (RDD, DRD, DDR). m = 3, n = 7 → **28**. m = 1 or n = 1 → **1** (one straight line).

## 3. Brute force + complexity

Recurse right and down from the start and count arrivals: O(2^(m+n)). Each cell is asked about again and again.

## 4. Pattern trigger

"Count paths in a grid, only right / down" → **2-D DP** paths(r, c) = paths(r + 1, c) + paths(r, c + 1), or the **combination** C(m + n − 2, m − 1).

## 5. Plan before coding

- N = m + n − 2 total steps, r = m − 1 of them down.
- res = 1; for i = 1..r: res = res × (N − r + i) / i.
- After step i, res = C(N − r + i, i), so each step stays a whole number.
- Return (int)res.

## 6. Code

See the approaches above.

## 7. Dry run

m = 3, n = 7: N = 8, r = 2.

| i | N − r + i | res |
|---|---|---|
| start | | 1 |
| 1 | 7 | 1 × 7 / 1 = 7 |
| 2 | 8 | 7 × 8 / 2 = **28** |

## 8. Final complexity + extension

**O(m) time, O(1) space.** Using r = min(m, n) − 1 makes it O(min(m, n)).

The DP versions are O(m × n); one row of size n is enough for tabulation. Extension: LC 63 Unique Paths II (obstacles) breaks the formula, so it needs the DP. Related: LC 64 Minimum Path Sum.

## What confused me / what clicked

- Every path has the same length: n − 1 rights and m − 1 downs. Only their order changes.
- Choosing the positions of the downs fixes the path → C(m + n − 2, m − 1).
- `double` is fine here: every value stays a whole number below 2⁵³, so nothing is rounded.
- In my DP, the first row and first column are all 1, because there is only one straight way to reach them.
- My "from the end" memo checks dp before the base case. It's still correct, because base cells stay −1 and fall through to `return 1`.
