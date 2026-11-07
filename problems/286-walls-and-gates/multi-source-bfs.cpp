class Solution {
public:
    void wallsAndGates(vector<vector<int>>& rooms) {

        int m = rooms.size();
        int n = rooms[0].size();

        queue<pair<int, int>> q;

        vector<vector<int>> directions = {
            {0, 1}, {0, -1}, {1, 0}, {-1, 0}
        };

        // Add all gates to the queue
        for (int r = 0; r < m; r++) {
            for (int c = 0; c < n; c++) {
                if (rooms[r][c] == 0) {
                    q.push({r, c});
                }
            }
        }

        // Multi-source BFS
        while (!q.empty()) {

            auto [r, c] = q.front();
            q.pop();

            for (auto& dir : directions) {

                int nr = r + dir[0];
                int nc = c + dir[1];

                if (nr < 0 || nc < 0 || nr >= m || nc >= n)
                    continue;

                if (rooms[nr][nc] != INT_MAX)
                    continue;

                rooms[nr][nc] = rooms[r][c] + 1;

                q.push({nr, nc});
            }
        }
    }
};
