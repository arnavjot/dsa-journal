## 1. Restate + clarify

Houses in a row with money nums[i]. You can't rob two neighbours. Return the most money. n ≥ 1, amounts ≥ 0.

## 2. Tiny example + edge case

[2,7,9,3,1] → 2 + 9 + 1 = **12**. [2,1,1,2] → 2 + 2 = **4** (skips two houses in a row, so "every other house" is not enough). [5] → 5.

## 3. Brute force + complexity

Try every subset with no two neighbours: O(2ⁿ). Plain recursion (rob or skip each house) is the same O(2ⁿ).

## 4. Pattern trigger

"Pick or skip each item, maximise, with a rule about neighbours" → **1-D DP**.

## 5. Plan before coding

- best(i) = most money from houses i onwards.
- best(i) = max(nums[i] + best(i + 2), best(i + 1)); best(n) = best(n + 1) = 0.
- Fill from the right. Only the next two values are used → next1, next2.

## 6. Code

See the approaches above.

## 7. Dry run

[1,2,3,1], from the right:

| i | rob: nums[i] + next2 | skip: next1 | best |
|---|---|---|---|
| 3 | 1 + 0 = 1 | 0 | 1 |
| 2 | 3 + 0 = 3 | 1 | 3 |
| 1 | 2 + 1 = 3 | 3 | 3 |
| 0 | 1 + 3 = 4 | 3 | **4** |

## 8. Final complexity + extension

**O(n) time, O(1) space** (two variables). Memo and tabulation are O(n) space.

Extension: **LC 213 House Robber II** (houses in a circle: run this twice, without the first house and without the last). LC 337 (houses on a tree).

## What confused me / what clicked

- Rob → i + 2, skip → i + 1. That's the whole recurrence.
- The commented memo version stops *at* the last house, so it needs the extra `index + 2 < n` check; stopping one past the end with `return 0` avoids it.
- Two variables = the tabulation with only the last two cells kept.
