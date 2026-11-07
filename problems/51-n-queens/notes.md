## 1. Restate + clarify

Place n queens on an n×n board so no two attack each other (same row, column or diagonal). Return every board.

Questions to ask:
- 1 ≤ n ≤ 9. n = 2 and 3 have no solutions.

## 2. Tiny example + edge case

n = 4 → 2 boards: [.Q.., ...Q, Q..., ..Q.] and [..Q., Q..., ...Q, .Q..]. n = 1 → [Q].

## 3. Brute force + complexity

Choose n squares out of n² and check: astronomically many. One per column + backtracking cuts it to at most **n!** placements.

## 4. Pattern trigger

"Place items under constraints, undo when stuck" → **backtracking**, with O(1) conflict checks.

## 5. Plan before coding

- solve(col): col == n → store the board.
- for each row: safe if rowCheck[row], diag[col − row], anti[row + col] are all free.
- Place Q, mark all three, solve(col + 1), then remove Q and unmark.

## 6. Code

See the approaches above.

## 7. Dry run

n = 4: col 0 row 0 → col 1 rows 0, 1 attacked, row 2 OK → col 2: every row attacked → back up → col 1 row 3 → col 2 row 1 → col 3: all attacked → back up … eventually col 0 row 1 leads to the first solution.

## 8. Final complexity + extension

**O(n!) time, O(n²) board.**

Extensions: **LC 52 N-Queens II** (count only), **LC 37 Sudoku Solver** (same backtracking with constraint sets).

## What confused me / what clicked

- ↘ diagonal: col − row is constant. ↗ diagonal: row + col is constant.
- One queen per column means no column check is needed.
- Marking and unmarking the maps is the backtracking.
