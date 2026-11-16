## 1. Restate + clarify

If an element is 0, set its entire row and column to 0, in place.

## 2. Tiny example + edge case

[[1,1,1],[1,0,1],[1,1,1]] → **[[1,0,1],[0,0,0],[1,0,1]]**. [[0,1,2,0],[3,4,5,2],[1,3,1,5]] → **[[0,0,0,0],[0,4,5,0],[0,3,1,0]]**.

## 3. Brute force + complexity

Copy the matrix and zero from the copy: O(mn) space. Or two sets of zero rows and columns: O(m + n) space.

## 4. Pattern trigger

"Mark rows/columns in place" → **use the first row and column as the marker arrays**.

## 5. Plan before coding

- firstRowZero / firstColZero = whether row 0 / column 0 had a 0.
- For i, j ≥ 1: if 0 → matrix[i][0] = matrix[0][j] = 0.
- For i, j ≥ 1: if matrix[i][0] or matrix[0][j] is 0 → zero the cell.
- Then zero row 0 and/or column 0 if their flags are set.

## 6. Code

See the approaches above.

## 7. Dry run

Example 2: firstRowZero = true (the zeros at (0,0) and (0,3)); firstColZero = true.

The inside has no zeros, so nothing new is marked. Fill: columns 0 and 3 are marked in row 0, so (1,0), (1,3), (2,0) and (2,3) become 0. Then row 0 is zeroed.

Result **[[0,0,0,0],[0,4,5,0],[0,3,1,0]]**.

## 8. Final complexity + extension

**O(m × n) time, O(1) extra space.**

## What confused me / what clicked

- Zeroing straight away spreads wrongly; mark first, then fill.
- The two booleans exist because the header cells are reused as markers.
- I didn't paste code for this one; it's mine.
