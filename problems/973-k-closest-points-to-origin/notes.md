## 1. Restate + clarify

Return the k points closest to (0, 0), any order.

Questions to ask:
- Coordinates up to 10⁴, so x² + y² ≤ 2·10⁸ fits in an int.

## 2. Tiny example + edge case

[[1,3],[-2,2]], k = 1 → [[-2,2]] (d² 8 vs 10). [[3,3],[5,-1],[-2,4]], k = 2 → [[3,3],[-2,4]].

## 3. Brute force + complexity

Sort by distance², take the first k: **O(n log n)**. Your min-heap of all points is the same cost.

## 4. Pattern trigger

"k smallest of n" → **max-heap of size k** (evict the worst).

## 5. Plan before coding

- For each point: push {x² + y², index}; if size > k, pop (the farthest).
- The k left in the heap are the answer.

## 6. Code

See the approaches above.

## 7. Dry run

[[3,3],[5,-1],[-2,4]], k = 2: push 18 → push 26 → push 20 → size 3 > 2 → pop 26 → answer {18, 20} = [3,3], [-2,4].

## 8. Final complexity + extension

**O(n log k) time, O(k) space.** Quickselect on distance: O(n) average.

Same pattern: **LC 215**, **LC 347**.

## Review of my solution

- **Correct**: a min-heap of all points, then pop k.
- It costs **O(n log n)** because every point goes in. Keeping only k (max-heap, pop the farthest) is O(n log k), which matters when k is much smaller than n.

## What confused me / what clicked

- Compare distance², no sqrt.
- "k closest" → max-heap of size k (throw away the farthest).
