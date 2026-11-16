// Prim's algorithm on the complete graph, with an array instead of a heap - O(n^2) time, O(n) space
class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();
        vector<int> minDist(n, INT_MAX);   // cheapest edge from the tree to each point
        vector<bool> inTree(n, false);
        minDist[0] = 0;
        int total = 0;

        for (int step = 0; step < n; step++) {
            int u = -1;
            for (int v = 0; v < n; v++) {
                if (!inTree[v] && (u == -1 || minDist[v] < minDist[u])) {
                    u = v;                 // closest point not in the tree yet
                }
            }
            inTree[u] = true;
            total += minDist[u];

            for (int v = 0; v < n; v++) {
                if (!inTree[v]) {
                    int d = abs(points[u][0] - points[v][0]) + abs(points[u][1] - points[v][1]);
                    minDist[v] = min(minDist[v], d);
                }
            }
        }
        return total;
    }
};
