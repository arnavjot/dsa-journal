## 1. Restate + clarify

Given an m×n grid of letters and a list of words, return every word that can be formed by moving between horizontally or vertically adjacent cells, using each cell at most once per word.

Questions to ask:
- Words are unique; each found word is returned once. Lowercase letters only.

## 2. Tiny example + edge case

Board `oaan / etae / ihkr / iflv`, words oath, pea, eat, rain → **[oath, eat]**.
Edge case: `ab / cd`, word abcb → **[]** (it would need b twice).

## 3. Brute force + complexity

Run Word Search (LC 79) for each word: **O(W · m·n · 4^L)**.

## 4. Pattern trigger

"Many words on one grid" → **Trie + backtracking DFS**: the trie prunes every path no word continues.

## 5. Plan before coding

- Insert every word; store the word itself at its last node.
- For every cell: dfs(r, c, root).
- dfs: no link for board[r][c] → return. Move to that node; if it holds a word → add it, clear it.
- Mark the cell #, try up / down / left / right (skip # cells), restore the letter.

## 6. Code

See the approaches above.

## 7. Dry run

Example 1, from (0,0) 'o': trie has "o" → right (0,1) 'a': "oa" → down (1,1) 't': "oat" → down (2,1) 'h': "oath" holds a word → **add oath**.
From (1,3) 'e': "e" → left (1,2) 'a': "ea" → left (1,1) 't': "eat" → **add eat**.
Starting cells like 'i', 'h', 'k' stop at once: no word starts with them.

## 8. Final complexity + extension

Worst case **O(m·n · 4·3^(L−1))**; trie **O(total letters)**. In practice the trie cuts most branches.

Extra pruning: remove a trie branch once all its words are found, so later DFS calls stop even sooner.

## What confused me / what clicked

- Walk the grid and the trie **together**: no link = stop right there.
- Store the full word in the node, then clear it after adding.
- `#` marks the current path; restoring it lets other paths use the cell.
