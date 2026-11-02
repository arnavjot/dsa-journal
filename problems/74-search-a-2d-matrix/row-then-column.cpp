class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int n = matrix.size(), m = matrix[0].size();
        // 1) binary search the rows: last row whose first value <= target
        int lo = 0, hi = n - 1, r = -1;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (matrix[mid][0] <= target) { r = mid; lo = mid + 1; }
            else hi = mid - 1;
        }
        if (r == -1) return false;
        // 2) binary search inside that row
        lo = 0; hi = m - 1;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (matrix[r][mid] == target) return true;
            if (matrix[r][mid] < target) lo = mid + 1;
            else hi = mid - 1;
        }
        return false;
    }
};
