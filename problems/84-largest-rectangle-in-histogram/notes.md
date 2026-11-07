## 1. Restate + clarify

Bars of width 1 with `heights[i]`. Return the area of the largest rectangle that fits inside the histogram.

Questions to ask:
- Heights can be 0? Yes.
- Size? Up to 10⁵ bars, so O(n²) is too slow.

## 2. Tiny example + edge case

`[2,1,5,6,2,3]` → bars 2 and 3 (heights 5, 6) at height 5 × width 2 = **10**.
`[2,4]` → **4**.

Edge cases:
- Rising `[1,2,3,4,5]` → **9** (3 × 3); nothing pops until the clean-up.
- Equal `[3,3,3]` → **9**.
- A 0 splits the histogram: `[2,0,2]` → 2.

## 3. Brute force + complexity

Every range [i, j], height = its shortest bar. **O(n²) time, O(1) space.**

## 4. Pattern trigger

"For each bar, how far can it stretch before a **shorter** bar?" → previous / next **smaller** element → **monotonic (rising) stack**.

## 5. Plan before coding

- Stack of indices with rising heights; start with index 0.
- For i = 1 … n − 1: while `heights[i] < heights[top]`: pop and measure. Then push i.
- Measure popped: `width = stack empty ? i : i - 1 - top`, `area = heights[popped] * width`.
- After the loop, measure everything left with i = n.

## 6. Code

See the approaches above.

## 7. Dry run

`[2,1,5,6,2,3]`

| i | event | area | best | stack after |
|---|---|---|---|---|
| — | push 0 | | 0 | 0 |
| 1 (h1) | pop 0: h2 × 1 | 2 | 2 | 1 |
| 2, 3 | push | | 2 | 1 2 3 |
| 4 (h2) | pop 3: h6 × 1 | 6 | 6 | 1 2 |
| 4 (h2) | pop 2: h5 × 2 | **10** | **10** | 1 4 |
| 5 | push | | 10 | 1 4 5 |
| end (i = 6) | pop 5: 3 × 1, pop 4: 2 × 4, pop 1: 1 × 6 | 3, 8, 6 | 10 | — |

Return **10**.

## 8. Final complexity + extension

**O(n) time, O(n) space.**

Extension: **LC 85 Maximal Rectangle**: build a histogram for each row of the matrix (heights of consecutive 1s) and run this on each row.

## What confused me / what clicked

- The stack is **rising**, so the bar below a popped bar is its nearest shorter-or-equal bar on the left.
- The bar that causes the pop is the nearest **shorter** bar on the right → right limit `i - 1`.
- Empty stack after popping → nothing shorter on the left → width `i`.
- Final clean-up with `i = n` = pretending there's a height-0 bar at the end.
- My two-pass version (prev smaller + next smaller) finds the same limits with two stacks; the one-pass version does both at the moment of popping.
