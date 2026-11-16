## 1. Restate + clarify

n is happy if repeatedly replacing it by the sum of the squares of its digits eventually gives 1. Otherwise it loops forever. Return whether n is happy.

## 2. Tiny example + edge case

19 → 82 → 68 → 100 → **1** (happy). 2 → 4 → 16 → 37 → 58 → 89 → 145 → 42 → 20 → 4 … (**not** happy). 1 → **true**.

## 3. Brute force + complexity

Keep a set of seen values; stop on 1 or a repeat. Same time, O(cycle) extra space.

## 4. Pattern trigger

"A sequence that either ends or cycles" → **Floyd's cycle detection (slow/fast)**, like LC 141 Linked List Cycle.

## 5. Plan before coding

- findSquare(n): sum of digit squares.
- slow = fast = n.
- Step slow once, fast twice, until both are 1 (happy) or they meet elsewhere (cycle).

## 6. Code

See the approaches above.

## 7. Dry run

n = 19, step by step:

- Step 1: slow → 82, fast → 68.
- Step 2: slow → 68, fast → 1.
- Step 3: slow → 100, fast stays 1.
- Step 4: slow → **1**.

Both are 1 → **true**.

## 8. Final complexity + extension

**O(log n) time, O(1) space.** All unhappy numbers end in the same cycle 4 → 16 → 37 → 58 → 89 → 145 → 42 → 20, so checking for 4 also works.

## What confused me / what clicked

- Big numbers shrink fast (a 10-digit number gives at most 810), so the values must repeat.
- Floyd works on any "next value" function, not just linked lists.
- My do-while needs `do`, because slow == fast at the start.
- In my while version, fast reaches 1 first and stays there (f(1) = 1). The loop ends when slow gets there too.
