## 1. Restate + clarify

Stations on a circle: gas[i] fuel, cost[i] to drive to the next one. Return the start that lets you go all the way round, or −1. The answer is unique if it exists.

## 2. Tiny example + edge case

gas [1,2,3,4,5], cost [3,4,5,1,2] → **3**. gas [2,3,4], cost [3,4,3] → **−1**.

## 3. Brute force + complexity

Try every start and simulate the full circle: O(n²).

## 4. Pattern trigger

"Circular trip, running balance" → **greedy reset when the tank goes negative**.

## 5. Plan before coding

- total = tank = start = 0.
- For each i: add gas[i] − cost[i] to both; if tank < 0: start = i + 1, tank = 0.
- Return total ≥ 0 ? start : −1.

## 6. Code

See the approaches above.

## 7. Dry run

Example 1, gains −2, −2, −2, 3, 3:

- i = 0: tank −2 → start 1.
- i = 1: −2 → start 2.
- i = 2: −2 → start 3.
- i = 3: tank 3.
- i = 4: tank 6.

total = 0 ≥ 0 → **3**.

## 8. Final complexity + extension

**O(n) time, O(1) space.**

## What confused me / what clicked

- A failure at i rules out every start from s to i at once.
- The total decides whether any answer exists; the pass finds which one.
- I didn't paste code for this one; it's mine.
