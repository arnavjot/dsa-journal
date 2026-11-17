## 1. Restate + clarify

Buy and sell a stock as many times as you like, holding at most one share at a time. After selling, you must wait one day before buying again. Find the maximum profit.

## 2. Tiny example + edge case

[1,2,3,0,2] → **3** (buy 1, sell 2, cooldown, buy 0, sell 2). [1] → **0**. Falling prices → **0**.

## 3. Brute force + complexity

Recursion over buy / sell / wait on each day: O(3ⁿ). With memo on (day, holding) it's O(n).

## 4. Pattern trigger

"Buy / sell with rules between actions" → **state-machine DP** (one value per state per day).

## 5. Plan before coding

- hold = −∞, sold = 0, rest = 0.
- Each day p: prevSold = sold; sold = hold + p; hold = max(hold, rest − p); rest = max(rest, prevSold).
- Return max(sold, rest).

## 6. Code

See the approaches above.

## 7. Dry run

[1,2,3,0,2]:

| day | price | hold | sold | rest |
|---|---|---|---|---|
| 0 | 1 | −1 | −∞ | 0 |
| 1 | 2 | −1 | 1 | 0 |
| 2 | 3 | −1 | 2 | 1 |
| 3 | 0 | 1 | −1 | 2 |
| 4 | 2 | 1 | **3** | 2 |

Answer max(3, 2) = **3**.

## 8. Final complexity + extension

**O(n) time, O(1) space.** Related: LC 121, LC 122 (no cooldown: drop the rest state), LC 714 (with a fee: subtract it when selling), LC 123 / 188 (at most k transactions: add a count to the state).

## What confused me / what clicked

- Three states, and each day's values come only from the day before.
- The cooldown just means a buy comes from rest, never straight from sold.
- I didn't paste code for this one; it's mine.
