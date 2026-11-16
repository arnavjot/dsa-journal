// Recursion - O(3^(n+m)) time, O(n+m) stack space
class Solution {
public:
    int solveUsingRecursion(string& a, string& b, int i, int j) { // MEMORY LIMIT EXCEEDED pass by ref
        // base case
        if (i >= a.length()) {
            return b.length() - j;
        }
        if (j >= b.length()) {
            return a.length() - i;
        }

        int ans = 0;

        if (a[i] == b[j]) {
            // match
            ans = 0 + solveUsingRecursion(a, b, i + 1, j + 1);
        } else {
            // insert
            int insert = 1 + solveUsingRecursion(a, b, i, j + 1);
            // delete
            int remove = 1 + solveUsingRecursion(a, b, i + 1, j);
            // replace
            int replace = 1 + solveUsingRecursion(a, b, i + 1, j + 1);
            ans = min(insert, min(remove, replace));
        }
        return ans;
    }
    int minDistance(string word1, string word2) {
        int i = 0;
        int j = 0;
        int ans = solveUsingRecursion(word1, word2, i, j);
        return ans;
    }
};
