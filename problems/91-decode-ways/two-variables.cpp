// DP from the end with two variables - O(n) time, O(1) space
class Solution {
public:
    int numDecodings(string s) {
        int n = s.size();
        int next = 1, next2 = 0;   // ways to decode s[i+1..] and s[i+2..]; the empty rest has 1 way
        for (int i = n - 1; i >= 0; i--) {
            int cur = 0;
            if (s[i] != '0') {
                cur = next;                                    // take s[i] as one letter
                if (i + 1 < n && (s[i] == '1' || (s[i] == '2' && s[i + 1] <= '6'))) {
                    cur += next2;                              // take s[i..i+1] as 10..26
                }
            }
            next2 = next;
            next = cur;
        }
        return next;
    }
};
