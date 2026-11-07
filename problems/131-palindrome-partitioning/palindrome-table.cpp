class Solution {
public:
    void backtrack(string& s, int start, vector<vector<bool>>& pal, vector<string>& curr, vector<vector<string>>& ans) {
        if (start == s.length()) {
            ans.push_back(curr);
            return;
        }
        for (int i = start; i < s.length(); i++) {
            if (pal[start][i]) {                                   // O(1) lookup instead of a scan
                curr.push_back(s.substr(start, i - start + 1));
                backtrack(s, i + 1, pal, curr, ans);
                curr.pop_back();
            }
        }
    }

    vector<vector<string>> partition(string s) {
        int n = s.size();
        vector<vector<bool>> pal(n, vector<bool>(n, false));
        for (int i = n - 1; i >= 0; i--)
            for (int j = i; j < n; j++)
                pal[i][j] = s[i] == s[j] && (j - i < 2 || pal[i + 1][j - 1]);   // ends match + inside is a palindrome
        vector<vector<string>> ans;
        vector<string> curr;
        backtrack(s, 0, pal, curr, ans);
        return ans;
    }
};
