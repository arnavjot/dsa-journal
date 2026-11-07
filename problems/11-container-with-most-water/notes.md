## 1. Restate + clarify

Pick two lines; the water they hold is `(j − i) × min(height[i], height[j])`. Return the maximum.

Questions to ask:
- At least 2 lines; heights ≥ 0; up to 10⁵ lines.

## 2. Tiny example + edge case

`[1,8,6,2,5,4,8,3,7]` → lines 1 and 8 (heights 8 and 7, 7 apart) → **49**.

Edge case: `[1,1]` → 1.

## 3. Brute force + complexity

Every pair: **O(n²)**.

## 4. Pattern trigger

"Best pair from both ends, limited by the smaller" → **two pointers, move the limiting side**.

## 5. Plan before coding

- left = 0, right = n − 1, ans = 0.
- Loop: ans = max(ans, width × min height); move the shorter side inward.

## 6. Code

See the approaches above.

## 7. Dry run

`[1,8,6,2,5,4,8,3,7]`

| left, right | area | move |
|---|---|---|
| 0, 8 | 8 × 1 = 8 | left (1 < 7) |
| 1, 8 | 7 × 7 = **49** | right (7 < 8) |
| 1, 7 | 6 × 3 = 18 | right |
| 1, 6 | 5 × 8 = 40 | left (tie) |
| … | ≤ 49 | … |

## 8. Final complexity + extension

**O(n) time, O(1) space.**

Extension: **LC 42 Trapping Rain Water** (water above every bar, not just one container).

## What confused me / what clicked

- The shorter line caps the height; moving the taller one can only shrink the width without raising the cap.
- Ties: moving either side is fine.
- `left <= right` checks a width-0 case at the end; `left < right` would skip it.
