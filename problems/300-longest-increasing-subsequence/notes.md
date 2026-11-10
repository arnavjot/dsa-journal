## 1. Restate + clarify

Length of the longest **strictly** increasing subsequence (can skip elements, keeps order). 1 ≤ n ≤ 2500.

## 2. Tiny example + edge case

[10,9,2,5,3,7,101,18] → **4** (2, 3, 7, 18). [0,1,0,3,2,3] → **4**. All equal [7,7,7] → **1**.

## 3. Brute force + complexity

Every subsequence: O(2ⁿ). Take/skip recursion is the same.

## 4. Pattern trigger

"Longest increasing subsequence" → DP on (curr, prev) in O(n²), or the **tails array + binary search** in O(n log n).

## 5. Plan before coding

- ans = [nums[0]].
- For each next x: if x > ans.back(), push it. Else find the first ans[k] ≥ x and set ans[k] = x.
- Return ans.size().

## 6. Code

See the approaches above.

## 7. Dry run

[3,4,1,2,5]:

| x | action | ans |
|---|---|---|
| 3 | start | [3] |
| 4 | 4 > 3, push | [3, 4] |
| 1 | replace 3 | [1, 4] |
| 2 | replace 4 | [1, 2] |
| 5 | 5 > 2, push | [1, 2, 5] |

Answer **3**. The real LIS is 3, 4, 5; ans = [1, 2, 5] is not a subsequence, but its length is right.

## 8. Final complexity + extension

**O(n log n) time, O(n) space.** DP versions: O(n²) time; memo and tabulation O(n²) space, two-row tabulation O(n).

Extension: to print an actual LIS, store for each number the index it replaced/extended (a parent pointer) and walk back. Related: LC 354 Russian Doll Envelopes, LC 1143 Longest Common Subsequence.

## What confused me / what clicked

- ans[k] = smallest tail for length k + 1; replacing makes the tail smaller, which only helps later numbers.
- ans is not the LIS itself, just the right length.
- Search for first ≥ (lower_bound), because equal numbers can't extend a strictly increasing run.
- In the memo, prev starts at −1, so dp uses prev + 1.
