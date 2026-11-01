class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size(), best = 0;
        for (int i = 0; i < n; i++) {
            int minH = INT_MAX;
            for (int j = i; j < n; j++) {        // every range [i, j]: height is its shortest bar
                minH = min(minH, heights[j]);
                best = max(best, minH * (j - i + 1));
            }
        }
        return best;
    }
};
