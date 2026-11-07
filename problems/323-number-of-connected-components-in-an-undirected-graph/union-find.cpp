class Solution {
public:
    vector<int> parent;

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);

        return parent[x];
    }

    int countComponents(int n, vector<vector<int>>& edges) {

        parent.resize(n);

        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }

        int components = n;

        for (auto& edge : edges) {

            int u = edge[0];
            int v = edge[1];

            int pu = find(u);
            int pv = find(v);

            if (pu != pv) {
                parent[pu] = pv;
                components--;
            }
        }

        return components;
    }
};
