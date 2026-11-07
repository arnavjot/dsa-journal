class Solution {
public:
    bool isSafe(int i, int j, vector<vector<char>>& grid, vector<vector<bool>>& vis) {
        int n = grid.size();
        int m = grid[0].size();
        if (i >= 0 && i < n && j >= 0 && j < m && grid[i][j] == '1' && !vis[i][j]) {
            return true;
        }
        return false;
    }

    void bfs(int i, int j, vector<vector<char>>& grid, vector<vector<bool>>& vis) {
        queue<pair<int, int>> q;
        q.push({i, j});
        vis[i][j] = true;

        int dx[] = {-1, 0, 1, 0};
        int dy[] = {0, 1, 0, -1};

        while (!q.empty()) {
            auto frontNode = q.front();
            q.pop();

            int tempX = frontNode.first;
            int tempY = frontNode.second;
            for (int k = 0; k < 4; k++) {
                int newX = tempX + dx[k];
                int newY = tempY + dy[k];
                if (isSafe(newX, newY, grid, vis)) {
                    q.push({newX, newY});
                    vis[newX][newY] = true;
                }
            }
        }
    }

    int numIslands(vector<vector<char>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<bool>> vis(n, vector<bool>(m, false));
        int count = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (!vis[i][j] && grid[i][j] == '1') {
                    bfs(i, j, grid, vis);
                    count++;
                }
            }
        }
        return count;
    }
};
