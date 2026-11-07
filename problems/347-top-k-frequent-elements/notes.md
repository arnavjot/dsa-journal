## 1. Restate + clarify

Return the `k` numbers that appear most often, in any order. The answer is unique.

Questions to ask:
- Any order? Yes. 1 ≤ k ≤ number of distinct values.
- Size? Up to 10⁵, so aim for better than O(n²).

## 2. Tiny example + edge case

`[1,1,1,2,2,3]`, k = 2 → counts 1→3, 2→2, 3→1 → **[1,2]**.

Edge case: `[1]`, k = 1 → [1].

## 3. Brute force + complexity

Count each number by re-scanning (visited array), sort the pairs: **O(n²)**. Map + sort: **O(n + d log d)**.

## 4. Pattern trigger

"Top k by frequency" → **hash map to count** + **heap of size k** (or bucket sort).

## 5. Plan before coding

- `freq[num]++` for every number.
- Min-heap of (count, num): push each pair, pop when size > k.
- Pop the remaining k into `ans`.

## 6. Code

See the approaches above.

## 7. Dry run

`[1,1,1,2,2,3]`, k = 2: freq = {1:3, 2:2, 3:1}

| push | heap (top first) | pop? |
|---|---|---|
| (3,1) | (3,1) | no |
| (2,2) | (2,2) (3,1) | no |
| (1,3) | (1,3) (2,2) (3,1) | size 3 > 2 → pop (1,3) |

Answer: pop (2,2), (3,1) → **[2,1]**.

## 8. Final complexity + extension

**O(n + d log k) time, O(d + k) space.**

Extensions: **bucket sort** by count for O(n); **LC 692 Top K Frequent Words** (ties by alphabetical order); **LC 215 Kth Largest**.

## What confused me / what clicked

- Min-heap for "most frequent": you throw out the **smallest** when it's too big.
- Store `(count, num)` so the heap orders by count.
- The heap stays at size k, so it's log k per operation, not log n.
