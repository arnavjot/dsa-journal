## 1. Restate + clarify

Coins of given values, unlimited of each. Return the fewest coins that add up to amount, or -1 if impossible. amount = 0 → 0.

## 2. Tiny example + edge case

[1,2,5], 11 → **3** (5 + 5 + 1). [2], 3 → **-1**. [1], 0 → **0**. [1,3,4], 6 → **2** (3 + 3), but greedy says 3 (4 + 1 + 1).

## 3. Brute force + complexity

Try every coin as the next coin, recursively: exponential (about k^(amount / smallest coin)).

## 4. Pattern trigger

"Fewest items to reach a total, each item reusable" → **unbounded knapsack DP** over the amount.

## 5. Plan before coding

- dp[0] = 0.
- dp[i] = 1 + min(dp[i − coin]) over coins ≤ i whose dp isn't INT_MAX; otherwise INT_MAX.
- Answer dp[amount], or -1 if it is INT_MAX.

## 6. Code

See the approaches above.

## 7. Dry run

[1,3,4], 6:

| i | 0 | 1 | 2 | 3 | 4 | 5 | 6 |
|---|---|---|---|---|---|---|---|
| dp | 0 | 1 | 2 | 1 | 1 | 2 | **2** |

dp[6] = 1 + min(dp[5], dp[3], dp[2]) = 1 + 1 = 2.

## 8. Final complexity + extension

**O(amount × k) time, O(amount) space.**

Extension: **LC 518 Coin Change II** counts the *number of ways* instead (loop coins outside amounts so each combination is counted once). BFS over amounts also finds the fewest coins.

## What confused me / what clicked

- Greedy fails; the DP tries every coin as the last one.
- INT_MAX = "can't make this"; check it before 1 + temp, or it overflows.
- The commented `amount < 0` base case isn't needed because I only recurse when coin ≤ amount.
