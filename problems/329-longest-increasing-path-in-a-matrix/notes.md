## 1. Restate + clarify

Return the length of the longest strictly increasing path in the matrix, moving up/down/left/right.

## 2. Tiny example + edge case

[[9,9,4],[6,6,8],[2,1,1]] → **4** (1, 2, 6, 9). [[3,4,5],[3,2,6],[2,2,1]] → **4** (3, 4, 5, 6). [[1]] → **1**.

## 3. Brute force + complexity

DFS from every cell without memo: exponential in the worst case.

## 4. Pattern trigger

"Longest increasing path, no cycles possible" → **DFS + memo (DAG longest path)**.

## 5. Plan before coding

- memo all 0.
- dfs(r, c): if memo → return it; best = 1; for each bigger neighbour, best = max(best, 1 + dfs).
- Answer = max over cells.

## 6. Code

See the approaches above.

## 7. Dry run

Example 2: the cell with 3 at (0, 0) → 4 → 5 → 6 gives memo[0][0] = 4 → **4**.

## 8. Final complexity + extension

**O(m × n) time and space.** Related: LC 2328 Number of Increasing Paths in a Grid.

## What confused me / what clicked

- Strictly increasing means no cycles, so memo is safe.
- Each cell's answer depends only on bigger neighbours.
- I didn't paste code for this one; it's mine.
