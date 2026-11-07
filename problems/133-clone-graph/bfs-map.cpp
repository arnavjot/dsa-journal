class Solution {
public:
    Node* cloneGraph(Node* node) {
        if (node == nullptr) return nullptr;
        unordered_map<Node*, Node*> mp;              // original → its copy
        mp[node] = new Node(node->val);
        queue<Node*> q;
        q.push(node);
        while (!q.empty()) {
            Node* cur = q.front();
            q.pop();
            for (Node* nb : cur->neighbors) {
                if (mp.find(nb) == mp.end()) {       // first time we see nb: copy it, visit it later
                    mp[nb] = new Node(nb->val);
                    q.push(nb);
                }
                mp[cur]->neighbors.push_back(mp[nb]);   // link the copies
            }
        }
        return mp[node];
    }
};
