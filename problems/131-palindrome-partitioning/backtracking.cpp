class Solution {
public:

    bool isPalindrome(string str) {
        int left = 0;
        int right = str.length() - 1;

        while (left < right) {
            if (str[left] != str[right]) {
                return false;
            }

            left++;
            right--;
        }

        return true;
    }

    void backtrack(string& s, int start, vector<string>& curr, vector<vector<string>>& ans) {

        if (start == s.length()) {
            ans.push_back(curr);
            return;
        }

        for (int i = start; i < s.length(); i++) {

            string sub = s.substr(start, i - start + 1);

            if (isPalindrome(sub)) {

                curr.push_back(sub);

                backtrack(s, i + 1, curr, ans);

                curr.pop_back();
            }
        }
    }

    vector<vector<string>> partition(string s) {

        vector<vector<string>> ans;
        vector<string> curr;

        backtrack(s, 0, curr, ans);

        return ans;
    }
};
