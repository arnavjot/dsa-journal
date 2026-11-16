## 1. Restate + clarify

Given airline tickets [from, to], rebuild the trip that starts at JFK, uses every ticket exactly once, and is smallest in dictionary order when there's a choice. A valid trip is guaranteed.

## 2. Tiny example + edge case

[[MUC,LHR],[JFK,MUC],[SFO,SJC],[LHR,SFO]] → **JFK, MUC, LHR, SFO, SJC**. [[JFK,KUL],[JFK,NRT],[NRT,JFK]] → **JFK, NRT, JFK, KUL**. Taking KUL first would strand you.

## 3. Brute force + complexity

Backtracking: try destinations in sorted order and undo when stuck. Exponential in the worst case.

## 4. Pattern trigger

"Use every edge exactly once" → **Eulerian path, Hierholzer's algorithm**.

## 5. Plan before coding

- graph[from] = min-heap of destinations.
- dfs(a): while a has tickets, pop the smallest and dfs it; then route.push_back(a).
- dfs("JFK"), then reverse route.

## 6. Code

See the approaches above.

## 7. Dry run

Tickets JFK→KUL, JFK→NRT, NRT→JFK:

- dfs(JFK) takes KUL (smallest). KUL has no tickets → route = [KUL].
- Back at JFK, take NRT. NRT → JFK.
- JFK has no tickets left → route = [KUL, JFK].
- Back to NRT → [KUL, JFK, NRT].
- Back to JFK → [KUL, JFK, NRT, JFK].

Reversed: **JFK, NRT, JFK, KUL**.

## 8. Final complexity + extension

**O(E log E) time, O(E) space.** Related: LC 753 Cracking the Safe and LC 2097 Valid Arrangement of Pairs (also Eulerian paths).

## What confused me / what clicked

- Greedy smallest-first alone fails at dead ends; post-order fixes it.
- The route comes out backwards.
- I didn't paste code for this one; it's mine.
