## 1. Restate + clarify

Return the k-th largest element in the array (duplicates count: it's the k-th in sorted order, not the k-th distinct). Can you do it without sorting?

## 2. Tiny example + edge case

[3,2,1,5,6,4], k = 2 → **5**. [3,2,3,1,2,4,5,5,6], k = 4 → **4**. k = 1 → the maximum.

## 3. Brute force + complexity

Sort and take nums[n − k]: **O(n log n)**.

## 4. Pattern trigger

"k-th largest / top k" → **min-heap of size k** (or quickselect).

## 5. Plan before coding

- Push the first k numbers.
- For each later number: if it's bigger than the top, pop the top and push it.
- Return the top.

## 6. Code

See the approaches above.

## 7. Dry run

[3,2,1,5,6,4], k = 2: heap {2,3} → 1 skip → 5 > 2: {3,5} → 6 > 3: {5,6} → 4 ≤ 5 skip → top **5**.

## 8. Final complexity + extension

**O(n log k) time, O(k) space.** Quickselect: O(n) average, O(n²) worst.

Related: **LC 703** (same heap, but for a stream), **LC 347**, **LC 973**.

## What confused me / what clicked

- k-th **largest** → keep the k largest → their minimum → **min**-heap.
- Only replace the top when the new number is bigger.
