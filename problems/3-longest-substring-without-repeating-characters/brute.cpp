class Solution {
public:
    // brute force 
    int lengthOfLongestSubstring(string s) {
        int n = s.length();
        int maxi = 0;
        for (int i = 0; i < n; i++) {
            unordered_set<char> seen;
            for (int j = i; j < n; j++) {
                if (seen.count(s[j])) break;   // repeat found, this start is done
                seen.insert(s[j]);
                maxi = max(maxi, j - i + 1);
            }
        }
        return maxi;
    }
};
