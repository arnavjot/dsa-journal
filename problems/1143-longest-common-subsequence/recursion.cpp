// Recursion - O(2^(n+m)) time, O(n+m) stack space
class Solution {
public:
    int solveRec(string text1, string text2, int i, int j) {
        if (i >= text1.length()) {
            return 0;
        }
        if (j >= text2.length()) {
            return 0;
        }
        int ans = 0;
        if (text1[i] == text2[j]) {
            ans += 1 + solveRec(text1, text2, i + 1, j + 1);
        } else {
            ans = 0 + max(solveRec(text1, text2, i, j + 1),
                          solveRec(text1, text2, i + 1, j));
        }
        return ans;
    }
    int longestCommonSubsequence(string text1, string text2) {
        int i = 0;
        int j = 0;
        int ans = solveRec(text1, text2, i, j);
        return ans;
    }
};
