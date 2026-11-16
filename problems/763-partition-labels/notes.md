## 1. Restate + clarify

Split s into as many parts as possible so each letter appears in at most one part. Return the part sizes.

## 2. Tiny example + edge case

"ababcbacadefegdehijhklij" → **[9,7,8]**. "eccbbbbdec" → **[10]**. "abc" → **[1,1,1]**.

## 3. Brute force + complexity

Try all 2^(n − 1) cut sets: exponential.

## 4. Pattern trigger

"Each letter must stay in one part" → **last occurrence + greedy cut**.

## 5. Plan before coding

- last[c] for each letter.
- start = end = 0; for each i: end = max(end, last[s[i]]); if i == end: push end − start + 1; start = i + 1.

## 6. Code

See the approaches above.

## 7. Dry run

Example 1: a's last index is 8, so end = 8. b (5), c (7) and so on stay inside. At i = 8, i == end → cut, size **9**.

## 8. Final complexity + extension

**O(n) time, O(1) space.** Related: LC 56 Merge Intervals (each letter is an interval from its first to its last index; merge them).

## What confused me / what clicked

- Each letter is really an interval [first, last]; the parts are the merged intervals.
- Cut the moment i reaches end.
- I didn't paste code for this one; it's mine.
