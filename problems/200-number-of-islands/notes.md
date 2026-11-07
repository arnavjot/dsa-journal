## 1. Restate + clarify

Count groups of '1's connected horizontally or vertically.

Questions to ask:
- Diagonals don't connect. Can the grid be modified? (Decides vis array vs sinking.)

## 2. Tiny example + edge case

Example 2 (11000 / 11000 / 00100 / 00011) → **3**. All water → 0. Checkerboard 101/010/101 → **5**.

## 3. Brute force + complexity

There's nothing slower worth doing: flood fill is already **O(m·n)**.

## 4. Pattern trigger

"Count connected groups on a grid" → **BFS / DFS flood fill** (or Union-Find).

## 5. Plan before coding

- vis array, count = 0.
- For each cell: unvisited '1' → BFS from it (mark on push), count++.
- BFS: pop, check 4 neighbours, push unvisited land.

## 6. Code

See the approaches above.

## 7. Dry run

Example 2: (0,0) → BFS marks (0,0),(0,1),(1,0),(1,1) → count 1. (2,2) → count 2. (3,3) → BFS marks (3,3),(3,4) → count 3.

## 8. Final complexity + extension

**O(m·n) time and space.**

Extensions: **LC 695 Max Area of Island**, **LC 463 Island Perimeter**, **LC 130 Surrounded Regions**, **LC 417 Pacific Atlantic**.

## What confused me / what clicked

- One flood = one island.
- Mark visited when pushing.
- Sinking ('0') replaces the vis array if changing the grid is OK.
