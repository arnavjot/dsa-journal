## 1. Restate + clarify

Each turn, smash the two heaviest stones: equal → both gone; otherwise the smaller is gone and the larger becomes their difference. Return the last stone's weight, or 0.

## 2. Tiny example + edge case

[2,7,4,1,8,1] → **1**. [1] → 1. [2,2] → 0.

## 3. Brute force + complexity

Sort every turn and take the last two: **O(n² log n)**.

## 4. Pattern trigger

"Repeatedly take the largest" → **max-heap**.

## 5. Plan before coding

- Push all stones into a max-heap.
- While size > 1: pop first, pop second; if different, push first − second.
- Return the top, or 0 if empty.

## 6. Code

See the approaches above.

## 7. Dry run

[2,7,4,1,8,1]: 8,7 → 1 · 4,2 → 2 · 2,1 → 1 · 1,1 → gone · one stone (1) left → **1**.

## 8. Final complexity + extension

**O(n log n) time, O(n) space.**

Related: **LC 703**, **LC 215**, **LC 1049 Last Stone Weight II** (a DP problem in disguise).

## What confused me / what clicked

- `priority_queue<int>` is already a max-heap in C++.
- Equal stones push nothing back.
