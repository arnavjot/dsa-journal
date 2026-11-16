## 1. Restate + clarify

Return all elements of an m × n matrix in clockwise spiral order, starting at the top-left. m and n are 1 to 10, so the matrix can be a single row or column.

## 2. Tiny example + edge case

[[1,2,3],[4,5,6],[7,8,9]] → **1,2,3,6,9,8,7,4,5**. [[1,2,3,4],[5,6,7,8],[9,10,11,12]] → **1,2,3,4,8,12,11,10,9,5,6,7**. One column [[1],[2],[3]] → **1,2,3**.

## 3. Brute force + complexity

Walk with a direction and a visited grid, turning right when the next cell is out of bounds or already visited: O(m × n) time but O(m × n) extra space.

## 4. Pattern trigger

"Spiral / layer-by-layer traversal of a matrix" → **four shrinking boundaries**.

## 5. Plan before coding

- startrow, endrow, startcol, endcol; count and total = m × n.
- While count < total:
  - top row → startrow++;
  - right column → endcol--;
  - bottom row backwards → endrow--;
  - left column upwards → startcol++.
- Guard every loop with count < total.

## 6. Code

See the approaches above.

## 7. Dry run

3 × 4, first lap:

- Right: 1, 2, 3, 4 → startrow = 1.
- Down: 8, 12 → endcol = 2.
- Left: 11, 10, 9 → endrow = 1.
- Up: 5 → startcol = 1.

Second lap: right gives 6, 7, and now count = 12 = total, so the other loops run zero times.

Result: **1,2,3,4,8,12,11,10,9,5,6,7**.

## 8. Final complexity + extension

**O(m × n) time, O(1) extra space.** Related: LC 59 Spiral Matrix II (fill 1..n² in spiral order, same loops), LC 885 Spiral Matrix III, LC 48 Rotate Image (also works layer by layer).

## What confused me / what clicked

- Four sides per lap; shrink the boundary right after its side is printed.
- Without `count < total` in the inner loops, the last single row or column gets printed again (e.g. 3 × 4: after 6, 7 the left loop would print 6 a second time).
- My erase version also works, but erasing from the front of a vector shifts everything, and it wipes out the input matrix.
