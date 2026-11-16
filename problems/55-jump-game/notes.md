## 1. Restate + clarify

Starting at index 0, nums[i] is the maximum jump length from i. Can you reach the last index?

## 2. Tiny example + edge case

[2,3,1,1,4] → **true**. [3,2,1,0,4] → **false** (every path lands on the 0 at index 3). [0] → **true**.

## 3. Brute force + complexity

DP: good[i] = some j in 1..nums[i] with good[i + j]. That's O(n²).

## 4. Pattern trigger

"Can I reach the end" → **greedy farthest reach**.

## 5. Plan before coding

- maxReach = 0.
- For each i: if i > maxReach → false; maxReach = max(maxReach, i + nums[i]).
- Return true.

## 6. Code

See the approaches above.

## 7. Dry run

[3,2,1,0,4]: maxReach 3, 3, 3, 3. Then i = 4 > 3 → **false**.

## 8. Final complexity + extension

**O(n) time, O(1) space.** Related: LC 45 Jump Game II (fewest jumps), LC 1306 Jump Game III (BFS).

## What confused me / what clicked

- The reachable set is always a prefix, so maxReach says it all.
- I didn't paste code for this one; it's mine.
