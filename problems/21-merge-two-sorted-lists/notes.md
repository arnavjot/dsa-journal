## 1. Restate + clarify

Merge two **sorted** linked lists into one sorted list by splicing their nodes together; return the head.

Questions to ask:
- Either list can be empty? Yes.
- Reuse nodes (no new allocations)? Yes, splice.
- Up to 50 nodes each.

## 2. Tiny example + edge case

`[1,2,4]` + `[1,3,4]` → **[1,1,2,3,4,4]**.

Edge cases: `[]` + `[]` → `[]`; `[]` + `[0]` → `[0]`; `[5]` + `[1,2,3,4]` → the 5 goes last.

## 3. Brute force + complexity

Copy all values into an array, sort, rebuild a list: **O((m + n) log(m + n))** time, **O(m + n)** space.

## 4. Pattern trigger

"Two sorted sequences → one" → the **merge step of merge sort** with a tail pointer.

## 5. Plan before coding

- Either empty → return the other.
- head = smaller front; advance that list.
- temp = head; while both non-empty: link the smaller front, advance it, move temp.
- Attach the leftover list. Return head.

## 6. Code

See the approaches above.

## 7. Dry run

`[1,2,4]` + `[1,3,4]`

| step | compare | take | merged |
|---|---|---|---|
| head | 1 ≤ 1 | list1's 1 | 1 |
| 1 | 2 vs 1 | list2's 1 | 1 1 |
| 2 | 2 vs 3 | 2 | 1 1 2 |
| 3 | 4 vs 3 | 3 | 1 1 2 3 |
| 4 | 4 ≤ 4 | list1's 4 | 1 1 2 3 4 |
| end | list1 empty | attach list2 (4) | 1 1 2 3 4 4 |

## 8. Final complexity + extension

**O(m + n) time, O(1) space.**

Extensions: **LC 23 Merge k Sorted Lists** (heap of fronts, or merge pairs); merge sort on a linked list (LC 148).

## What confused me / what clicked

- The answer reuses the input nodes: only `next` pointers change.
- Leftovers attach in one assignment, no loop needed (my first version looped and copied).
- A dummy node removes the "pick the head first" special case.
