## 1. Restate + clarify

Find the contiguous, non-empty subarray with the largest sum and return that sum. Numbers can be negative; n is up to 10⁵.

## 2. Tiny example + edge case

[−2,1,−3,4,−1,2,1,−5,4] → **6** ([4,−1,2,1]). [1] → **1**. [5,4,−1,7,8] → **23** (all of it). All negative [−3,−1,−2] → **−1**.

## 3. Brute force + complexity

Every (i, j), summed from scratch: O(n³). With a running sum per start i: O(n²). Both TLE at 10⁵.

## 4. Pattern trigger

"Maximum sum of a contiguous subarray" → **Kadane's algorithm** (a 1-D DP with O(1) space).

## 5. Plan before coding

- maxi = INT_MIN, sum = 0.
- For each number: sum += x; maxi = max(maxi, sum); if sum < 0, sum = 0.
- Return maxi.

## 6. Code

See the approaches above.

## 7. Dry run

[−2,1,−3,4,−1,2,1,−5,4]:

| x | sum | maxi |
|---|---|---|
| −2 | −2 → reset 0 | −2 |
| 1 | 1 | 1 |
| −3 | −2 → reset 0 | 1 |
| 4 | 4 | 4 |
| −1 | 3 | 4 |
| 2 | 5 | 5 |
| 1 | 6 | **6** |
| −5 | 1 | 6 |
| 4 | 5 | 6 |

## 8. Final complexity + extension

**O(n) time, O(1) space.**

Extension: to return the subarray itself, remember where the running sum last restarted and copy it into (bestStart, bestEnd) whenever maxi improves. Divide and conquer gives O(n log n). Related: LC 152 Maximum Product Subarray, LC 918 Maximum Sum Circular Subarray.

## What confused me / what clicked

- A negative running sum is dead weight: drop it and start again.
- Update maxi before resetting, or an all-negative array would wrongly give 0.
- maxi starts at INT_MIN, not 0, for the same reason.
- Kadane's is DP: best ending at i = max(nums[i], best ending at i − 1 + nums[i]). The reset to 0 is that max written another way.
