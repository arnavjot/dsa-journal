class Solution {
public:
    // From each cell, follow water downhill (to equal or lower) and see which oceans it reaches.
    void flow(vector<vector<int>>& h, int r, int c, vector<vector<bool>>& seen, bool& pac, bool& atl) {
        int m = h.size(), n = h[0].size();
        if (r == 0 || c == 0) pac = true;
        if (r == m - 1 || c == n - 1) atl = true;
        seen[r][c] = true;
        int d[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        for (auto& e : d) {
            int a = r + e[0], b = c + e[1];
            if (a >= 0 && b >= 0 && a < m && b < n && !seen[a][b] && h[a][b] <= h[r][c])
                flow(h, a, b, seen, pac, atl);
        }
    }

    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        int m = heights.size(), n = heights[0].size();
        vector<vector<int>> result;
        for (int r = 0; r < m; r++)
            for (int c = 0; c < n; c++) {
                vector<vector<bool>> seen(m, vector<bool>(n, false));   // fresh search per cell: O(m·n) each
                bool pac = false, atl = false;
                flow(heights, r, c, seen, pac, atl);
                if (pac && atl) result.push_back({r, c});
            }
        return result;
    }
};
