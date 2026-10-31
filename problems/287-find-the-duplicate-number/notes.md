## 1. Restate + clarify

`nums` has **n + 1** numbers, every value is between **1 and n**, and exactly one value repeats (maybe many times). Return that value. Rules: don't modify `nums`, use only O(1) extra space.

Questions to ask:
- Size? n ≤ 10⁵, so O(n²) is too slow. I need O(n) or O(n log n).
- Can the duplicate appear more than twice? Yes, it can.
- Can I change the array? No. Can I use a hash set? Not if space must be O(1).

## 2. Tiny example + edge case

`[1, 3, 4, 2, 2]` → answer **2**.

Edge case: the duplicate fills almost everything, `[2, 2, 2, 2, 2]` → **2**.

## 3. Brute force + complexity

Compare every pair. If `nums[i] == nums[j]`, return it. **O(n²) time, O(1) space.** It works but is too slow for 10⁵.

(A hash set or sorting would be faster, but both break the rules: extra space, or changing the array.)

## 4. Pattern trigger

"n + 1 numbers in the range 1..n" means every value is also a valid **index**. So `i → nums[i]` is a "next pointer" and the array is secretly a **linked list**. A duplicate value means two arrows point into the same node, which means a **cycle**. That's **fast & slow pointers (Floyd)**.

## 5. Plan before coding

- Phase 1: `slow = nums[slow]`, `fast = nums[nums[fast]]` until they're equal. Now both are inside the loop.
- Phase 2: `slow2 = 0`. Move `slow` and `slow2` one step at a time until equal. That index is the loop's start = the duplicate.
- Target: O(n) time, O(1) space, array untouched.

## 6. Code

See the three approaches above: brute force, cyclic sort, Floyd.

## 7. Dry run

`nums = [1, 3, 4, 2, 2]`. Arrows: 0→1→3→2→4→2 (loop 2→4→2). L = 3, C = 2.

**Phase 1**

| move | slow | fast |
|---|---|---|
| start | 0 | 0 |
| 1 | 1 | 3 |
| 2 | 3 | 4 |
| 3 | 2 | 4 |
| 4 | 4 | 4 ✅ meet |

slow walked 4, fast walked 8. Extra = 4 = 2 laps of 2, so k = 2. x = 4 − 3 = 1.

**Phase 2**

| check | slow | slow2 |
|---|---|---|
| start | 4 | 0 |
| 4 ≠ 0 → move | 2 | 1 |
| 2 ≠ 1 → move | 4 | 3 |
| 4 ≠ 3 → move | 2 | 2 |
| 2 == 2 → stop | return **2** | |

Edge case `[2,2,2,2,2]`: 0→2→2, so slow and fast meet at 2 right away, then slow2 goes 0→2. Return 2. ✓

## 8. Final complexity + extension

**O(n) time, O(1) space**, array not modified.

Extension: binary search on the *value* also works without modifying the array: for a guess `mid`, count how many numbers are ≤ mid. If the count is more than mid, the duplicate is ≤ mid. That's O(n log n) time, O(1) space.

## What confused me / what clicked

- **The phase 1 meeting point is not the answer.** It only puts a pointer somewhere inside the loop.
- **Why phase 2 works:** slow walked L + x, fast walked 2(L + x). Fast's extra L + x was only full laps, so L + x = k·C. From the meeting point (x into the loop), L more steps = full laps = back at the start. slow2 also needs exactly L steps from 0. They arrive together.
- **k isn't special.** It's however many extra laps fast happened to run. Long road + small loop → big k.
- **Why start at 0:** values are 1..n, so nothing points to 0. Index 0 is always on the road, never in the loop.
- **Cyclic sort works** but modifies the array. Say that out loud in the interview, then give Floyd.
