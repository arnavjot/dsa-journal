## 1. Restate + clarify

Design a class that, after each `add(val)`, returns the k-th largest number seen so far (including the starting nums).

Questions to ask:
- nums may start with k − 1 numbers; after the first add there are always at least k.

## 2. Tiny example + edge case

k = 3, nums [4,5,8,2]: add 3 → 4, add 5 → 5, add 10 → 5, add 9 → 8, add 4 → 8.
Edge case: k = 1 → the running maximum.

## 3. Brute force + complexity

Keep all numbers sorted and read all[size − k]: **O(n)** per add (insertion shifts).

## 4. Pattern trigger

"k-th largest, numbers keep coming" → **min-heap of size k**.

## 5. Plan before coding

- Constructor: push every num; pop whenever size > k.
- add: push val; pop if size > k; return top.

## 6. Code

See the approaches above.

## 7. Dry run

k = 3: after the constructor the heap is {4,5,8} (2 popped). add 3 → push, pop 3 → top 4. add 5 → push, pop 4 → {5,5,8} → 5. add 10 → pop 5 → {5,8,10} → 5. add 9 → pop 5 → {8,9,10} → 8.

## 8. Final complexity + extension

**O(log k) per add, O(k) space.**

Same idea: **LC 215 Kth Largest Element in an Array**, **LC 347 Top K Frequent**.

## What confused me / what clicked

- "k-th largest" → keep the k largest → their **minimum** is the answer → **min**-heap.
- Pop as soon as the size goes past k.
