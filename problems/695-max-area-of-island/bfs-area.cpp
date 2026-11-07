class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size(), best = 0;
        int d[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        for (int r = 0; r < m; r++)
            for (int c = 0; c < n; c++) {
                if (grid[r][c] != 1) continue;
                queue<pair<int, int>> q;
                q.push({r, c});
                grid[r][c] = 0;                       // mark when queued
                int area = 0;
                while (!q.empty()) {
                    auto [x, y] = q.front();
                    q.pop();
                    area++;                           // each popped cell is one unit of area
                    for (auto& e : d) {
                        int a = x + e[0], b = y + e[1];
                        if (a >= 0 && b >= 0 && a < m && b < n && grid[a][b] == 1) {
                            grid[a][b] = 0;
                            q.push({a, b});
                        }
                    }
                }
                best = max(best, area);
            }
        return best;
    }
};
