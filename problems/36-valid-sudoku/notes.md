## 1. Restate + clarify

Check that each filled cell's digit is unique in its row, column and 3×3 box. Empty cells are `.`. The board doesn't need to be solvable.

## 2. Tiny example + edge case

Example 1 → **true**. Example 2 (top-left changed to 8) → **false**: column 0 has two 8s.

Edge case: a nearly empty board is valid.

## 3. Brute force + complexity

Check rows, then columns, then boxes in three passes: still O(81).

## 4. Pattern trigger

"Is this value already present in its group?" → **hash sets per group**.

## 5. Plan before coding

- 27 sets: `rows[9]`, `cols[9]`, `boxes[9]`.
- For each filled cell: `box = (i/3)*3 + j/3`; if the digit is in any of the three sets → false; else insert into all three.
- Return true.

## 6. Code

See the approaches above.

## 7. Dry run

Example 2: row 0 starts `8 3 . . 7 …`, so cols[0] gets 8 at (0,0). Later, (3,0) is 8 again → `cols[0].count('8')` → **false**.

## 8. Final complexity + extension

**O(1)**: the board is fixed at 9×9 (81 cells).

Extensions: 9-bit masks instead of sets; **LC 37 Sudoku Solver** (backtracking).

## What confused me / what clicked

- Box index `(i/3)*3 + j/3` numbers boxes 0–8.
- One pass with 27 sets does all three checks at once.
- "Valid" ≠ "solvable".
