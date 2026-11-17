## 1. Restate + clarify

Count the combinations of coins (unlimited of each) that add up to amount. Order doesn't matter.

## 2. Tiny example + edge case

5, [1,2,5] → **4**. 3, [2] → **0**. 10, [10] → **1**. amount 0 → **1**.

## 3. Brute force + complexity

Recursion over how many of each coin: exponential.

## 4. Pattern trigger

"Number of ways, unlimited items, order doesn't matter" → **unbounded knapsack, coins outside**.

## 5. Plan before coding

- dp[0] = 1.
- For each coin: for a = coin..amount: dp[a] += dp[a − coin].
- Return dp[amount].

## 6. Code

See the approaches above.

## 7. Dry run

5 with [1,2,5]:

- After coin 1: dp = [1,1,1,1,1,1].
- After coin 2: [1,1,2,2,3,3].
- After coin 5: dp[5] = 3 + 1 = **4**.

## 8. Final complexity + extension

**O(coins × amount) time, O(amount) space.** Related: LC 322 Coin Change (fewest coins), LC 377 Combination Sum IV (orders count).

## What confused me / what clicked

- Coins outside = combinations; amounts outside = permutations.
- Going up allows reusing a coin; going down (as in 0/1 knapsack) wouldn't.
- In C++ the middle values can overflow an int even when the answer fits, so I used unsigned.
- I didn't paste code for this one; it's mine.
