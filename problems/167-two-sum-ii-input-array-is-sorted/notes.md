## 1. Restate + clarify

`numbers` is sorted ascending. Find the two numbers that add up to `target` and return their positions **1-indexed**, as `[i, j]` with i < j. Exactly one answer exists; the same element can't be used twice. Use **O(1) extra space**.

Questions to ask:
- 1-indexed? Yes, return positions + 1.
- Duplicates? Yes, numbers can repeat.
- Size? 2 to 3·10⁴.

## 2. Tiny example + edge case

`[2,7,11,15]`, target 9 → 2 + 7 → **[1,2]**.

Edge cases:
- `[-1,0]`, target -1 → **[1,2]** (negatives).
- `[1,2,3,4,4,9,56,90]`, target 8 → the two 4s → **[4,5]**.

## 3. Brute force + complexity

Every pair: **O(n²) time, O(1) space.**
Binary search for each partner: **O(n log n)**.
Hash map from Two Sum I: **O(n) time but O(n) space**, which breaks the rule.

## 4. Pattern trigger

"Sorted" + "pair that sums to target" + "O(1) space" → **two pointers from both ends**.

## 5. Plan before coding

- `left = 0`, `right = n - 1`.
- While `left < right`:
  - sum == target → return `{left + 1, right + 1}`.
  - sum < target → `left++` (numbers[left] is too small for any partner left).
  - sum > target → `right--` (numbers[right] is too big for any partner left).

## 6. Code

See the approaches above.

## 7. Dry run

`[1,3,4,5,7,10,11]`, target 9

| left | right | sum | compare | move |
|---|---|---|---|---|
| 0 (1) | 6 (11) | 12 | > 9 | right-- |
| 0 (1) | 5 (10) | 11 | > 9 | right-- |
| 0 (1) | 4 (7) | 8 | < 9 | left++ |
| 1 (3) | 4 (7) | 10 | > 9 | right-- |
| 1 (3) | 3 (5) | 8 | < 9 | left++ |
| 2 (4) | 3 (5) | **9** | equal | **return [3, 4]** |

## 8. Final complexity + extension

**O(n) time, O(1) space.**

Extensions:
- **LC 15 3Sum**: sort, fix one number, run this two-pointer search on the rest for `-fixed`.
- **LC 11 Container With Most Water**: same "move the pointer that can't help" idea.

## What confused me / what clicked

- Moving a pointer is safe because the number left behind **can't pair with anything still in range**: too small with the biggest, or too big with the smallest.
- At most n − 1 comparisons, since each one rules out a number.
- Answer is **1-indexed**: `left + 1, right + 1`.
- Two Sum I's hash map works, but this problem wants O(1) space, and sorting is what makes the two pointers possible.
