class Solution {
public:
    bool isPalindrome(string s) {
        int left = 0, right = s.length() - 1;
        while (left < right ) {
            while (left < right && !((tolower(s[left]) >= 'a' && tolower(s[left]) <= 'z') || (s[left] >= '0' && s[left] <= '9'))) left++; // or use isalnum
            while (left < right && !((tolower(s[right]) >= 'a' && tolower(s[right]) <= 'z')|| (s[right] >= '0' && s[right] <= '9'))) right--;
            if (tolower(s[left]) != tolower(s[right])) {
                return false;
            } 
            left++;
            right--;
        }
        return true;
    }
};
