## 1. Restate + clarify

Put '+' or '−' before every number. Count the expressions that evaluate to target.

## 2. Tiny example + edge case

[1,1,1,1,1], 3 → **5**. [1], 1 → **1**. [0,1,2], 3 → **2** (the 0 can take either sign).

## 3. Brute force + complexity

Try every sign assignment: O(2ⁿ).

## 4. Pattern trigger

"Choose + or − for each" → **count subsets with sum (total + target) / 2**.

## 5. Plan before coding

- total = sum; if |target| > total or (total + target) odd → 0.
- P = (total + target) / 2; dp[0] = 1.
- For each x: for s = P down to x: dp[s] += dp[s − x].

## 6. Code

See the approaches above.

## 7. Dry run

[0,1,2], target 3 → P = 3.

- x = 0 doubles dp[0] to 2.
- x = 1: dp[1] = 2.
- x = 2: dp[3] = dp[1] = 2, dp[2] = 2.

Answer **2** (+0+1+2 and −0+1+2).

## 8. Final complexity + extension

**O(n × P) time, O(P) space.** Related: LC 416 Partition Equal Subset Sum, LC 1049 Last Stone Weight II.

## What confused me / what clicked

- Choosing signs is choosing the '+' subset.
- The parity and range checks make P a valid whole number.
- I didn't paste code for this one; it's mine.
