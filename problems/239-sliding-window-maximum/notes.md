## 1. Restate + clarify

For every window of size `k` sliding across `nums`, return its maximum (n − k + 1 values).

Questions to ask:
- 1 ≤ k ≤ n ≤ 10⁵; negatives allowed.

## 2. Tiny example + edge case

`[1,3,-1,-3,5,3,6,7]`, k = 3 → **[3,3,5,5,6,7]**.

Edge cases: k = 1 → the array itself; repeated values `[7,7,2,7,1]`, k = 2 → [7,7,7,7].

## 3. Brute force + complexity

Scan every window for its max: **O(n · k)**.

## 4. Pattern trigger

"Max of every window" → a structure with fast max under insert/delete: **ordered map / multiset** (log k) or **monotonic deque** (O(1) amortized).

## 5. Plan before coding

- Put the first k numbers in `mp` (with counts); push `mp.rbegin()`.
- For i = k … n − 1: decrement `nums[i − k]` (erase at 0), add `nums[i]`, push `mp.rbegin()`.

## 6. Code

See the approaches above.

## 7. Dry run

`[1,3,-1,-3,5,3,6,7]`, k = 3

| window | map keys | max |
|---|---|---|
| 1 3 −1 | −1 1 3 | 3 |
| 3 −1 −3 | −3 −1 3 | 3 |
| −1 −3 5 | −3 −1 5 | 5 |
| −3 5 3 | −3 3 5 | 5 |
| 5 3 6 | 3 5 6 | 6 |
| 3 6 7 | 3 6 7 | 7 |

## 8. Final complexity + extension

Map: **O(n log k)**. Deque: **O(n)**. Both O(k) space.

Extension: the deque trick also solves **LC 1438** (longest subarray with max − min ≤ limit) with two deques.

## What confused me / what clicked

- Counts matter: a duplicate value must stay until its **last** copy leaves.
- `mp.rbegin()` is the biggest key in a `map`.
- The deque keeps only values that could still become a max, so the front is always the answer.
