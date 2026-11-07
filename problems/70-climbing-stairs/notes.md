## 1. Restate + clarify

You can climb 1 or 2 steps at a time. How many distinct ways to reach step n?

## 2. Tiny example + edge case

n = 2 → 2 (1+1, 2). n = 3 → 3. n = 1 → 1.

## 3. Brute force + complexity

Plain recursion ways(n) = ways(n − 1) + ways(n − 2): about **O(2ⁿ)** calls (the same values recomputed).

## 4. Pattern trigger

"Count ways, where each answer builds on smaller ones" → **1-D DP** (Fibonacci).

## 5. Plan before coding

- ways(1) = 1, ways(2) = 2.
- ways(i) = ways(i − 1) + ways(i − 2).
- Keep prev2, prev1; slide forward to n.

## 6. Code

See the approaches above.

## 7. Dry run

n = 5: 1, 2 → 3 → 5 → **8**.

## 8. Final complexity + extension

**O(n) time, O(1) space.** Memo/table: O(n) space.

Extensions: **LC 746 Min Cost Climbing Stairs**, steps of 1, 2 or 3 (sum of the last three), **LC 509 Fibonacci**.

## What confused me / what clicked

- Look at the **last move**: from i − 1 or i − 2.
- Recursion → memo → table → two variables: same recurrence, less and less work/space.
