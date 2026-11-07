class Solution {
public:
    int characterReplacement(string s, int k) {
        int n = s.size(), best = 0;
        for (int i = 0; i < n; i++) {
            int freq[26] = {0}, maxCount = 0;
            for (int j = i; j < n; j++) {               // every window starting at i
                maxCount = max(maxCount, ++freq[s[j] - 'A']);
                if ((j - i + 1) - maxCount <= k) best = max(best, j - i + 1);
            }
        }
        return best;
    }
};
