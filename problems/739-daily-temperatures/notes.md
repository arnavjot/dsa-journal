## 1. Restate + clarify

For each day, how many days until a **strictly warmer** day? If none, 0.

Questions to ask:
- Strictly warmer? Yes, an equal temperature doesn't count.
- Size? Up to 10⁵ days, temperatures 30 to 100. O(n²) is too slow.

## 2. Tiny example + edge case

`[73,74,75,71,69,72,76,73]` → **`[1,1,4,2,1,1,0,0]`**.

Edge cases:
- Only rising: `[30,40,50,60]` → `[1,1,1,0]`.
- Falling then hot: `[90,80,70,60,100]` → `[4,3,2,1,0]` (day 4 answers all four).
- Equal: `[50,50,50,51]` → `[3,2,1,0]`.

## 3. Brute force + complexity

From each day, scan forward for the first warmer day. **O(n²) time, O(1) extra space.**

## 4. Pattern trigger

"Next **greater** element to the right" → **monotonic (decreasing) stack** of indices still waiting.

## 5. Plan before coding

- `answer(n, 0)`, stack of indices.
- For each i:
  - While the stack isn't empty and `t[i] > t[top]`: pop `prev`, `answer[prev] = i - prev`.
  - Push i.
- Days left on the stack keep 0.

## 6. Code

See the approaches above.

## 7. Dry run

`[73,74,75,71,69,72,76,73]`

| i | temp | pops (answer set) | stack after (index:temp) |
|---|---|---|---|
| 0 | 73 | — | 0:73 |
| 1 | 74 | 0 → 1 | 1:74 |
| 2 | 75 | 1 → 1 | 2:75 |
| 3 | 71 | — | 2:75 3:71 |
| 4 | 69 | — | 2:75 3:71 4:69 |
| 5 | 72 | 4 → 1, 3 → 2 | 2:75 5:72 |
| 6 | 76 | 5 → 1, 2 → 4 | 6:76 |
| 7 | 73 | — | 6:76 7:73 |

Answer **`[1,1,4,2,1,1,0,0]`**.

## 8. Final complexity + extension

**O(n) time, O(n) space.**

Extensions:
- **LC 496 / 503 Next Greater Element I / II** (II wraps around: loop over 2n).
- **LC 84 Largest Rectangle in Histogram**: monotonic stack, popping when a shorter bar arrives.
- **LC 901 Online Stock Span**: previous greater instead of next greater.

## What confused me / what clicked

- The stack holds days **still waiting**; their temps only go down from bottom to top.
- One warm day can answer several waiting days at once: that's the inner `while`.
- Store **indices**, not temperatures, because the answer is `i - prev`.
- O(n): each index is pushed once and popped at most once.
