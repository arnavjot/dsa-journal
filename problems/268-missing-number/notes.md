## 1. Restate + clarify

nums has n distinct numbers from the range 0..n. Return the one number in that range that is missing.

## 2. Tiny example + edge case

[3,0,1] → **2**. [0,1] → **2** (n itself). [9,6,4,2,3,5,7,0,1] → **8**. [1] → **0**.

## 3. Brute force + complexity

For each 0..n, search the array: O(n²). Sort then scan: O(n log n).

## 4. Pattern trigger

"Numbers 0..n, one missing" → **cyclic sort**, **sum formula** or **XOR** (all O(n), O(1)).

## 5. Plan before coding

- Cyclic sort: while i < n, if nums[i] < n and nums[i] != nums[nums[i]], swap it home; else i++.
- Then the first i with nums[i] != i is missing; if none, n.

## 6. Code

See the approaches above.

## 7. Dry run

[3,0,1], cyclic sort:

- i = 0: value 3 = n → i++.
- i = 1: value 0 → swap with index 0 → [0,3,1].
- i = 1: value 3 → i++.
- i = 2: value 1 → swap with index 1 → [0,1,3].
- i = 2: value 3 → i++.

Scan: index 2 holds 3 ≠ 2 → **2**.

## 8. Final complexity + extension

**O(n) time, O(1) space.** Cyclic sort also solves LC 41 First Missing Positive, LC 448 Find All Numbers Disappeared in an Array and LC 287 Find the Duplicate Number.

## What confused me / what clicked

- Value v belongs at index v; the value n has no slot, so it's skipped.
- Checking nums[i] != nums[correct] stops it from swapping forever when the right value is already there.
- XOR is the bit-manipulation answer: every present number shows up twice (as an index and as a value). It doesn't change the array and can't overflow.
- The sum formula is fine here because n ≤ 10⁴.
