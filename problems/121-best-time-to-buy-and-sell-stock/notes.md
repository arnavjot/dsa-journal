## 1. Restate + clarify

`prices[i]` is the stock price on day i. Buy once, sell once **later**, and return the biggest profit. If no trade makes money, return 0.

Questions to ask:
- Exactly one buy and one sell? Yes (or none).
- Buy before sell? Yes, the sell day must come after the buy day.
- Size? Up to 10⁵ days, so O(n²) is too slow.

## 2. Tiny example + edge case

`[7,1,5,3,6,4]` → buy at 1 (day 1), sell at 6 (day 4) → **5**. Not 7 − 1: the 7 comes before the 1.

Edge cases:
- `[7,6,4,3,1]`: only goes down → **0** (don't trade).
- One day → 0.

## 3. Brute force + complexity

Every buy day i, every sell day j ≥ i, keep the best `prices[j] − prices[i]`. **O(n²) time, O(1) space.** TLE at n = 10⁵.

## 4. Pattern trigger

"Best (later − earlier)" → for each later element you only need the **best earlier element**, which is a running minimum. One pass, keep "min so far" (a greedy / sliding-window style scan).

## 5. Plan before coding

- `mini = INT_MAX`, `profit = 0`.
- For each price: `mini = min(mini, price)`, then `profit = max(profit, price - mini)`.
- Return `profit`.

## 6. Code

See the approaches above.

## 7. Dry run

`prices = [7,1,5,3,6,4]`

| day | price | mini | price − mini | profit |
|---|---|---|---|---|
| 0 | 7 | 7 | 0 | 0 |
| 1 | 1 | **1** | 0 | 0 |
| 2 | 5 | 1 | 4 | 4 |
| 3 | 3 | 1 | 2 | 4 |
| 4 | 6 | 1 | **5** | **5** |
| 5 | 4 | 1 | 3 | 5 |

Return **5** (buy day 1, sell day 4).

`[3,8,1,5]`: profit hits 5 on day 1 (3 → 8). The new low 1 on day 2 only gives 4 on day 3, so the answer stays **5**.

## 8. Final complexity + extension

**O(n) time, O(1) space.**

Extensions:
- **LC 122** (unlimited trades): add every rise, `profit += max(0, prices[i] - prices[i-1])`.
- **LC 123 / 188** (at most 2 / k trades): DP with buy/sell states.

## What confused me / what clicked

- Selling today, the best buy is the **cheapest day so far**. That turns O(n²) into one pass.
- `max − min` of the whole array is wrong when the min comes after the max.
- A new low doesn't erase the best profit; `profit` only goes up.
- Updating `mini` first is safe: on a new-low day the profit is just 0.
