class Twitter {
    int timestamp = 0;
    unordered_map<int, vector<pair<int, int>>> tweets;      // user → {time, tweetId}
    unordered_map<int, unordered_set<int>> following;
public:
    Twitter() {}

    void postTweet(int userId, int tweetId) { tweets[userId].push_back({timestamp++, tweetId}); }

    vector<int> getNewsFeed(int userId) {
        vector<pair<int, int>> all = tweets[userId];          // copy every relevant tweet…
        for (int f : following[userId])
            if (f != userId) all.insert(all.end(), tweets[f].begin(), tweets[f].end());
        sort(all.rbegin(), all.rend());                        // …newest first: O(T log T)
        vector<int> feed;
        for (int i = 0; i < all.size() && i < 10; i++) feed.push_back(all[i].second);
        return feed;
    }

    void follow(int followerId, int followeeId) { following[followerId].insert(followeeId); }
    void unfollow(int followerId, int followeeId) { following[followerId].erase(followeeId); }
};
