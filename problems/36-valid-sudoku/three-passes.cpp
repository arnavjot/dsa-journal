class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        // Check rows, then columns, then boxes, each with a fresh 9-slot seen array.
        for (int i = 0; i < 9; i++) {
            int row[9] = {}, col[9] = {}, box[9] = {};          // how many times each digit was seen
            for (int j = 0; j < 9; j++) {
                char a = board[i][j], b = board[j][i];
                char c = board[3 * (i / 3) + j / 3][3 * (i % 3) + j % 3];   // j-th cell of box i
                if (a != '.' && row[a - '1']++) return false;
                if (b != '.' && col[b - '1']++) return false;
                if (c != '.' && box[c - '1']++) return false;
            }
        }
        return true;
    }
};
