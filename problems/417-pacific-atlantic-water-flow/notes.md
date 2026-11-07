## 1. Restate + clarify

Rain flows from a cell to neighbours with equal or lower height. The Pacific touches the top and left edges, the Atlantic the bottom and right. Return every cell whose water can reach both.

## 2. Tiny example + edge case

Example 1 → [0,4], [1,3], [1,4], [2,2], [3,0], [3,1], [4,0]. [[1]] → [0,0] (touches every edge).

## 3. Brute force + complexity

From every cell, search downhill and check which edges it reaches: **O((m·n)²)**.

## 4. Pattern trigger

"Which cells can reach the edge?" for all cells → **flood from the edges instead** (same trick as Surrounded Regions), here in reverse (uphill).

## 5. Plan before coding

- Two grids: pacific, atlantic.
- DFS from every top/left cell into pacific, moving only to neighbours with height ≥ current.
- Same from every bottom/right cell into atlantic.
- Answer: cells true in both.

## 6. Code

See the approaches above.

## 7. Dry run

3×3 bowl (3 around, 1 in the middle): every edge cell (height 3) is on both oceans' edges or reachable along the rim; the centre (1) is lower than its neighbours, so neither flood can climb **down** into it → not in the answer.

## 8. Final complexity + extension

**O(m·n) time and space.**

Same idea: **LC 130 Surrounded Regions**, **LC 1020 Number of Enclaves**.

## What confused me / what clicked

- Water flows down, so the reverse search climbs up (≥).
- One flood per ocean; the answer is the overlap.
