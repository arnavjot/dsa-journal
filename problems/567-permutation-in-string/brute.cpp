class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        int m = s1.size(), n = s2.size();
        sort(s1.begin(), s1.end());
        for (int i = 0; i + m <= n; i++) {                 // every window of length m
            string w = s2.substr(i, m);
            sort(w.begin(), w.end());                       // anagram check by sorting
            if (w == s1) return true;
        }
        return false;
    }
};
