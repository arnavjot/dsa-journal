class Solution {
public:
    struct Node {
        Node* links[26];
        string word;

        Node() {
            word = "";

            for (int i = 0; i < 26; i++) {
                links[i] = NULL;
            }
        }
    };

    Node* root = new Node();

    void insert(string word) {
        Node* node = root;

        for (char ch : word) {
            int index = ch - 'a';

            if (node->links[index] == NULL) {
                node->links[index] = new Node();
            }

            node = node->links[index];
        }

        node->word = word;
    }

    void dfs(vector<vector<char>>& board, int r, int c,
             Node* node, vector<string>& ans) {

        char ch = board[r][c];
        int index = ch - 'a';

        if (node->links[index] == NULL) {
            return;
        }

        node = node->links[index];

        if (node->word != "") {
            ans.push_back(node->word);
            node->word = "";
        }

        board[r][c] = '#';

        int rows = board.size();
        int cols = board[0].size();

        if (r > 0 && board[r - 1][c] != '#') {
            dfs(board, r - 1, c, node, ans);
        }

        if (r < rows - 1 && board[r + 1][c] != '#') {
            dfs(board, r + 1, c, node, ans);
        }

        if (c > 0 && board[r][c - 1] != '#') {
            dfs(board, r, c - 1, node, ans);
        }

        if (c < cols - 1 && board[r][c + 1] != '#') {
            dfs(board, r, c + 1, node, ans);
        }

        board[r][c] = ch;
    }

    vector<string> findWords(vector<vector<char>>& board,
                             vector<string>& words) {

        for (string word : words) {
            insert(word);
        }

        vector<string> ans;

        int rows = board.size();
        int cols = board[0].size();

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                dfs(board, i, j, root, ans);
            }
        }

        return ans;
    }
};
