class Solution {
public:
    // brute force
    string minWindow(string s, string t) {
        int ansStart = -1;
        int minLen = INT_MAX;
        if (s.length() < t.length()) return "";
        unordered_map<char, int> freqT;
        for (int i = 0; i < t.length(); i++) {
            freqT[t[i]]++;
        }
        for (int i = 0; i < s.length(); i++) {
            unordered_map<char, int> freqS;
            int found = 0;
            for (int j = i; j < s.length(); j++) {
                freqS[s[j]]++;
                if (freqS[s[j]] <= freqT[s[j]]) {
                    found++;
                }
                if (found == t.length()) {
                    if (j - i + 1 < minLen) {
                        minLen = j - i + 1;
                        ansStart = i;
                    }
                    break;
                }
            }
        }
        if (ansStart == -1) {
            return "";
        } else {
            return s.substr(ansStart, minLen);
        }
    }
};
