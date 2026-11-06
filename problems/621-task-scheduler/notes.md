## 1. Restate + clarify

Each time unit the CPU runs one task or idles. Two runs of the **same** task need at least n units between them. Return the fewest time units to run everything.

## 2. Tiny example + edge case

AAABBB, n = 2 → **8** (A B · A B · A B). n = 0 → 6. AAAAAABCDEFG, n = 2 → **16**.

## 3. Brute force + complexity

Try every order with idles: exponential. Simulating greedily (always run the task with the most copies left) works: O(answer · log 26).

## 4. Pattern trigger

"Cooldown between equal items, minimise length" → **the most frequent item decides the frame** (greedy / counting).

## 5. Plan before coding

- Count frequencies; maxFreq = highest count, countMax = how many tasks have it.
- frame = (maxFreq − 1)·(n + 1) + countMax.
- Return max(tasks.size(), frame).

## 6. Code

See the approaches above.

## 7. Dry run

AAABBB, n = 2: maxFreq 3, countMax 2 → (3 − 1)·3 + 2 = **8**, and 8 ≥ 6 tasks → 8.
ACABDB, n = 1: maxFreq 2 (A, B), countMax 2 → 1·2 + 2 = 4 < 6 tasks → **6** (no idles).

## 8. Final complexity + extension

**Formula: O(m). Your simulation: O(answer · log 26).**

Extension: **LC 358 Rearrange String k Distance Apart** (same heap + cooldown queue, but output the order).

## Review of my solution

- **Correct** (matches an exact search on 1500 random cases).
- It simulates every tick, including idle ones, so it can take O(m·n) steps. The formula reads the answer straight from the counts.

## What confused me / what clicked

- Only the most frequent task(s) matter for idling.
- Last row = just the tied-for-top tasks.
- If gaps overflow, the answer is simply the task count.
