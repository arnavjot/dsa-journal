## 1. Restate + clarify

Given meeting times [start, end), can one person attend all of them? A meeting may start exactly when another ends.

## 2. Tiny example + edge case

[[0,30],[5,10],[15,20]] → **false**. [[7,10],[2,4]] → **true**. Empty → **true**.

## 3. Brute force + complexity

Check every pair for overlap: O(n²).

## 4. Pattern trigger

"Do any intervals overlap?" → **sort by start, compare neighbours**.

## 5. Plan before coding

- Sort by start.
- For i ≥ 1: if start[i] < end[i − 1] → false.
- Return true.

## 6. Code

See the approaches above.

## 7. Dry run

Sorted [0,30],[5,10],[15,20]: 5 < 30 → **false**.

## 8. Final complexity + extension

**O(n log n) time, O(1) extra space.** Extension: LC 253 Meeting Rooms II asks how many rooms are needed.

## What confused me / what clicked

- Sorting means only the previous meeting matters.
- Use `<` so back-to-back meetings are allowed.
- I didn't paste code for this one; it's the standard solution.
