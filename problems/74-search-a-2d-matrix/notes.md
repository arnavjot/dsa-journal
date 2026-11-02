## 1. Restate + clarify

Each row is sorted, and each row's first number is greater than the previous row's last number. Return whether `target` is in the matrix, in O(log(m·n)).

## 2. Tiny example + edge case

`[[1,3,5,7],[10,11,16,20],[23,30,34,60]]`: target 3 → **true**; target 13 → **false**.

Edge cases: first cell, last cell, a 1×1 matrix.

## 3. Brute force + complexity

Scan every cell: **O(n·m)**. Top-right staircase walk: **O(n + m)**.

## 4. Pattern trigger

"Sorted rows that continue each other" + "O(log)" → it's **one sorted array** → binary search on the flat index.

## 5. Plan before coding

- s = 0, e = n·m − 1.
- mid → row = mid / m, col = mid % m.
- Equal → true; smaller → s = mid + 1; bigger → e = mid − 1.

## 6. Code

See the approaches above.

## 7. Dry run

Target 3, m = 4

| s | e | mid | cell | value | action |
|---|---|---|---|---|---|
| 0 | 11 | 5 | (1, 1) | 11 | > 3 → e = 4 |
| 0 | 4 | 2 | (0, 2) | 5 | > 3 → e = 1 |
| 0 | 1 | 0 | (0, 0) | 1 | < 3 → s = 1 |
| 1 | 1 | 1 | (0, 1) | 3 | **found** |

## 8. Final complexity + extension

**O(log(n·m)) time, O(1) space.**

Extension: **LC 240 Search a 2D Matrix II** (rows and columns sorted separately, rows don't continue each other) → staircase walk from the top-right, O(n + m).

## What confused me / what clicked

- The matrix is just a sorted array folded into rows.
- `row = mid / m`, `col = mid % m` (m = number of columns).
- `(s + e) / 2` is fine here since n·m ≤ 10⁴; `s + (e − s) / 2` is the overflow-safe habit.
