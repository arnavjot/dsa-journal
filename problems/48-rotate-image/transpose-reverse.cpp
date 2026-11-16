// Transpose, then reverse every row - O(n^2) time, O(1) extra space
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        // *********TRANSPOSE*********
        int n = matrix.size();
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                swap(matrix[i][j], matrix[j][i]);
            }
        }
        // *********REVERSE EVERY ROW*********
        for (int i = 0; i < n; i++) {
            reverse(matrix[i].begin(), matrix[i].end());
        }
    }
};
