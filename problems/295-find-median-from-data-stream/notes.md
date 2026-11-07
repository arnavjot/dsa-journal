## 1. Restate + clarify

Support `addNum(num)` and `findMedian()` over a growing stream. Median of an even count = average of the two middle numbers.

Questions to ask:
- Numbers can repeat and be negative. findMedian is only called after at least one add.

## 2. Tiny example + edge case

add 1, add 2 → 1.5; add 3 → 2. add 5, 15, 1, 3 → 4.0.

## 3. Brute force + complexity

Keep a sorted array (insert in place): **addNum O(n)**, findMedian O(1).

## 4. Pattern trigger

"Running median" → **two heaps**: max-heap for the smaller half, min-heap for the bigger half.

## 5. Plan before coding

- Sizes equal: num > median → mini, median = mini.top(); else → maxi, median = maxi.top().
- maxi bigger: num > median → mini; else move maxi.top() to mini, push num to maxi. median = average of tops.
- mini bigger: mirror image. median = average of tops.

## 6. Code

See the approaches above.

## 7. Dry run

add 5 → maxi {5}, median 5. add 15 → mini {15}, median 10. add 1 → equal sizes, 1 ≤ 10 → maxi {5,1}, median 5. add 3 → maxi bigger, 3 ≤ 5 → move 5 to mini, maxi {3,1}, mini {5,15}, median (3 + 5) / 2 = **4**.

## 8. Final complexity + extension

**addNum O(log n), findMedian O(1), O(n) space.**

Follow-up: values in 0..100 → keep a count array and walk it. Related: **LC 480 Sliding Window Median**.

## What confused me / what clicked

- The median only needs the **two middle** numbers: the two heap tops.
- Balance by moving one top across, never more.
- Divide by `2.0` so the average isn't rounded down.
