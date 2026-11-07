## 1. Restate + clarify

Return the length of the longest run of consecutive **values** (any order in the array), in O(n).

Questions to ask:
- Duplicates? Yes (they don't extend a run). Empty → 0.
- Up to 10⁵ numbers.

## 2. Tiny example + edge case

`[100,4,200,1,3,2]` → 1, 2, 3, 4 → **4**.
`[0,3,7,2,5,8,4,6,0,1]` → 0…8 → **9**.

Edge case: `[1,2,0,1]` → 3.

## 3. Brute force + complexity

From every number, linear-search for x + 1, x + 2…: **O(n³)**. Sorting: **O(n log n)**.

## 4. Pattern trigger

"Consecutive values, O(n)" → **hash set** + count only from **run starts**.

## 5. Plan before coding

- `st = set(nums)`.
- For each num in st: if `num - 1` not in st → count up while `curr + 1` in st.
- Track the longest.

## 6. Code

See the approaches above.

## 7. Dry run

`[100,4,200,1,3,2]`

| num | num − 1 in set? | run | length |
|---|---|---|---|
| 100 | no | 100 | 1 |
| 4 | yes (3) | skip | — |
| 200 | no | 200 | 1 |
| 1 | no | 1, 2, 3, 4 | **4** |
| 3, 2 | yes | skip | — |

## 8. Final complexity + extension

**O(n) time, O(n) space.**

Extension: union-find over neighbours also works (more complex).

## What confused me / what clicked

- Starting only at run starts is what makes it O(n).
- The inner while looks nested, but across the whole loop it advances at most n times.
- Duplicates disappear in the set.
