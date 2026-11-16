// Peel the outer layer by erasing it from the matrix - O(m*n*(m+n)) time, changes the input
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> res;
        while (!matrix.empty()) {
            // 1. Go right
            res.insert(res.end(), matrix[0].begin(), matrix[0].end());
            matrix.erase(matrix.begin());

            // 2. Go down
            for (int i = 0; i < matrix.size(); ++i) {
                if (!matrix[i].empty()) {
                    res.push_back(matrix[i].back());
                    matrix[i].pop_back();
                }
            }

            // 3. Go left
            if (!matrix.empty()) {
                vector<int>& lastRow = matrix.back();
                res.insert(res.end(), lastRow.rbegin(), lastRow.rend());
                matrix.pop_back();
            }

            // 4. Go up
            for (int i = matrix.size() - 1; i >= 0; --i) {
                if (!matrix[i].empty()) {
                    res.push_back(matrix[i].front());
                    matrix[i].erase(matrix[i].begin());
                }
            }
        }
        return res;
    }
};
