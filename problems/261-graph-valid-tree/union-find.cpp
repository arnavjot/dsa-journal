class Solution {
public:
    vector<int> parent;

    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }

    bool validTree(int n, vector<vector<int>>& edges) {
        if (edges.size() != n - 1) return false;     // a tree has exactly n − 1 edges
        parent.resize(n);
        for (int i = 0; i < n; i++) parent[i] = i;
        for (auto& e : edges) {
            int pu = find(e[0]), pv = find(e[1]);
            if (pu == pv) return false;              // already connected → this edge makes a cycle
            parent[pu] = pv;
        }
        return true;                                 // n − 1 merges with no cycle → one connected tree
    }
};
