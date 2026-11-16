// Greedy: track the lowest and highest possible number of open '(' - O(n) time, O(1) space
class Solution {
public:
    bool checkValidString(string s) {
        int lo = 0, hi = 0;
        for (char c : s) {
            if (c == '(') {
                lo++; hi++;
            } else if (c == ')') {
                lo--; hi--;
            } else {                     // '*' can be ')', '' or '('
                lo--; hi++;
            }
            if (hi < 0) return false;    // too many ')' even if every '*' is '('
            lo = max(lo, 0);             // can't have negative open brackets
        }
        return lo == 0;                  // some choice closes everything
    }
};
