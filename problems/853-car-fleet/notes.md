## 1. Restate + clarify

n cars drive toward `target`. A faster car that catches a slower one can't pass; it slows down and they become a **fleet**. Cars meeting exactly at the target also count as one fleet. How many fleets arrive?

Questions to ask:
- Positions distinct? Yes.
- Can cars pass? No.
- Size? Up to 10⁵ cars.

## 2. Tiny example + edge case

target 12, positions `[10,8,0,5,3]`, speeds `[2,4,1,1,3]`

| position | speed | time to target |
|---|---|---|
| 10 | 2 | 1 |
| 8 | 4 | 1 |
| 5 | 1 | 7 |
| 3 | 3 | 3 |
| 0 | 1 | 12 |

Fleets: {10, 8}, {5, 3}, {0} → **3**.

Edge cases:
- One car → 1.
- Everyone the same speed (`[0,4,8]`, speed 1): no one catches anyone → n fleets.

## 3. Brute force + complexity

Simulate time steps until everyone arrives, merging cars that meet. Messy (fractional meeting times) and slow.

## 4. Pattern trigger

"Cars ahead block cars behind" → sort by position, process **front to back**, and compare **arrival times** to the fleet ahead → a stack of fleet times (monotonic: times only increase going back).

## 5. Plan before coding

- `time = (target - position) / speed` as a double.
- Sort by position descending.
- For each car: if the stack is empty or `time > st.top()` → push (new fleet). Otherwise it joins.
- Return `st.size()`.

## 6. Code

See the approaches above.

## 7. Dry run

Sorted (closest first): 10 (t 1), 8 (t 1), 5 (t 7), 3 (t 3), 0 (t 12)

| car | time | st.top() | action | stack |
|---|---|---|---|---|
| 10 | 1 | — | push | 1 |
| 8 | 1 | 1 | 1 > 1? no → joins | 1 |
| 5 | 7 | 1 | push | 1 7 |
| 3 | 3 | 7 | 3 > 7? no → joins | 1 7 |
| 0 | 12 | 7 | push | 1 7 12 |

Return **3**.

## 8. Final complexity + extension

**O(n log n) time** (sorting), **O(n) space**.

Extension: **LC 1776 Car Fleet II**: when does each car collide with the next? Uses a monotonic stack from the back.

## What confused me / what clicked

- Compare **times**, not speeds: a fast car far back may still arrive last.
- Process from the car **closest to the target**, because only cars ahead can slow you down.
- `time <= top` → joins (equal means meeting exactly at the target, still one fleet).
- Nothing is ever popped; a joining car just takes the fleet's time.
- Use `double`: (12 − 3) / 3 is fine, but (10 − 3) / 2 = 3.5 would be cut to 3 with ints.
