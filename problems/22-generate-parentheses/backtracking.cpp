class Solution {
public:
    void backtrack(int n, int open, int close, string curr, vector<string>& ans) {

        if (curr.length() == 2 * n) {
            ans.push_back(curr);
            return;
        }

        if (open < n) {
            backtrack(n, open + 1, close, curr + '(', ans);
        }

        if (close < open) {
            backtrack(n, open, close + 1, curr + ')', ans);
        }
    }

    vector<string> generateParenthesis(int n) {
        vector<string> ans;
        backtrack(n, 0, 0, "", ans);
        return ans;
    }
};
