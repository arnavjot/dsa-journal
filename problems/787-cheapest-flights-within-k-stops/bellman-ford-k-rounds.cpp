class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        vector<int> dist(n, 1e9);
        dist[src] = 0;
        for (int round = 0; round <= k; round++) {      // round r allows r + 1 flights (r stops)
            vector<int> next = dist;                    // read last round, write this round
            for (auto& f : flights) {
                int u = f[0], v = f[1], w = f[2];
                if (dist[u] != 1e9 && dist[u] + w < next[v])
                    next[v] = dist[u] + w;
            }
            dist = next;
        }
        return dist[dst] == 1e9 ? -1 : dist[dst];
    }
};
