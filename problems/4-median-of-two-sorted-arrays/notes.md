## 1. Restate + clarify

Two sorted arrays, sizes m and n. Return the **median** of all m + n numbers in **O(log(m + n))**.

Questions to ask:
- One array can be empty (not both). Even total → average of the two middle values (as a double).

## 2. Tiny example + edge case

`[1,3] + [2]` → **2.0**. `[1,2] + [3,4]` → **2.5**.
Edge cases: `[] + [1,2,3,4]` → 2.5; all of one array before the other: `[1,2,3] + [7,8,9,10]` → 7.0.

## 3. Brute force + complexity

Merge, take the middle: **O(m + n)** time (O(1) space if you only walk to the middle).

## 4. Pattern trigger

"Sorted arrays + log time" but no single sorted list to search → **binary search on the answer's structure**: the position of the **cut** in the shorter array.

## 5. Plan before coding

- Make nums1 the shorter one (swap by calling again).
- leftSize = (m + n + 1) / 2. Search i in 0…m; j = leftSize − i.
- left1 = nums1[i − 1], right1 = nums1[i], left2 = nums2[j − 1], right2 = nums2[j] (−∞ / +∞ when off the end).
- left1 <= right2 && left2 <= right1 → found:
  - odd → max(left1, left2); even → (max(left1, left2) + min(right1, right2)) / 2.0.
- left1 > right2 → right = i − 1 (fewer from nums1); else left = i + 1.

## 6. Code

See the approaches above.

## 7. Dry run

`[1,3,8,9,15] + [7,11,18,19,21,25]`: m = 5, n = 6, leftSize = 6

| left | right | i | j | left1 | right1 | left2 | right2 | result |
|---|---|---|---|---|---|---|---|---|
| 0 | 5 | 2 | 4 | 3 | 8 | 19 | 21 | left2 > right1 → left = 3 |
| 3 | 5 | 4 | 2 | 9 | 15 | 11 | 18 | ok, odd → max(9, 11) = **11** |

## 8. Final complexity + extension

**O(log min(m, n)) time, O(1) space.**

Extension: **k-th smallest of two sorted arrays**: same cut idea with leftSize = k.

## What confused me / what clicked

- You binary search **where to cut**, not a value.
- Only the two **cross** comparisons matter; each array is already sorted inside.
- `(double)` before adding avoids int overflow and integer division.
- INT_MIN / INT_MAX stand in for "nothing on this side", so the checks still work at the edges.
