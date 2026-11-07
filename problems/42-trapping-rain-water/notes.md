## 1. Restate + clarify

Bars of width 1 with `height[i]`. How much rain water is trapped between them?

Questions to ask:
- Heights ≥ 0; up to 2·10⁴ bars.
- Edges hold nothing (no wall outside).

## 2. Tiny example + edge case

`[0,1,0,2,1,0,1,3,2,1,2,1]` → **6**. `[4,2,0,3,2,5]` → **9**.

Edge case: rising `[1,2,3,4]` → 0.

## 3. Brute force + complexity

For each bar, scan both ways for the tallest: **O(n²)**. Prefix/suffix max arrays: **O(n) time, O(n) space**.

## 4. Pattern trigger

"Each position is limited by the smaller of two maxes" → **two pointers moving the lower side**.

## 5. Plan before coding

- left, right at the ends; leftMax = rightMax = 0.
- If `height[left] <= height[right]`: new leftMax, or add `leftMax − height[left]`; left++.
- Else the same on the right; right−−.

## 6. Code

See the approaches above.

## 7. Dry run

`[4,2,0,3,2,5]`

| left, right | side | action | water |
|---|---|---|---|
| 0, 5 | left (4 ≤ 5) | leftMax = 4 | 0 |
| 1, 5 | left | +4 − 2 = 2 | 2 |
| 2, 5 | left | +4 − 0 = 4 | 6 |
| 3, 5 | left | +4 − 3 = 1 | 7 |
| 4, 5 | left | +4 − 2 = 2 | **9** |

## 8. Final complexity + extension

**O(n) time, O(1) space.**

Extensions: monotonic-stack version (fills water layer by layer); **LC 407** (2D, uses a heap).

## What confused me / what clicked

- Water at i = min(maxLeft, maxRight) − height[i].
- Working on the **lower** side means the other side's wall is guaranteed tall enough.
- A bar taller than the current max just becomes the new max (no water on it).
