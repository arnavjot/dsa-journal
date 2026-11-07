## 1. Restate + clarify

Return the area (number of cells) of the largest island of 1s connected up/down/left/right, or 0.

## 2. Tiny example + edge case

Example 1 → **6**. All water → 0. 11 / 10 → 3.

## 3. Brute force + complexity

Flood fill is already **O(m·n)**; nothing faster is needed.

## 4. Pattern trigger

"Size of the biggest connected group" → **flood fill that returns a count**.

## 5. Plan before coding

- dfs(r, c): off grid or 0 → 0.
- Set grid[r][c] = 0; area = 1 + dfs of the 4 neighbours.
- For each 1 in the scan: maxArea = max(maxArea, dfs(r, c)).

## 6. Code

See the approaches above.

## 7. Dry run

11 / 10: dfs(0,0) sinks it → right (0,1) sinks (returns 1) → down (1,0) sinks (returns 1) → total 1 + 1 + 1 = **3**.

## 8. Final complexity + extension

**O(m·n) time; O(m·n) recursion in the worst case.**

Related: **LC 200 Number of Islands**, **LC 463 Island Perimeter**, **LC 827 Making A Large Island**.

## What confused me / what clicked

- Return the size from the DFS: 1 + what the neighbours return.
- Sink before recursing so nothing is counted twice.
