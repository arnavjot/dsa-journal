## 1. Restate + clarify

Return all **unique** triplets `[a, b, c]` from the array with `a + b + c = 0`.

Questions to ask:
- Values unique, not indices? Yes: no repeated triplets in the output.
- Size up to 3000 → O(n²) is fine, O(n³) isn't.

## 2. Tiny example + edge case

`[-1,0,1,2,-1,-4]` → sorted `[-4,-1,-1,0,1,2]` → **[[-1,-1,2],[-1,0,1]]**.

Edge cases: `[0,1,1]` → []. `[0,0,0]` → [[0,0,0]].

## 3. Brute force + complexity

Every triple + a set to remove repeats: **O(n³)**.

## 4. Pattern trigger

"Three numbers summing to a target" → **sort + fix one + two pointers** (Two Sum II inside a loop).

## 5. Plan before coding

- Sort.
- For each i (skip if equal to the previous): j = i + 1, k = n − 1.
  - sum < 0 → j++; sum > 0 → k−−.
  - sum = 0 → record, move both, skip equal j's and k's.

## 6. Code

See the approaches above.

## 7. Dry run

Sorted `[-4,-1,-1,0,1,2]`

| i | j, k | sum | action |
|---|---|---|---|
| 0 (−4) | … | always < 0 | j moves to the end |
| 1 (−1) | 2, 5 | −1 −1 + 2 = 0 | record [−1,−1,2] |
| 1 (−1) | 3, 4 | −1 + 0 + 1 = 0 | record [−1,0,1] |
| 2 (−1) | | | skip: same as nums[1] |
| 3 (0) | 4, 5 | 3 > 0 | k−−, done |

## 8. Final complexity + extension

**O(n²) time, O(1) extra space** (plus sorting).

Extensions: **LC 16 3Sum Closest**, **LC 18 4Sum** (one more fixed loop).

## What confused me / what clicked

- It's Two Sum II (LC 167) for each fixed `nums[i]`.
- Sorting puts duplicates next to each other, so skipping them is easy.
- Skip duplicates in three places: i, and j/k after a match.
