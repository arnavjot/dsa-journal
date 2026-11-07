class Solution {
public:
    // Before adding edge u-v, check with DFS whether u can already reach v.
    bool reach(vector<vector<int>>& adj, int u, int target, vector<bool>& seen) {
        if (u == target) return true;
        seen[u] = true;
        for (int w : adj[u])
            if (!seen[w] && reach(adj, w, target, seen)) return true;
        return false;
    }

    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        vector<vector<int>> adj(n + 1);
        for (auto& e : edges) {
            vector<bool> seen(n + 1, false);
            if (reach(adj, e[0], e[1], seen)) return e;   // already connected → this edge makes a cycle
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }
        return {};
    }
};
