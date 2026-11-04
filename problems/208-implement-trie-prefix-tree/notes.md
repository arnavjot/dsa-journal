## 1. Restate + clarify

Build a Trie with `insert(word)`, `search(word)` (was this exact word inserted?) and `startsWith(prefix)` (does any inserted word start with it?).

Questions to ask:
- Lowercase a–z only. Up to 3·10⁴ calls, words up to 2000 letters.

## 2. Tiny example + edge case

insert("apple"); search("apple") → true; search("app") → **false**; startsWith("app") → true; insert("app"); search("app") → true.

## 3. Brute force + complexity

Keep a set of words: search O(L), but startsWith must scan every word: **O(n·L)**. Storing every prefix too makes insert **O(L²)**.

## 4. Pattern trigger

"Insert words, answer prefix questions fast" → **Trie** (prefix tree).

## 5. Plan before coding

- Node: `links[26]` (NULL by default) and `flag`.
- insert: for each letter, create the link if missing, move down; set flag at the end.
- search: for each letter, a missing link → false; at the end return flag.
- startsWith: same walk; at the end return true.

## 6. Code

See the approaches above.

## 7. Dry run

insert car, insert cat:

```
root → c → a → r (flag)
              → t (flag)
```

search("ca") → path exists, flag false → **false**. startsWith("ca") → **true**. search("cow") → no 'o' under c → **false**.

## 8. Final complexity + extension

**O(L) per call; space O(total letters × 26).**

Extensions: **LC 211** (search with '.' wildcards: try every link), **LC 212 Word Search II** (trie + grid DFS), and counting words with a prefix (store a counter in each node).

## What confused me / what clicked

- A path existing ≠ a word existing: that's what `flag` is for.
- search and startsWith are the same walk; only the last line differs.
- Shared prefixes share nodes, which is where the trie saves space and time.
