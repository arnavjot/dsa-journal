class Solution {
public:
    void sink(vector<vector<char>>& grid, int i, int j) {
        if (i < 0 || j < 0 || i >= grid.size() || j >= grid[0].size() || grid[i][j] != '1') return;
        grid[i][j] = '0';                  // mark visited by turning land into water
        sink(grid, i - 1, j);
        sink(grid, i, j + 1);
        sink(grid, i + 1, j);
        sink(grid, i, j - 1);
    }

    int numIslands(vector<vector<char>>& grid) {
        int count = 0;
        for (int i = 0; i < grid.size(); i++)
            for (int j = 0; j < grid[0].size(); j++)
                if (grid[i][j] == '1') {   // new island: count it, then sink all of it
                    count++;
                    sink(grid, i, j);
                }
        return count;
    }
};
