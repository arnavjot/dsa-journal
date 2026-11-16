// Dijkstra where a path costs its highest cell - O(n^2 log n) time, O(n^2) space
class Solution {
public:
    int swimInWater(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<vector<bool>> seen(n, vector<bool>(n, false));
        priority_queue<array<int, 3>, vector<array<int, 3>>, greater<array<int, 3>>> pq;   // {time needed, row, col}
        pq.push({grid[0][0], 0, 0});
        seen[0][0] = true;
        int dr[4] = {1, -1, 0, 0}, dc[4] = {0, 0, 1, -1};

        while (!pq.empty()) {
            auto [t, r, c] = pq.top();
            pq.pop();
            if (r == n - 1 && c == n - 1) return t;         // the cheapest way to reach the corner
            for (int k = 0; k < 4; k++) {
                int nr = r + dr[k], nc = c + dc[k];
                if (nr < 0 || nc < 0 || nr >= n || nc >= n || seen[nr][nc]) continue;
                seen[nr][nc] = true;
                pq.push({max(t, grid[nr][nc]), nr, nc});    // the path's time is its highest cell
            }
        }
        return -1;
    }
};
