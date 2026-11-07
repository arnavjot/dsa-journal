class Solution {
public:
    bool isPalindrome(string s) {
        string clean;
        for (char c : s) {
            if (isalnum(c)) clean += tolower(c);    // keep letters + digits, lower-cased
        }
        string rev(clean.rbegin(), clean.rend());   // reversed copy
        return clean == rev;
    }
};
