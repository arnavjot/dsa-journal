class Solution {
public:
    int characterReplacement(string s, int k) {
        unordered_map<char, int> freq;
        int i = 0, maxCount = 0, maxLen = 0;

        for(int j = 0; j < s.size(); j++) {
            freq[s[j]]++;
            maxCount = max(maxCount, freq[s[j]]);
            
            while((j - i + 1) - maxCount > k) {
                freq[s[i]]--;
                i++;
            }
            maxLen  = max(maxLen, j - i + 1);
        }
        return maxLen;
    }
};
