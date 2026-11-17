## 1. Restate + clarify

Bursting balloon i earns nums[left]·nums[i]·nums[right] with its current neighbours (missing = 1). Find the most coins from bursting all of them.

## 2. Tiny example + edge case

[3,1,5,8] → **167**. [1,5] → **10**. [7] → **7**.

## 3. Brute force + complexity

Try every burst order: O(n!).

## 4. Pattern trigger

"Remove items one by one, score depends on current neighbours" → **interval DP where k is removed last**.

## 5. Plan before coding

- v = [1] + nums + [1]; dp all 0.
- For len = 2..n + 1, l = 0.., r = l + len: dp[l][r] = max over l < k < r of dp[l][k] + dp[k][r] + v[l]·v[k]·v[r].
- Return dp[0][n + 1].

## 6. Code

See the approaches above.

## 7. Dry run

[1,5], so v = [1,1,5,1]:

- dp[0][2] = 1·1·5 = 5.
- dp[1][3] = 1·5·1 = 5.
- dp[0][3]: if k = 1 (the 1) goes last: dp[1][3] + 1·1·1 = 6. If k = 2 (the 5) goes last: dp[0][2] + 1·5·1 = **10**.

## 8. Final complexity + extension

**O(n³) time, O(n²) space.** Related: LC 1039 Minimum Score Triangulation, LC 1000 Minimum Cost to Merge Stones, matrix-chain multiplication.

## What confused me / what clicked

- Thinking about the last burst makes the two sides independent.
- Use open intervals (l, r) with the padded 1s.
- I didn't paste code for this one; it's mine.
