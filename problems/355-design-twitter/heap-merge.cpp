class Twitter {
private:
    int timestamp = 0;

    unordered_map<int, vector<pair<int, int>>> tweets;
    unordered_map<int, unordered_set<int>> following;

public:
    Twitter() {

    }

    void postTweet(int userId, int tweetId) {
        tweets[userId].push_back({timestamp++, tweetId});
    }

    vector<int> getNewsFeed(int userId) {
        priority_queue<tuple<int, int, int>> maxHeap;
        unordered_set<int> users = following[userId];
        users.insert(userId);

        for (int user : users) {
            if (!tweets[user].empty()) {
                int index = tweets[user].size() - 1;
                auto [time, tweetId] = tweets[user][index];
                maxHeap.push({time, user, index});
            }
        }

        vector<int> feed;

        while (!maxHeap.empty() && feed.size() < 10) {
            auto [time, user, index] = maxHeap.top();
            maxHeap.pop();
            feed.push_back(tweets[user][index].second);

            if (index > 0) {
                int nextIndex = index - 1;
                int nextTime = tweets[user][nextIndex].first;
                maxHeap.push({nextTime, user, nextIndex});
            }
        }
        return feed;
    }

    void follow(int followerId, int followeeId) {
        following[followerId].insert(followeeId);
    }

    void unfollow(int followerId, int followeeId) {
        following[followerId].erase(followeeId);
    }
};

/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter* obj = new Twitter();
 * obj->postTweet(userId,tweetId);
 * vector<int> param_2 = obj->getNewsFeed(userId);
 * obj->follow(followerId,followeeId);
 * obj->unfollow(followerId,followeeId);
 */
