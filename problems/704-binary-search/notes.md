## 1. Restate + clarify

`nums` is sorted ascending with no duplicates. Return the index of `target`, or `-1` if it isn't there. Must be **O(log n)**.

Questions to ask:
- Sorted which way? Ascending.
- Duplicates? No.
- Size? Up to 10⁴.

## 2. Tiny example + edge case

`[-1,0,3,5,9,12]`, target 9 → **4** (2 looks: index 2, then 4).
Same array, target 2 → **-1**.

Edge cases:
- One element: `[5]`, target 5 → 0; target 6 → -1.
- Target smaller than everything / bigger than everything → -1.

## 3. Brute force + complexity

Scan left to right. **O(n) time, O(1) space.** Ignores the sorting, and the problem asks for O(log n).

## 4. Pattern trigger

"Sorted" + "find" + "O(log n)" → **binary search**: one look at the middle rules out half.

## 5. Plan before coding

- `s = 0`, `e = n - 1`: the part that could still contain target.
- While `s <= e`:
  - `mid = s + (e - s) / 2`.
  - Equal → return mid.
  - `nums[mid] < target` → `s = mid + 1` (left half incl. mid is too small).
  - Else → `e = mid - 1`.
- Return -1.

## 6. Code

See the approaches above.

## 7. Dry run

`[-1,0,3,5,9,12]`, target 9

| s | e | mid | nums[mid] | compare | next |
|---|---|---|---|---|---|
| 0 | 5 | 2 | 3 | 3 < 9 | s = 3 |
| 3 | 5 | 4 | 9 | **equal** | **return 4** |

Target 2:

| s | e | mid | nums[mid] | compare | next |
|---|---|---|---|---|---|
| 0 | 5 | 2 | 3 | 3 > 2 | e = 1 |
| 0 | 1 | 0 | -1 | -1 < 2 | s = 1 |
| 1 | 1 | 1 | 0 | 0 < 2 | s = 2 |
| 2 | 1 | | | s > e | **return -1** |

## 8. Final complexity + extension

**O(log n) time, O(1) space.**

Extensions:
- **LC 35 Search Insert Position**: same loop, return `s` at the end instead of -1.
- **LC 74 / 33 / 153**: binary search on a 2D matrix, a rotated array, the minimum of a rotated array.

## What confused me / what clicked

- `s` and `e` mark what's **still possible**; everything outside is ruled out for good.
- `mid ± 1`, because mid itself was already checked. Using `s = mid` can loop forever.
- `s <= e`, because s == e still has one number to check.
- `s + (e - s) / 2` avoids int overflow.
- Not found → the loop ends with s just past e, and **s is where target would be inserted**.
