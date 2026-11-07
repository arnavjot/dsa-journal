## 1. Restate + clarify

Given `nums` and `target`, return the **indices** of the two numbers that add up to `target`. Exactly one answer exists, and you can't use the same element twice.

Questions to ask:
- Indices or values? Indices, in any order.
- Can numbers be negative or repeat? Yes to both.
- Size? 2 to 10⁴, values −10⁹ to 10⁹.

## 2. Tiny example + edge case

`[2,7,11,15]`, target 9 → 2 + 7 → **[0,1]**.

Edge cases:
- `[3,2,4]`, target 6 → **[1,2]**, not [0,0]: 3 can't pair with itself.
- `[3,3]`, target 6 → **[0,1]**: the same value twice is fine, it's two different elements.

## 3. Brute force + complexity

Try every pair i < j. **O(n²) time, O(1) space.**

## 4. Pattern trigger

"Find two that add up to X" + unsorted → for each number the partner is **fixed** (target − x) → "have I seen the partner?" → **hash map** (number → index).

## 5. Plan before coding

- `unordered_map<int,int> seen` (number → index).
- For each i: `rem = target - nums[i]`.
  - `seen` has rem → return `{seen[rem], i}`.
  - Else `seen[nums[i]] = i`.
- Look up **before** saving.

## 6. Code

See the approaches above.

## 7. Dry run

`nums = [3,2,4]`, target 6

| i | nums[i] | rem | seen before | found? | action |
|---|---|---|---|---|---|
| 0 | 3 | 3 | {} | no | save 3→0 |
| 1 | 2 | 4 | {3→0} | no | save 2→1 |
| 2 | 4 | 2 | {3→0, 2→1} | **yes, index 1** | **return {1, 2}** |

At i = 0 the map is still empty, so 3 can't use itself as its own partner.

## 8. Final complexity + extension

**O(n) time, O(n) space.**

Extensions:
- **LC 167 Two Sum II** (sorted input): two pointers, O(1) space.
- **LC 15 3Sum**: sort, fix one number, run two pointers on the rest.

## What confused me / what clicked

- The partner isn't something to search for, it's **calculated**: rem = target − nums[i].
- The map stores **number → index**, because you look up by number and the answer wants the index.
- **Look up first, then save**: that's what stops a number pairing with itself.
- Whichever element of the pair comes second finds the first one already saved, so one pass is enough.
