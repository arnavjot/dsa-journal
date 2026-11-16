## 1. Restate + clarify

Design add(point) and count(point). count returns how many ways to pick three stored points that, together with the query, form an axis-aligned square with positive area. Duplicate points count separately.

## 2. Tiny example + edge case

add (3,10), (11,2), (3,2); count (11,10) → **1**; count (14,8) → **0**; add (11,2); count (11,10) → **2**.

## 3. Brute force + complexity

For each query, try every triple of stored points: O(n³).

## 4. Pattern trigger

"Count axis-aligned squares with one fixed corner" → **enumerate the diagonal corner**, then look up the other two.

## 5. Plan before coding

- add: cnt[x][y]++; remember (x, y) if it is new.
- count: for each distinct (px, py) with |px − x| == |py − y| and px != x: ans += cnt[px][py] × cnt[x][py] × cnt[px][y].

## 6. Code

See the approaches above.

## 7. Dry run

After the 2nd add of (11, 2), count (11, 10): the diagonal (3, 2) has dx = 8, dy = 8. The corners are (11, 2) with 2 copies and (3, 10) with 1 copy, so 1 × 2 × 1 = **2**.

## 8. Final complexity + extension

**add O(1), count O(P), space O(P).** Related: LC 939 Minimum Area Rectangle, LC 963 Minimum Area Rectangle II.

## What confused me / what clicked

- The query plus its opposite corner fix the square.
- Duplicate points multiply the count.
- I didn't paste code for this one; it's mine.
