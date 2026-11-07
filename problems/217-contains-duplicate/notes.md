## 1. Restate + clarify

Given an integer array `nums`, return `true` if **any value appears at least twice**, `false` if every value is different.

Questions to ask:
- Size? 1 to 10⁵ numbers, so O(n²) is too slow.
- Range? −10⁹ to 10⁹, so no counting array indexed by value.
- Can I change the array? (Decides whether sorting is allowed.)

## 2. Tiny example + edge case

`[1,2,3,1]` → 1 appears twice → **true**.
`[1,2,3,4]` → all different → **false**.

Edge cases: one number → false. Negatives work the same: `[-3,7,0,-3]` → true.

## 3. Brute force + complexity

Compare every pair (i, j), i < j. **O(n²) time, O(1) space.** ~5·10⁹ comparisons at n = 10⁵: too slow.

Better: sort, then compare neighbours. **O(n log n), O(1) extra**, but it changes the array.

## 4. Pattern trigger

"Have I seen this value before?" → **hash set**. Trade O(n) memory for O(1) lookups.

## 5. Plan before coding

- `unordered_set<int> seen`.
- For each `num`: if `seen.count(num)` → return true. Else `seen.insert(num)`.
- Loop ends → return false.

## 6. Code

See the approaches above.

## 7. Dry run

`nums = [1,2,3,1]`

| i | num | seen before | count(num) | action | seen after |
|---|---|---|---|---|---|
| 0 | 1 | {} | 0 | insert | {1} |
| 1 | 2 | {1} | 0 | insert | {1,2} |
| 2 | 3 | {1,2} | 0 | insert | {1,2,3} |
| 3 | 1 | {1,2,3} | **1** | **return true** | |

`[1,2,3,4]`: every count is 0, the loop ends, **return false**.

## 8. Final complexity + extension

**O(n) time, O(n) space.**

Extensions:
- **LC 219 Contains Duplicate II**: a repeat within distance k. Keep only the last k numbers in the set (sliding window), or store each number's last index in a map.
- To return *which* number repeats, return `num` instead of `true`.

## What confused me / what clicked

- **Check before insert.** Insert first and `count` always finds the number you just added.
- `count()` doesn't scan the whole set: it hashes `num` to one bucket and looks only there. That's where the O(1) comes from.
- Return early: one repeat is enough, so only an all-different array gets read to the end.
- Sorting is the answer when memory is tight but changing the array is allowed.
