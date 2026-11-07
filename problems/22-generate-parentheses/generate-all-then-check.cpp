class Solution {
public:
    bool valid(string& s) {
        int bal = 0;
        for (char c : s) {
            bal += (c == '(') ? 1 : -1;
            if (bal < 0) return false;          // a ')' with nothing to close
        }
        return bal == 0;
    }
    void gen(int n, string& s, vector<string>& ans) {
        if (s.size() == 2 * n) {
            if (valid(s)) ans.push_back(s);     // check only at the end
            return;
        }
        s.push_back('('); gen(n, s, ans); s.pop_back();
        s.push_back(')'); gen(n, s, ans); s.pop_back();
    }
    vector<string> generateParenthesis(int n) {
        vector<string> ans;
        string s;
        gen(n, s, ans);                          // all 2^(2n) strings
        return ans;
    }
};
