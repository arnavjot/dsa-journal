## 1. Restate + clarify

Change beginWord into endWord one letter at a time; every intermediate word must be in wordList. Return the number of words in the shortest such sequence, or 0.

Questions to ask:
- The count includes both ends. beginWord need not be in the list; endWord must be.

## 2. Tiny example + edge case

hit → cog with [hot,dot,dog,lot,log,cog] → **5** (hit → hot → dot → dog → cog). Without cog in the list → **0**.

## 3. Brute force + complexity

Build the graph by comparing every pair of words: **O(N² · L)**, then BFS.

## 4. Pattern trigger

"Fewest one-step transformations" → **BFS shortest path** on an implicit graph.

## 5. Plan before coding

- Set of words; queue (beginWord, 1); erase beginWord.
- Pop (word, steps): if word == endWord → steps.
- For each position, each letter: if the new word is in the set → erase it, queue (new, steps + 1).
- Queue empty → 0.

## 6. Code

See the approaches above.

## 7. Dry run

hit(1) → hot(2) → dot, lot(3) → dog, log(4) → cog(5) **found**.

## 8. Final complexity + extension

**O(N · L² · 26) time, O(N · L) space.**

Faster in practice: **bidirectional BFS** (grow from both ends, expand the smaller side). Related: **LC 126 Word Ladder II** (return all shortest ladders), **LC 433 Minimum Genetic Mutation**.

## What confused me / what clicked

- Generating neighbours with 26 letters per position beats comparing against every word.
- Mark visited **when queuing** (erase or visited set), not when popping.
- Both my versions are the same BFS; one counts levels, the other stores steps per word.
