## 1. Restate + clarify

A sorted array of **unique** values was rotated at some unknown point. Return the index of `target`, or −1, in **O(log n)**.

Questions to ask:
- Values unique? **Yes.** Can it be rotated 0 times? **Yes.** Missing target → −1.

## 2. Tiny example + edge case

`[4,5,6,7,0,1,2]`, target 0 → **4**; target 3 → **−1**.
Edge cases: `[1]`, target 0 → −1; `[5,1,3]`, target 3 → **2**.

## 3. Brute force + complexity

Scan every index: **O(n)**.

## 4. Pattern trigger

Rotated sorted + O(log n) → **binary search**. Key fact: cut at mid, and **one half is always sorted**, because the array only drops once.

## 5. Plan before coding

- low = 0, high = n − 1. While low <= high: mid.
- nums[mid] == target → return mid.
- **Left sorted** (nums[low] <= nums[mid]):
  - nums[low] <= target <= nums[mid] → high = mid − 1; else low = mid + 1.
- **Right sorted** (otherwise):
  - nums[mid] <= target <= nums[high] → low = mid + 1; else high = mid − 1.
- Return −1.

## 6. Code

See the approaches above.

## 7. Dry run

`[4,5,6,7,0,1,2]`, target 0

| low | high | mid | nums[mid] | sorted half | target inside? | next |
|---|---|---|---|---|---|---|
| 0 | 6 | 3 | 7 | left [4…7] | no | low = 4 |
| 4 | 6 | 5 | 1 | left [0…1] | yes | high = 4 |
| 4 | 4 | 4 | 0 | found | | return **4** |

## 8. Final complexity + extension

**O(log n) time, O(1) space.**

Extensions: **LC 81** (with duplicates: when nums[low] == nums[mid] == nums[high], shrink both ends, worst case O(n)), **LC 153** (find the minimum).

## Two ways to think about it

| | one pass (mine) | pivot first |
|---|---|---|
| idea | each step: which half is sorted, is target in it? | find min index (LC 153), then normal binary search in the right part |
| loops | 1 | 2 |
| time | O(log n) | O(log n) + O(log n) |

## What confused me / what clicked

- You can only **trust the range check in the sorted half**. If target isn't there, go to the other half without checking it.
- `<=` in `nums[low] <= nums[mid]`: when low == mid, the one-element left half counts as sorted.
- `(low + high) / 2` is fine here (n ≤ 5000); `low + (high − low) / 2` avoids overflow in general.
