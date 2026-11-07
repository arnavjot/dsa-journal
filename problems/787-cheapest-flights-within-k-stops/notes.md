## 1. Restate + clarify

Directed flights with prices. Return the cheapest price from src to dst using at most k stops (k + 1 flights), or −1.

## 2. Tiny example + edge case

Example 1 (k = 1) → **700**. 3 cities, [[0,1,100],[1,2,100],[0,2,500]]: k = 1 → 200, k = 0 → 500.

## 3. Brute force + complexity

Try every route of at most k + 1 flights: exponential.

## 4. Pattern trigger

"Cheapest path with a limit on the number of edges" → **BFS by levels (stops)** or **Bellman-Ford for k + 1 rounds**. Plain Dijkstra is not enough.

## 5. Plan before coding

- dist[src] = 0; queue (0 stops, src, 0).
- Pop; if stops > k skip; for each flight: cost + w < dist[next] → update, queue (stops + 1, next, cost + w).
- dist[dst] or −1.

## 6. Code

See the approaches above.

## 7. Dry run

Trap: 0→1→2→3 costs 3 but needs 2 stops; 0→3 costs 10. k = 1: BFS reaches city 3 at 1 stop with cost 10; the route through 2 would need stops = 2 > k → skipped → **10**.

## 8. Final complexity + extension

**About O(k · E)**, O(n) for the price array (+ queue).

Related: **LC 743 Network Delay Time** (Dijkstra, no stop limit), **LC 1631 Path With Minimum Effort**.

## What confused me / what clicked

- k stops = k + 1 flights.
- The stop limit is why Dijkstra alone fails: the cheapest-so-far route might be too long.
- Bellman-Ford needs a copy per round, or one round could use two flights.
