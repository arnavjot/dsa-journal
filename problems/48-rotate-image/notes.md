## 1. Restate + clarify

Rotate an n × n matrix 90° clockwise, in place (no second matrix).

## 2. Tiny example + edge case

[[1,2,3],[4,5,6],[7,8,9]] → **[[7,4,1],[8,5,2],[9,6,3]]**. 1 × 1 stays the same.

## 3. Brute force + complexity

Copy into a new matrix with new[j][n−1−i] = old[i][j]: O(n²) time but O(n²) extra space, which isn't allowed.

## 4. Pattern trigger

"Rotate a square matrix in place" → **transpose + reverse each row**.

## 5. Plan before coding

- Transpose: for i < n − 1, for j > i, swap [i][j] and [j][i].
- Reverse each row.

## 6. Code

See the approaches above.

## 7. Dry run

Transpose [[1,2,3],[4,5,6],[7,8,9]] → [[1,4,7],[2,5,8],[3,6,9]]. Reverse rows → **[[7,4,1],[8,5,2],[9,6,3]]**.

## 8. Final complexity + extension

**O(n²) time, O(1) space.** The other in-place method rotates four cells at a time, layer by layer. Counter-clockwise: transpose, then reverse every column.

## What confused me / what clicked

- Transpose maps [i][j] → [j][i]; reversing the row maps column i → n − 1 − i; together that's [j][n − 1 − i], the clockwise rotation.
- j must start at i + 1, or every pair gets swapped back.
