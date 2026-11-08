## 1. Restate + clarify

Words are sorted in an unknown alphabet. Return any order of the letters that fits, or "" if none does. Every letter that appears must be in the answer. Ask: can words repeat? (yes, equal neighbours give no rule) What if a word comes before its own prefix? (impossible → "").

## 2. Tiny example + edge case

["wrt","wrf","er","ett","rftt"]:

| pair | first difference | rule |
|---|---|---|
| wrt, wrf | t vs f | t → f |
| wrf, er | w vs e | w → e |
| er, ett | r vs t | r → t |
| ett, rftt | e vs r | e → r |

Chain w → e → r → t → f, so **"wertf"**.

Edge cases: ["z","x","z"] gives z → x and x → z, a cycle → "". ["abc","ab"] → "" (prefix after the longer word).

## 3. Brute force + complexity

Try every order of the k letters and check the list: O(k! · C). Fine for 5 letters, hopeless for 26.

## 4. Pattern trigger

"Find an order that respects 'x before y' rules" → **topological sort**. Nodes = letters, edges = rules from neighbouring words.

## 5. Plan before coding

- Mark every letter that appears (indegree 0, or present = true).
- For each neighbouring pair: skip the common prefix. Ran out of letters? If the first word is longer → return "". Otherwise the first differing letters give one edge u → v (count it once).
- Kahn: queue indegree-0 letters, take them in order, lower their followers' indegrees.
- Fewer letters taken than appear → cycle → "".

## 6. Code

See the approaches above.

## 7. Dry run

Example 1: indegrees w 0, e 1, r 1, t 1, f 1. Queue {w} → take w (e drops to 0) → take e (r drops to 0) → take r → take t → take f → **"wertf"**, all 5 letters placed.

["z","x","z"]: z → x and x → z, both indegree 1, the queue starts empty, 0 of 2 placed → **""**.

## 8. Final complexity + extension

**O(C) time** for C total characters, **O(1) extra space** (at most 26 letters and a 26 × 26 rule table).

Extension: return every valid alphabet (backtracking over the indegree-0 choices), or check whether the order is unique (the queue never holds more than one letter).

Related: **LC 207 / 210 Course Schedule**, **LC 953 Verifying an Alien Dictionary** (the reverse: order given, check the words).

## What confused me / what clicked

- Only the **first** differing letter matters; after it, the rest of the two words say nothing.
- Compare **neighbours** only: if every neighbouring pair is in order, the whole list is.
- Two separate "impossible" checks: the prefix trap (found while building rules) and a cycle (found after Kahn's).
- Letters with no rules still go in the answer: they start at indegree 0.
