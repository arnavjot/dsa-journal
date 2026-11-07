class LRUCache {
public:
    class node {
    public:
        int key;
        int val;
        node* next;
        node* prev;
        node(int k, int v) {
            key = k;
            val = v;
        }
    };

    node* head = new node(-1, -1);
    node* tail = new node(-1, -1);
    int cap;
    unordered_map<int, node*> nodes;

    LRUCache(int capacity) {
        cap = capacity;
        head->next = tail;
        tail->prev = head;
    }

    void addnode(node* newnode) {
        node* temp = head->next;
        newnode->next = temp;
        newnode->prev = head;
        head->next = newnode;
        temp->prev = newnode;
    }

    void deletenode(node* delnode) {
        node* delprev = delnode->prev;
        node* delnext = delnode->next;
        delprev->next = delnext;
        delnext->prev = delprev;
    }

    int get(int key) {
        if (nodes.find(key) != nodes.end()) {
            // node* resnode = nodes[key];
            // int res = resnode->val;
            // nodes.erase(key);
            // deletenode(resnode);
            // addnode(resnode);
            // nodes[key] = head->next;
            // return res;
            node* resnode = nodes[key];
            int res = resnode->val;
            deletenode(resnode);
            addnode(resnode);
            return res;
        }
        return -1;
    }

    void put(int key, int value) {
        if (nodes.find(key) != nodes.end()) {
            node* existing = nodes[key];
            nodes.erase(key);
            deletenode(existing);
        }
        if (nodes.size() == cap) {
            nodes.erase(tail->prev->key);
            deletenode(tail->prev);
        }
        node* newNode = new node(key, value);
        addnode(newNode);
        nodes[key] = newNode;
    }
};
/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int paranodes_1 = obj->get(key);
 * obj->put(key,value);
 */
