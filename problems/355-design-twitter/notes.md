## 1. Restate + clarify

Design postTweet, getNewsFeed (10 most recent tweets by the user and people they follow, newest first), follow, unfollow.

Questions to ask:
- Following yourself or unfollowing someone you don't follow must be harmless.

## 2. Tiny example + edge case

post(1,5), feed(1) → [5]; follow(1,2), post(2,6), feed(1) → [6,5]; unfollow(1,2), feed(1) → [5].

## 3. Brute force + complexity

Collect every relevant tweet, sort by time, take 10: **O(T log T)** per feed.

## 4. Pattern trigger

"Newest k items from several time-ordered lists" → **merge k sorted lists with a heap**, stop early.

## 5. Plan before coding

- tweets[user] = list of {time, id}; following[user] = set.
- feed: users = followees + self; push each one's newest tweet {time, user, index}.
- Pop the newest, add its id, push that user's previous tweet; stop at 10.

## 6. Code

See the approaches above.

## 7. Dry run

Users 1 (11@0, 12@4), 2 (21@1, 22@3), 3 (31@2, 32@5); user 1 follows 2 and 3.
Heap starts {12@4, 22@3, 32@5} → pop 32 → push 31 → pop 12 → push 11 → pop 22 → … → [32, 12, 22, 31, 21, 11].

## 8. Final complexity + extension

**post / follow / unfollow O(1); getNewsFeed O(F + 10 log F).**

Same pattern: **LC 23 Merge k Sorted Lists**.

## What confused me / what clicked

- Timestamps, not tweet IDs, give the order.
- One tweet per user in the heap is enough because each list is sorted.
- Add yourself to the users set.
