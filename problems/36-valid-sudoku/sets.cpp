class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        unordered_set<char> rows[9], cols[9];
        unordered_set<char> boxes[9];

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                char digit = board[i][j];
                if (digit == '.') {
                    continue;
                }
                int box = (i / 3) * 3 + (j / 3); // box index

                if (rows[i].count(digit) || cols[j].count(digit) || boxes[box].count(digit)) {
                    return false;
                }
                rows[i].insert(digit);
                cols[j].insert(digit);
                boxes[box].insert(digit);
            }
        }
        return true;
    }
};
