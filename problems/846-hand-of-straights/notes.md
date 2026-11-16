## 1. Restate + clarify

Can the cards be split into groups of groupSize consecutive values? Duplicates are allowed.

## 2. Tiny example + edge case

[1,2,3,6,2,3,4,7,8], 3 → **true** ([1,2,3], [2,3,4], [6,7,8]). [1,2,3,4,5], 4 → **false** (5 cards).

## 3. Brute force + complexity

Backtracking over which cards form each group: exponential.

## 4. Pattern trigger

"Partition into consecutive runs" → **greedy from the smallest card + ordered count map**.

## 5. Plan before coding

- If n % k ≠ 0 → false.
- count = map of card → copies.
- While not empty: first = smallest; for x in first..first + k − 1: missing → false; else decrement (erase at 0).
- Return true.

## 6. Code

See the approaches above.

## 7. Dry run

Example 1, counts {1:1, 2:2, 3:2, 4:1, 6:1, 7:1, 8:1}:

- Smallest is 1 → take 1, 2, 3.
- Smallest is 2 → take 2, 3, 4.
- Smallest is 6 → take 6, 7, 8.

The map is empty → **true**.

## 8. Final complexity + extension

**O(n log n) time, O(n) space.** Same problem: LC 1296 Divide Array in Sets of K Consecutive Numbers.

## What confused me / what clicked

- The smallest card leaves no choice, which is what makes the greedy correct.
- An ordered map gives the smallest key in O(log n).
- I didn't paste code for this one; it's mine.
