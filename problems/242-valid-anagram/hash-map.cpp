class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s.length() != t.length()) {
            return false;
        }
        unordered_map<char, int> count;   // works for any characters, not just a–z
        for (char c : s) count[c]++;
        for (char c : t) {
            if (--count[c] < 0) {         // t uses a letter more often than s
                return false;
            }
        }
        return true;                      // same length + never below 0 → all exactly 0
    }
};
