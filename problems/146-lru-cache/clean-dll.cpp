class LRUCache {
    struct Node {
        int key, val;
        Node* prev = nullptr;
        Node* next = nullptr;
        Node(int k, int v) : key(k), val(v) {}
    };

    int cap;
    unordered_map<int, Node*> pos;      // key → its node in the list
    Node* head = new Node(-1, -1);      // dummy: head->next = most recently used
    Node* tail = new Node(-1, -1);      // dummy: tail->prev = least recently used

    void unlink(Node* n) {
        n->prev->next = n->next;
        n->next->prev = n->prev;
    }

    void pushFront(Node* n) {
        n->next = head->next;
        n->prev = head;
        head->next->prev = n;
        head->next = n;
    }

public:
    LRUCache(int capacity) : cap(capacity) {
        head->next = tail;
        tail->prev = head;
    }

    int get(int key) {
        auto it = pos.find(key);
        if (it == pos.end()) return -1;
        Node* n = it->second;
        unlink(n);                      // just used → move to the front
        pushFront(n);
        return n->val;
    }

    void put(int key, int value) {
        auto it = pos.find(key);
        if (it != pos.end()) {          // key exists: update in place, move to the front
            Node* n = it->second;
            n->val = value;
            unlink(n);
            pushFront(n);
            return;
        }
        if ((int)pos.size() == cap) {   // full: evict the least recently used
            Node* lru = tail->prev;
            unlink(lru);
            pos.erase(lru->key);
            delete lru;                 // free it (no leak)
        }
        Node* n = new Node(key, value);
        pushFront(n);
        pos[key] = n;
    }

    ~LRUCache() {
        Node* cur = head;
        while (cur) {
            Node* nxt = cur->next;
            delete cur;
            cur = nxt;
        }
    }
};
