## 1. Restate + clarify

Capture every region of 'O' that is completely surrounded by 'X' (flip it to 'X'). O's connected to the border stay.

## 2. Tiny example + edge case

XXXX / XOOX / XXOX / XOXX → XXXX / XXXX / XXXX / XOXX (the bottom O touches the border). A single cell → unchanged.

## 3. Brute force + complexity

From each O region, search to see if it reaches the border: still O(n·m) if done carefully, but messier.

## 4. Pattern trigger

"Which cells connect to the edge?" → **flood from the border**.

## 5. Plan before coding

- DFS from every border O, marking vis.
- Flip every O that is not in vis.

## 6. Code

See the approaches above.

## 7. Dry run

Example 1: the only border O is (3,1); its DFS marks just itself. The inner O's (1,1), (1,2), (2,2) are unmarked → X.

## 8. Final complexity + extension

**O(n·m) time and space.**

Same trick: **LC 417 Pacific Atlantic Water Flow**, **LC 1020 Number of Enclaves**.

## What confused me / what clicked

- Ask the opposite question: what is NOT surrounded? Start from the border.
- Mark first, flip at the end.
