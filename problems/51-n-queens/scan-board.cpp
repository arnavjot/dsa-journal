class Solution {
public:
    bool isSafe(vector<vector<bool>>& board, int row, int col) {
        for (int i = 0; i < row; i++) {
            if (board[i][col]) {
                return false;
            }
        }

        int maxLeft = min(row, col);
        for (int i = 1; i <= maxLeft; i++) {
            if (board[row - i][col - i]) {
                return false;
            }
        }
        int column = board.size() - col - 1;
        int maxRight = min(row, column);
        for (int i = 1; i <= maxRight; i++) {
            if (board[row - i][col + i]) {
                return false;
            }
        }

        return true;
    }
    vector<vector<string>> answer(vector<vector<bool>>& board) {
        vector<string> ansRow;
        vector<vector<string>> ans;

        for (vector<bool> row : board) {
            string strAns;
            for (bool val : row) {
                if (val) {
                    strAns += "Q";
                } else {
                    strAns += ".";
                }
            }
            ansRow.push_back(strAns);
        }
        ans.push_back(ansRow);
        return ans;
    }
    vector<vector<string>> queens(vector<vector<bool>>& board, int row) {
        vector<vector<string>> ans;
        if (row == board.size()) {
            return answer(board);
        }

        for (int col = 0; col < board.size(); col++) {
            // place the queen if it is safe
            if (isSafe(board, row, col)) {
                board[row][col] = true;
                vector<vector<string>> recAns = queens(board, row + 1);
                ans.insert(ans.end(), recAns.begin(), recAns.end());
                // for (const auto& solution : recAns) {
                //     ans.push_back(solution);
                // } // alternate approach for above line
                board[row][col] = false;
            }
        }
        return ans;
    }
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<bool>> board(n, vector<bool>(n, false));
        return queens(board, 0);
    }
};
