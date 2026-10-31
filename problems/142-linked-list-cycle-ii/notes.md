## 1. Restate + clarify

Given `head` of a linked list, return the **node where the cycle begins**, or `NULL` if there's no cycle. Don't modify the list. Follow-up: O(1) memory.

Questions to ask:
- Can the list be empty? Yes, return NULL.
- Can the cycle start at head? Yes.
- Size up to 10⁴ nodes.

## 2. Tiny example + edge case

`A → B → C → D → E → F → (back to C)` → return **C**.

Edge cases: empty list → NULL. One node pointing to itself → that node. No cycle → NULL.

## 3. Brute force + complexity

Walk the list, put every node pointer in an `unordered_set`. The first node already in the set is the cycle start. **O(n) time, O(n) space.**

## 4. Pattern trigger

"Cycle in a linked list" + "O(1) memory" → **fast & slow pointers (Floyd)**. Same as LC 287, except here `next` is `node->next` instead of `nums[i]`.

## 5. Plan before coding

- `fast` and `slow` at head. While `fast` and `fast->next` exist: fast 2 steps, slow 1 step.
- If they meet: `fast = head`, then both move 1 step while `fast != slow`. Return `slow`.
- If the loop ends: no cycle, return NULL.

## 6. Code

See the approaches above.

## 7. Dry run

`A → B → C → D → E → F → C`. L = 2, C = 4.

**Phase 1**

| step | slow | fast |
|---|---|---|
| start | A | A |
| 1 | B | C |
| 2 | C | E |
| 3 | D | C |
| 4 | E | E ✅ meet |

slow walked 4, fast walked 8. Extra 4 = 1 lap, k = 1. x = 4 − 2 = 2 (C → D → E).

**Phase 2** (fast back to A, both 1 step)

| check | fast | slow |
|---|---|---|
| start | A | E |
| A ≠ E → move | B | F |
| B ≠ F → move | C | C |
| C == C → stop | return **C** | |

## 8. Final complexity + extension

**O(n) time, O(1) space.**

Extension: to get the cycle **length**, after the first meeting keep one pointer still and walk the other until it comes back, counting steps.

## What confused me / what clicked

- It's the exact same algorithm as LC 287. Index ↔ node, `nums[i]` ↔ `node->next`.
- This version **reuses fast** instead of making slow2. After the reset, fast moves only 1 step.
- **Check before moving** (`while (fast != slow)`) handles L = 0: if the cycle starts at head, they're equal right after `fast = head`, and we return head immediately.
- The `fast->next != NULL` check exists because fast jumps two nodes; `NULL->next` would crash.
