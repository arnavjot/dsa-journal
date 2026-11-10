## 1. Restate + clarify

House Robber, but the houses form a circle: house 0 and house n − 1 are neighbours. n ≥ 1, amounts ≥ 0.

## 2. Tiny example + edge case

[2,3,2] → **3** (can't take both 2s, they touch). [1,2,3,1] → 1 + 3 = **4**. [5] → **5** (one house, both ranges would be empty).

## 3. Brute force + complexity

Every subset with no two neighbours, first and last counting as neighbours: O(2ⁿ).

## 4. Pattern trigger

"House Robber in a circle" → break the circle: **run the line version twice**.

## 5. Plan before coding

- n == 1 → nums[0].
- case1 = House Robber on 0..n − 2 (last house left out).
- case2 = House Robber on 1..n − 1 (first house left out).
- Answer max(case1, case2). Any valid plan skips the first or the last house, so it's inside at least one case.

## 6. Code

See the approaches above.

## 7. Dry run

[9,1,1,9]:
- case1 on [9,1,1] → 9 + 1 = **10**
- case2 on [1,1,9] → 1 + 9 = **10**
- answer **10** (robbing both 9s isn't allowed: they're neighbours in the circle).

## 8. Final complexity + extension

**O(n) time, O(1) space** with two variables per case. Your memo version is O(n) space (dp1, dp2 and the stack).

Related: **LC 198 House Robber**, LC 337 House Robber III (tree).

## What confused me / what clicked

- The circle only adds one rule: not both 0 and n − 1. Two cases remove that rule.
- Two separate dp arrays in the memo version, because the cases end at different houses.
- Don't forget n == 1.
