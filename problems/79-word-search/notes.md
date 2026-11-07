## 1. Restate + clarify

Return true if `word` can be traced on the grid through horizontally or vertically adjacent cells, using each cell at most once.

Questions to ask:
- No diagonals. Up to 6×6 grid, word up to 15 letters.

## 2. Tiny example + edge case

Board `ABCE / SFCS / ADEE`: ABCCED → **true**, SEE → **true**, ABCB → **false** (it would need the same B twice).

## 3. Brute force + complexity

There's no shortcut: try every start, explore paths. That *is* the backtracking solution: **O(m·n · 3^L)**.

## 4. Pattern trigger

"Path on a grid, each cell once" → **DFS + backtracking** (mark, recurse, unmark).

## 5. Plan before coding

- For every cell: dfs(i, j, 0).
- dfs: out of bounds → false; letter ≠ word[index] → false; last letter → true.
- Mark #, try down / up / right / left with index + 1, restore, return the result.

## 6. Code

See the approaches above.

## 7. Dry run

ABCCED: A(0,0) → B(0,1) → C(0,2) → C(1,2) → E(2,2) → D(2,1) → **true**. Each step only goes on when the letter matches.

## 8. Final complexity + extension

**O(m·n · 3^L) time, O(L) recursion.**

Pruning ideas: return false early if the board doesn't have enough of some letter; start from the end of the word if its last letter is rarer.
Extension: **LC 212 Word Search II** (many words → trie).

## What confused me / what clicked

- Mark with `#` so the path can't step back onto itself.
- Restore afterwards: backtracking means leaving the board as you found it.
- `||` stops trying directions once one works.
