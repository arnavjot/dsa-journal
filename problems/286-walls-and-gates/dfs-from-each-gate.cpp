class Solution {
public:
    // DFS works only if a room is revisited whenever a shorter distance reaches it.
    void dfs(vector<vector<int>>& rooms, int r, int c, int d) {
        if (r < 0 || c < 0 || r >= rooms.size() || c >= rooms[0].size()) return;
        if (rooms[r][c] < d) return;            // wall (-1), or already reached at least as close
        rooms[r][c] = d;
        dfs(rooms, r + 1, c, d + 1);
        dfs(rooms, r - 1, c, d + 1);
        dfs(rooms, r, c + 1, d + 1);
        dfs(rooms, r, c - 1, d + 1);
    }

    void wallsAndGates(vector<vector<int>>& rooms) {
        for (int r = 0; r < rooms.size(); r++)
            for (int c = 0; c < rooms[0].size(); c++)
                if (rooms[r][c] == 0) dfs(rooms, r, c, 0);   // one DFS per gate
    }
};
