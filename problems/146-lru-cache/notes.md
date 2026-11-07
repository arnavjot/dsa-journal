## 1. Restate + clarify

Design a cache with a fixed `capacity`. `get(key)` returns the value or −1; `put(key, value)` inserts or updates. When it's full, a new key evicts the **least recently used** key. Both must be **O(1)**.

Questions to ask:
- Both get and put count as "using" a key. Updating an existing key doesn't evict anything.

## 2. Tiny example + edge case

Capacity 2: put(1,1), put(2,2), get(1) = 1, put(3,3) evicts **2**, get(2) = −1, put(4,4) evicts **1**, get(1) = −1, get(3) = 3, get(4) = 4.
Edge cases: capacity 1; put on an existing key (refresh, no eviction).

## 3. Brute force + complexity

Store (key, value, lastUsed) in an array; scan for a key or for the oldest: **O(n)** per call.

## 4. Pattern trigger

"O(1) lookup + keep an order + remove the oldest" → **hash map + doubly linked list**.

## 5. Plan before coding

- Node {key, val, prev, next}; dummy head and tail.
- `unlink(n)` and `pushFront(n)` helpers.
- get: missing → −1; else move to the front, return val.
- put: exists → update val, move to the front. Else if full → evict `tail->prev` (unlink, erase key, delete). Insert a new node at the front.

## 6. Code

See the approaches above. ★ is the cleaned-up version of your old solution.

## 7. Dry run

Capacity 2 (front = most recent)

| call | list after | evicted |
|---|---|---|
| put(1,1) | 1 | |
| put(2,2) | 2, 1 | |
| get(1) → 1 | 1, 2 | |
| put(3,3) | 3, 1 | 2 |
| get(2) → −1 | 3, 1 | |
| put(4,4) | 4, 3 | 1 |

## 8. Final complexity + extension

**O(1) per call, O(capacity) space.**

Extension: **LC 460 LFU Cache** (evict the least *frequently* used, ties by recency: one list per frequency).

## Review of my old solution

- **Correct and O(1)**: LeetCode accepts it, and every get returns the right value.
- **Memory leak**: `deletenode` only unlinks. After an update or an eviction that node is never `delete`d. (AddressSanitizer reported 66k leaked nodes on a random test.)
- **Extra work on update**: it removes the node and allocates a new one; just set `val` and move the node to the front.
- The commented get works too; `nodes.erase(key)` and `nodes[key] = head->next` are unnecessary because it's the same node.

## What confused me / what clicked

- The node stores its **key** so eviction can erase it from the map.
- Dummy head/tail = no NULL checks.
- Unlinking ≠ freeing: call `delete` when a node is gone for good.
