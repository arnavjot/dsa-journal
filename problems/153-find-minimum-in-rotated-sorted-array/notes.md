## 1. Restate + clarify

A sorted array (all different values) was rotated some number of times. Return its **minimum** in **O(log n)**.

Questions to ask:
- Values are unique (yes). It may be rotated 0 times (fully sorted). n ≥ 1.

## 2. Tiny example + edge case

`[3,4,5,1,2]` → **1**. `[4,5,6,7,0,1,2]` → **0**.
Edge cases: not rotated `[11,13,15,17]` → **11**; two elements `[2,1]` → **1**; one element → itself.

## 3. Brute force + complexity

Scan and keep the smallest: **O(n)**. Correct, but the problem wants O(log n).

## 4. Pattern trigger

Sorted (even rotated) + O(log n) → **binary search**. The array goes up, **drops once**, goes up again; the minimum is right after the drop. Each step decides which side the drop is on.

## 5. Plan before coding

- s = 0, e = n − 1.
- While s < e: mid = s + (e − s) / 2.
  - arr[mid] <= arr[e] → mid … e has no drop, so the minimum is at mid or left: **e = mid**.
  - else → arr[mid] is bigger than the end, so the drop is after mid: **s = mid + 1**.
- Return arr[s].

## 6. Code

See the approaches above.

## 7. Dry run

`[4,5,6,7,0,1,2]`

| s | e | mid | arr[mid] vs arr[e] | next |
|---|---|---|---|---|
| 0 | 6 | 3 | 7 > 2 | s = 4 |
| 4 | 6 | 5 | 1 <= 2 | e = 5 |
| 4 | 5 | 4 | 0 <= 1 | e = 4 |

s == e == 4 → return **0**.

## 8. Final complexity + extension

**O(log n) time, O(1) space.**

Extensions: **LC 33 Search in Rotated Sorted Array** (find the drop, then search the right half), **LC 154** (with duplicates: when arr[mid] == arr[e], do e−−).

## Two ways I wrote it

| | compare with **right** (s < e) | compare with **left** (l <= r) |
|---|---|---|
| check | `arr[mid] <= arr[e]` | `nums[mid] >= nums[l]` |
| keeps mid? | yes, `e = mid` | no, so it saves `ans = min(ans, nums[mid])` first |
| unrotated array | works on its own | needs `if (nums[l] < nums[r])` early stop |
| returns | `arr[s]` | `ans` |

The right-end version is shorter because arr[e] always tells you the side: if mid is bigger than the end, the drop **must** be to the right.

## What confused me / what clicked

- `e = mid`, not `mid − 1`: mid might be the answer.
- `s < e` pairs with `e = mid` (with `s <= e` it would loop forever once s == e).
- In the left-end version, `>=` matters: when l == mid, nums[mid] >= nums[l] is true and you correctly move right.
