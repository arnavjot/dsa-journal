## 1. Restate + clarify

Merge k sorted linked lists into one sorted list.

Questions to ask:
- `lists` can be empty, and any list inside can be empty (NULL). N = total nodes, k ≤ 10⁴.

## 2. Tiny example + edge case

`[1,4,5], [1,3,4], [2,6]` → `1,1,2,3,4,4,5,6`. `[]` → `[]`. `[[]]` → `[]`.

## 3. Brute force + complexity

Collect every node, sort by value, relink: **O(N log N)**. Or merge one list at a time into a growing result: **O(N·k)**.

## 4. Pattern trigger

"Repeatedly take the smallest of k candidates" → **min-heap** (priority_queue with a reversed compare).

## 5. Plan before coding

- Push every non-empty head.
- While the heap isn't empty: pop the smallest, attach it after tail (or make it head), push its next if any.
- Return head.

## 6. Code

See the approaches above.

## 7. Dry run

Example 1, heap shown smallest first:

| pop | push | heap after | merged |
|---|---|---|---|
| 1 (list 0) | 4 | 1, 2, 4 | 1 |
| 1 (list 1) | 3 | 2, 3, 4 | 1 1 |
| 2 (list 2) | 6 | 3, 4, 6 | 1 1 2 |
| 3 | 4 | 4, 4, 6 | … 3 |

and so on until the heap is empty.

## 8. Final complexity + extension

**O(N log k) time, O(k) heap.** Merging in pairs is also O(N log k), with no heap.

Tidier: start from a **dummy** node so the `head == NULL` branch disappears (both branches do the same thing).

## What confused me / what clicked

- `a->val > b->val` makes priority_queue a **min**-heap.
- Push only `tail->next`: each list is sorted.
- Pairs beat one-by-one: log k rounds instead of k.
