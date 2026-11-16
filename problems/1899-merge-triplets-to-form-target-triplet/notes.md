## 1. Restate + clarify

You can merge two triplets into their element-wise max, as often as you like. Can you produce exactly the target triplet?

## 2. Tiny example + edge case

[[2,5,3],[1,8,4],[1,7,5]], target [2,7,5] → **true** (merge the 1st and 3rd). [[3,4,5],[4,5,6]], target [3,2,5] → **false**.

## 3. Brute force + complexity

Try every subset and take its max: O(2ⁿ).

## 4. Pattern trigger

"Merge = max, values only grow" → **skip anything that overshoots; merge the rest**.

## 5. Plan before coding

- found = {false, false, false}.
- For each triplet: skip if any value > target; else mark found[k] where t[k] == target[k].
- Return all found.

## 6. Code

See the approaches above.

## 7. Dry run

Example 3, target [5,5,5]:

- [2,5,3] fits → found b.
- [2,3,4] fits.
- [1,2,5] → found c.
- [5,2,3] → found a.

All three → **true**.

## 8. Final complexity + extension

**O(n) time, O(1) space.**

## What confused me / what clicked

- Merging only ever increases values, so an overshoot can never be undone.
- Merging every safe triplet together is the best you can do.
- I didn't paste code for this one; it's mine.
