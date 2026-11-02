class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        vector<int> s1Freq(26, 0);
        vector<int> s2Freq(26, 0);
        if (s1.length() > s2.length()) return false;

        for(int i = 0; i < s1.size(); i++) {
            s1Freq[s1[i] - 'a']++;
            s2Freq[s2[i] - 'a']++;
        }
        if(s1Freq == s2Freq) return true;
        for (int i = s1.length(); i < s2.length(); i++) {
            s2Freq[s2[i - s1.length()] - 'a']--;
            s2Freq[s2[i] - 'a']++;
            if (s1Freq == s2Freq) return true;
        }
        return false;
    }
};
