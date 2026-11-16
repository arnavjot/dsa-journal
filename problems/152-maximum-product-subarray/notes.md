## 1. Restate + clarify

Find the contiguous non-empty subarray with the largest product and return that product.

## 2. Tiny example + edge case

[2,3,−2,4] → **6**. [−2,0,−1] → **0**. [−2,3,−4] → **24**.

## 3. Brute force + complexity

All subarrays with a running product: O(n²).

## 4. Pattern trigger

"Best product of a subarray" → **Kadane with both max and min**.

## 5. Plan before coding

- best = curMax = curMin = nums[0].
- For each x after it: if x < 0 swap; curMax = max(x, curMax × x); curMin = min(x, curMin × x); best = max(best, curMax).

## 6. Code

See the approaches above.

## 7. Dry run

[2,−5,−2,−4,3]:

- x = −5: swap → curMax −5, curMin −10.
- x = −2: swap → curMax 20, curMin −2.
- x = −4: swap → curMax 8, curMin −80.
- x = 3: curMax 24, curMin −240.

best = **24** ([−2,−4,3]).

## 8. Final complexity + extension

**O(n) time, O(1) space.** Related: LC 53 Maximum Subarray (Kadane), LC 1567 Maximum Length of Subarray With Positive Product.

## What confused me / what clicked

- A negative turns min into max, so keep both.
- max(x, …) restarts at x, which also handles zeros.
- I didn't paste code for this one; it's mine.
