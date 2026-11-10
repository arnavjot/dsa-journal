## 1. Restate + clarify

Can the array be split into two groups with equal sums? All numbers are positive (1..100), n ≤ 200.

## 2. Tiny example + edge case

[1,5,11,5] → **true** (1 + 5 + 5 = 11). [1,2,3,5] → **false** (total 11 is odd). [2,2,3,5] → **false** (total 12, but no subset makes 6).

## 3. Brute force + complexity

Every subset: O(2ⁿ). The take/skip recursion is the same.

## 4. Pattern trigger

"Split into two equal sums" → **subset sum to total / 2** → 0/1 knapsack DP over (index, sum).

## 5. Plan before coding

- total odd → false. target = total / 2.
- dp[index][sum] = true if the numbers from index on can bring sum to target.
- dp[·][target] = true; dp[index][sum] = dp[index + 1][sum + arr[index]] (if it fits) || dp[index + 1][sum].
- Answer dp[0][0]; keep only two rows.

## 6. Code

See the approaches above.

## 7. Dry run

[1,2,3], target 3. Rows from the last number up (T = can still reach 3):

| index | sum 0 | 1 | 2 | 3 |
|---|---|---|---|---|
| 3 (none left) | F | F | F | T |
| 2 (number 3) | **T** | F | F | T |
| 1 (number 2) | T | T | F | T |
| 0 (number 1) | **T** | T | T | T |

dp[0][0] = **true** (1 + 2, or just 3).

## 8. Final complexity + extension

**O(n × target) time, O(target) space.**

Extension: one row is enough if sum goes from target **down** to 0 (each number used at most once). A `bitset` (`bits |= bits << x`) does the same in O(n × target / 64). Related: LC 494 Target Sum, LC 1049 Last Stone Weight II.

## What confused me / what clicked

- Equal halves = one subset hitting total / 2.
- Odd total → false immediately.
- My recursion checks `index >= size` before `sum == target`, so it never sees a sum finished by the very last number. It's still right: the numbers left out also add up to target, and that subset is finished earlier.
- Two rows because each row only reads the one below.
