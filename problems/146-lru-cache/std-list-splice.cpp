class LRUCache {
    int cap;
    list<pair<int, int>> items;                               // front = most recent: {key, value}
    unordered_map<int, list<pair<int, int>>::iterator> pos;   // key → where it sits in items

public:
    LRUCache(int capacity) : cap(capacity) {}

    int get(int key) {
        auto it = pos.find(key);
        if (it == pos.end()) return -1;
        items.splice(items.begin(), items, it->second);       // move to the front, O(1)
        return it->second->second;
    }

    void put(int key, int value) {
        auto it = pos.find(key);
        if (it != pos.end()) {
            it->second->second = value;
            items.splice(items.begin(), items, it->second);
            return;
        }
        if ((int)items.size() == cap) {
            pos.erase(items.back().first);                    // evict the least recent
            items.pop_back();
        }
        items.push_front({key, value});
        pos[key] = items.begin();
    }
};
