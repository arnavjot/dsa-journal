class Solution {
public:
    string minWindow(string s, string t) {
        int left = 0;
        string ans = "";
        int ansStart = -1;
        int minLen = INT_MAX;
        if (s.length() < t.length()) return "";
        unordered_map<char, int> freqS;
        unordered_map<char, int> freqT;
        for (int i = 0; i < t.length(); i++) {
            freqT[t[i]]++;
        }
        int found = 0;
        for (int right = 0; right < s.length(); right++) {
            freqS[s[right]]++;
            if (freqS[s[right]] <= freqT[s[right]]) {
                found++;
            }
            if (found == t.length()) {
                while (freqS[s[left]] > freqT[s[left]]) { // if unnecessary chars
                    freqS[s[left]]--;
                    left++;
                }
                if (right - left + 1 < minLen) {
                    minLen = right - left + 1;
                    ansStart = left;
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
