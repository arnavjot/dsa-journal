class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int left = 0;
        int maxi = 0;
        unordered_set<char> window;

        for (int right = 0; right < s.length(); right++) {
            while (window.count(s[right])) {
                window.erase(s[left]);
                left++;
            }
            window.insert(s[right]);
            maxi = max(maxi, right - left + 1);
        }
        return maxi;
    }
};
