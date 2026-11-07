class Solution {
public:
    bool exist(vector<vector<char>>& b, string& w, int i, int r, int c) {
        if (i == w.size()) return true;
        if (r < 0 || c < 0 || r >= b.size() || c >= b[0].size() || b[r][c] != w[i]) return false;
        char ch = b[r][c];
        b[r][c] = '#';
        bool ok = exist(b, w, i + 1, r - 1, c) || exist(b, w, i + 1, r + 1, c) ||
                  exist(b, w, i + 1, r, c - 1) || exist(b, w, i + 1, r, c + 1);
        b[r][c] = ch;
        return ok;
    }

    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        vector<string> ans;
        for (string& w : words) {                       // LC 79 once per word
            bool found = false;
            for (int r = 0; r < board.size() && !found; r++)
                for (int c = 0; c < board[0].size() && !found; c++)
                    if (exist(board, w, 0, r, c)) found = true;
            if (found) ans.push_back(w);
        }
        return ans;
    }
};
