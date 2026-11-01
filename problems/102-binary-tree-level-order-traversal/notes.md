## 1. Restate + clarify

Return the node values **level by level**, each level left to right.

Questions to ask:
- Empty tree → `[]`.
- Up to 2000 nodes.

## 2. Tiny example + edge case

`[3,9,20,null,null,15,7]` → **`[[3],[9,20],[15,7]]`**.

Edge cases: `[]` → `[]`. `[1]` → `[[1]]`. Lopsided trees still give one vector per depth.

## 3. Brute force + complexity

DFS carrying the depth, appending to `ans[depth]`: **O(n) time**, same answer.

## 4. Pattern trigger

"Level by level" → **BFS with a queue**.

## 5. Plan before coding

- Push root.
- While the queue isn't empty: `size = q.size()`, pop `size` nodes into `level`, push their children, add `level` to `ans`.

## 6. Code

See the approaches above.

## 7. Dry run

`[3,9,20,null,null,15,7]`

| round | size | popped | queue after | ans |
|---|---|---|---|---|
| 1 | 1 | 3 | 9, 20 | [[3]] |
| 2 | 2 | 9, 20 | 15, 7 | [[3],[9,20]] |
| 3 | 2 | 15, 7 | — | [[3],[9,20],[15,7]] |

## 8. Final complexity + extension

**O(n) time, O(w) space** (w = widest level).

Extensions: **LC 107** (bottom-up: reverse ans), **LC 103** (zigzag: reverse every other level), **LC 199** (right side view: last node of each level).

## What confused me / what clicked

- Saving `size` first is what separates the levels.
- The queue never holds more than about two levels at once.
- The inner variable named `root` shadows the parameter; fine here, but `node` would be clearer.
