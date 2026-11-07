## 1. Restate + clarify

Design a stack with `push`, `pop`, `top` and `getMin`, **all O(1)**.

Questions to ask:
- Called on an empty stack? No, pop/top/getMin always have something.
- Values? Any int (−2³¹ to 2³¹−1).
- Up to 3·10⁴ calls.

## 2. Tiny example + edge case

`push -2, push 0, push -3, getMin → -3, pop, top → 0, getMin → -2`.

Edge case: equal mins. `push 3, push 3, pop, getMin` must still be 3.

## 3. Brute force + complexity

Plain stack; `getMin` scans every value. **getMin O(n)**, the rest O(1). Fails the "all O(1)" rule.

## 4. Pattern trigger

"getMin in O(1) on a stack that changes" → **remember the min at every level**: store `(val, min so far)` with each element.

## 5. Plan before coding

- `vector<pair<int,int>> st`.
- `push(val)`: min = empty ? val : min(val, st.back().second); push `(val, min)`.
- `pop`: `pop_back()`.
- `top`: `st.back().first`. `getMin`: `st.back().second`.

## 6. Code

See the approaches above.

## 7. Dry run

| call | stack after (bottom → top) | returns |
|---|---|---|
| push(-2) | (-2,-2) | |
| push(0) | (-2,-2) (0,-2) | |
| push(-3) | (-2,-2) (0,-2) (-3,-3) | |
| getMin() | same | **-3** |
| pop() | (-2,-2) (0,-2) | |
| top() | same | **0** |
| getMin() | same | **-2** |

After the pop, the old min -2 is still saved in the pair (0,-2). Nothing was recomputed.

## 8. Final complexity + extension

**O(1) every operation, O(n) space.**

Extensions:
- Save space with a second stack that only stores a new min when `val <= current min`.
- **Max stack**: same idea with max.

## What confused me / what clicked

- One "current min" variable breaks as soon as you pop the min.
- Each pair remembers the min **at its level**, which never changes while it's on the stack.
- `st.back()` is the top of a vector used as a stack.
- Equal values: `min(oldMin, val)` stores the duplicate min again, so popping one copy is safe.
