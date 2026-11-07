class Solution {
public:
    void dfs(int u, vector<vector<int>>& adj, vector<bool>& visited) {
        visited[u] = true;
        for (int v : adj[u])
            if (!visited[v]) dfs(v, adj, visited);
    }

    int countComponents(int n, vector<vector<int>>& edges) {
        vector<vector<int>> adj(n);
        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }
        vector<bool> visited(n, false);
        int components = 0;
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {          // a node no earlier DFS reached: a new component
                components++;
                dfs(i, adj, visited);
            }
        }
        return components;
    }
};
