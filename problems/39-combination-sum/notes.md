## 1. Restate + clarify

Distinct candidates, a target. Return all unique combinations that sum to target; a number may be used **any number of times**.

## 2. Tiny example + edge case

`[2,3,6,7]`, 7 → [[2,2,3],[7]]. `[2,3,5]`, 8 → [[2,2,2,2],[2,3,3],[3,5]]. `[2]`, 1 → [].

## 3. Brute force + complexity

Try every multiset of candidates up to the target: exponential, with repeats in different orders unless you control the order.

## 4. Pattern trigger

"All combinations reaching a target, with reuse" → **backtracking: pick (stay) or skip (move on)**.

## 5. Plan before coding

- target == 0 → save, return. index == n or target < 0 → return.
- Pick: push, dfs(index, target − c), pop.
- Skip: dfs(index + 1, target).

## 6. Code

See the approaches above.

## 7. Dry run

`[3,4]`, 7: pick 3 (t 4) → pick 3 (t 1) → pick 3 (t −2) ✗ → skip to 4 (t 1): pick ✗, end ✗ → back: skip 3 at t 4 → pick 4 (t 0) ✓ **[3,4]**.

## 8. Final complexity + extension

Exponential (roughly O(2^(t/m))), recursion depth ≤ t / smallest candidate.

Extensions: **LC 40** (each used once, duplicates in input), **LC 216**, **LC 377** (order matters → DP).

## What confused me / what clicked

- Pick keeps the **same index** (reuse); skip moves on for good.
- Index order prevents [2,3] and [3,2] from both appearing.
- target is "what's still missing".
