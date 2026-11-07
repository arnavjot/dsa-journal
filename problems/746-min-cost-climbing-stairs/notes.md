## 1. Restate + clarify

cost[i] is paid when you step on stair i. You can start at step 0 or 1 and climb 1 or 2 steps. Return the minimum cost to reach the top (one past the last step).

## 2. Tiny example + edge case

[10,15,20] → **15** (start on 1, jump to the top). [1,100,1,1,1,100,1,1,100,1] → **6**.

## 3. Brute force + complexity

Plain recursion: **O(2ⁿ)**.

## 4. Pattern trigger

"Cheapest way, each choice from the last one or two" → **1-D DP**.

## 5. Plan before coding

- dp[0] = cost[0], dp[1] = cost[1].
- dp[i] = cost[i] + min(dp[i − 1], dp[i − 2]).
- Answer: min(dp[n − 1], dp[n − 2]).

## 6. Code

See the approaches above.

## 7. Dry run

[10,15,20]: dp = 10, 15, 20 + min(15, 10) = 30 → top = min(30, 15) = **15**.

## 8. Final complexity + extension

**O(n) time; O(1) space with two variables** (your tabulation is O(n) space).

Related: **LC 70 Climbing Stairs**, **LC 198 House Robber**.

## What confused me / what clicked

- dp[i] includes paying cost[i].
- The top is past the end: take the cheaper of the last two.
- Recursion (2ⁿ) → memo (n) → table (n space) → two variables (1 space).
