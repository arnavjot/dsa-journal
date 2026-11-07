## 1. Restate + clarify

Build a key-value store where each `set(key, value, timestamp)` keeps old versions. `get(key, timestamp)` returns the value set at the **latest time ≤ timestamp**, or `""` if there is none.

Questions to ask:
- Are set timestamps increasing? **Yes, strictly** (LeetCode promises it). That's what makes binary search possible.
- Missing key, or every time is after `timestamp` → `""`.

## 2. Tiny example + edge case

set(foo, bar, 1) → get(foo, 1) = **bar**, get(foo, 3) = **bar**. set(foo, bar2, 4) → get(foo, 4) = **bar2**, get(foo, 5) = **bar2**.
Edge cases: get(foo, 0) = **""** (too early); get(baz, 1) = **""** (never set).

## 3. Brute force + complexity

Walk the key's list from the newest back to the first time ≤ t: get is **O(n)** per call.

## 4. Pattern trigger

Sorted list + "last element ≤ target" → **binary search** (upper bound − 1).

## 5. Plan before coding

- `unordered_map<string, vector<pair<int, string>>> mp`.
- set: `mp[key].push_back({timestamp, value})`; it stays sorted by time.
- get: key missing → `""`. Else left = 0, right = n − 1, ans = "".
  - `values[mid].first <= timestamp` → ans = its value, **left = mid + 1** (look for a later one).
  - else → right = mid − 1.
- Return ans.

## 6. Code

See the approaches above.

## 7. Dry run

times `[1,3,5,7,9,11,13]` (values a…g), get(k, 8)

| left | right | mid | time | ≤ 8? | ans | next |
|---|---|---|---|---|---|---|
| 0 | 6 | 3 | 7 | yes | d | left = 4 |
| 4 | 6 | 5 | 11 | no | d | right = 4 |
| 4 | 4 | 4 | 9 | no | d | right = 3 |

left > right → return **d**.

## 8. Final complexity + extension

**set O(1), get O(log n); space O(total sets).**

One-liner alternative with the STL:

```cpp
auto it = upper_bound(values.begin(), values.end(), timestamp,
    [](int t, const pair<int, string>& p) { return t < p.first; });
return it == values.begin() ? "" : prev(it)->second;
```

`upper_bound` finds the first time **> t**; the one before it is the answer. Same pattern: **LC 1146 Snapshot Array**.

## What confused me / what clicked

- It's "last ≤ t", so a hit doesn't stop the search: **save it and go right**.
- `ans = ""` handles "too early" without any special case.
- `auto&` avoids copying the vector on every get.
