## 1. Restate + clarify

Make a **deep copy** of a list where every node also has a `random` pointer (to any node or NULL). No copy may point into the original list.

Questions to ask:
- random can point to itself, backwards, forwards or NULL. Values can repeat (so map by **node**, not value).

## 2. Tiny example + edge case

`[[7,null],[13,0],[11,4],[10,2],[1,0]]` → same shape, all new nodes.
Edge cases: empty list → NULL; `[[1,0]]` (random to itself).

## 3. Brute force + complexity

For each copy's random, walk the original from head to find the target's position, then walk the copy to the same position: **O(n²)**.

## 4. Pattern trigger

"Copy a structure with arbitrary pointers" → **hash map original → copy**.

## 5. Plan before coding

- Map head → new copy.
- For each node: if next has no copy, make one; copy->next = map[next]. Same for random.
- Move on. Return map[head].

## 6. Code

See the approaches above.

## 7. Dry run

`[[1,1],[2,1]]`

| temp | next | random | copies after |
|---|---|---|---|
| #0 (1) | #1: create 2' | #1: exists | 1', 2' |
| #1 (2) | NULL | #1: exists (itself) | 1', 2' |

Return 1' → 2', both randoms → 2'.

## 8. Final complexity + extension

**O(n) time, O(n) space** (the map).

O(1) extra space: interleave copies (A → A' → B → B'), set `A'->random = A->random->next`, then split the two lists.

## What confused me / what clicked

- The map answers "what is the copy of **that** node?" for random pointers anywhere in the list.
- Check the map before `new`: one copy per node.
- Two-pass is simpler; one-pass needs the "already made?" checks.
