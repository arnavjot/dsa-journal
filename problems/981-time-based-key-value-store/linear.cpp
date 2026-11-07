class TimeMap {
public:
    unordered_map<string, vector<pair<int, string>>> mp;

    TimeMap() {}

    void set(string key, string value, int timestamp) {
        mp[key].push_back({timestamp, value});
    }

    string get(string key, int timestamp) {
        if (mp.find(key) == mp.end()) return "";
        auto& values = mp[key];
        // walk back from the newest until a time <= timestamp
        for (int i = values.size() - 1; i >= 0; i--) {
            if (values[i].first <= timestamp) return values[i].second;
        }
        return "";
    }
};
