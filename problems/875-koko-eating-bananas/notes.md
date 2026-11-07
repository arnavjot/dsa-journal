## 1. Restate + clarify

Koko eats `k` bananas per hour from one pile (a pile smaller than k still takes the whole hour). Find the **minimum** k so she finishes all piles within `h` hours.

Questions to ask:
- h ≥ number of piles (guaranteed). Piles up to 10⁹, so the answer range is huge.

## 2. Tiny example + edge case

`[3,6,7,11]`, h = 8 → **4** (1 + 2 + 2 + 3 = 8 hours).
`[30,11,23,4,20]`, h = 5 → **30**; h = 6 → **23**.

## 3. Brute force + complexity

Try k = 1, 2, …: **O(n · max(piles))**.

## 4. Pattern trigger

"Minimum value such that a check passes" + the check is monotonic → **binary search on the answer**.

## 5. Plan before coding

- left = 1, right = max(piles), ans = right.
- mid → hours = Σ (pile + mid − 1) / mid.
- hours ≤ h → ans = mid, right = mid − 1; else left = mid + 1.

## 6. Code

See the approaches above.

## 7. Dry run

`[3,6,7,11]`, h = 8

| left | right | mid | hours | fits? | next |
|---|---|---|---|---|---|
| 1 | 11 | 6 | 1+1+2+2 = 6 | yes | ans 6, right 5 |
| 1 | 5 | 3 | 1+2+3+4 = 10 | no | left 4 |
| 4 | 5 | 4 | 1+2+2+3 = 8 | yes | ans 4, right 3 |

Return **4**.

## 8. Final complexity + extension

**O(n log max) time, O(1) space.**

Extensions (same pattern): **LC 1011 Ship Packages Within D Days**, **LC 410 Split Array Largest Sum**, **LC 1482**.

## Where `(pile + mid - 1) / mid` comes from

I need pile ÷ speed **rounded up** (a leftover banana still costs a whole hour), but `int / int` in C++ rounds **down**.

1. **Plain version first:**

   ```cpp
   hours += pile / mid;            // full hours (rounds down)
   if (pile % mid != 0) hours++;   // any leftover → one more hour
   ```

   Careful: `+=`, not `=` (that would overwrite the total) and not `int hours = …` (that makes a new variable inside the loop).

2. **Can I drop the `if`?** Add something to `pile` so rounding down lands where rounding up would.

3. **Test tiny numbers** (speed 3):

   | pile | want | must add |
   |---|---|---|
   | 6 (exact) | 2 | at most 2 (adding 3 → 9/3 = 3, too many) |
   | 7 (remainder 1) | 3 | at least 2 (7 + 2 = 9 → 3) |

   The only value that works for both is 2 = **mid − 1**.

4. **Why:** a remainder is 1 … mid − 1. Adding mid − 1 pushes even remainder 1 to the next multiple; an exact fit stays just short. Adding a full `mid` would add an hour **every** time.

Same idiom anywhere you divide into groups: pages, trips, boxes. `ceil((double)a / b)` also works but can be off for huge numbers.

## What confused me / what clicked

- You binary search the **speed**, not the piles.
- `(pile + k − 1) / k` is integer ceil.
- `long long` for the hours sum.
- When it fits, save it and keep looking slower.
