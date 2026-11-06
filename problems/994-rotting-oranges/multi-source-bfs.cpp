class Solution {
public:
    // does dfs solution work fine here?
    bool isSafe(int x, int y, int n, int m) {
        return (x >= 0 && x < n && y >= 0 && y < m);
    }

    int orangesRotting(vector<vector<int>>& grid) {
        vector<vector<int>> temp = grid;
        queue<pair<pair<int, int>, int>> q;
        int minTime = 0;
        int n = grid.size();
        int m = grid[0].size();

        // find all rotten oranges and put them in the queue
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (temp[i][j] == 2) {
                    q.push({{i, j}, 0});
                }
            }
        }

        // bfs logic
        while (!q.empty()) {
            auto frontNode = q.front();
            q.pop();
            int tempX = frontNode.first.first;
            int tempY = frontNode.first.second;
            int frontTime = frontNode.second;
            int dx[] = {-1, 0, 1, 0};
            int dy[] = {0, 1, 0, -1};
            for (int i = 0; i < 4; i++) {
                int newX = tempX + dx[i];
                int newY = tempY + dy[i];
                if (isSafe(newX, newY, n, m) && temp[newX][newY] == 1) {
                    q.push({{newX, newY}, frontTime + 1});
                    // mark this orange as rotten
                    temp[newX][newY] = 2;
                    minTime = max(minTime, frontTime + 1);
                }
            }
        }

        // Check if there are any fresh oranges left
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (temp[i][j] == 1) {
                    return -1;
                }
            }
        }

        return minTime;

        /*  DFS explores one path deeply before others. That creates problems:

            Incorrect Time Calculation:
            DFS can take a longer path first and rot a fresh orange later than it would have via another path.
            It does not guarantee the minimum time to reach a fresh orange.

            Complexity & Redundancy:
            DFS needs careful backtracking or visited marking.
            **Without proper pruning, the same cell might be visited multiple times from different paths with different times.**

            No Parallel Spread:
            Rotting spreads in parallel, not in a chain.
            DFS processes one rotten orange completely before moving to others, which breaks parallelism.
        */
    }
};
