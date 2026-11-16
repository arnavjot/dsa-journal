## 1. Restate + clarify

Return the fewest jumps to reach the last index (it's guaranteed reachable). nums[i] is the maximum jump length from i.

## 2. Tiny example + edge case

[2,3,1,1,4] → **2** (0 → 1 → 4). [2,3,0,1,4] → **2**. [0] → **0**.

## 3. Brute force + complexity

DP: min over all earlier j that can reach i, which is O(n²). BFS with a queue is O(n²) edges.

## 4. Pattern trigger

"Fewest steps" → BFS; reach is a range, so **windows instead of a queue**.

## 5. Plan before coding

- jumps = curEnd = farthest = 0.
- For i = 0..n − 2: farthest = max(farthest, i + nums[i]); if i == curEnd: jumps++, curEnd = farthest.
- Return jumps.

## 6. Code

See the approaches above.

## 7. Dry run

[2,3,1,1,4]:

- i = 0: farthest 2, i = curEnd → jumps 1, curEnd 2.
- i = 1: farthest 4.
- i = 2: i = curEnd → jumps 2, curEnd 4.
- i = 3: farthest 4.

Result **2**.

## 8. Final complexity + extension

**O(n) time, O(1) space.** Related: LC 55 Jump Game, LC 1306 Jump Game III, LC 1345 Jump Game IV (real BFS).

## What confused me / what clicked

- Each window is a BFS level.
- Jump only when the window runs out.
- I didn't paste code for this one; it's mine.
