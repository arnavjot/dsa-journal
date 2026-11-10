// Expand around center - O(n^2) time, O(1) extra space
class Solution {
public:
    int expand(string s, int i, int j){
        int count=0;
        while(i>=0 && i<s.length() && s[i] == s[j]){
            count++;
            i--;
            j++;
        }
        return count;
    }
    int countSubstrings(string s) {
        int number = 0;
        for(int center = 0; center < s.length(); center++){
            int odd = expand(s,center,center);
            int even = expand(s,center,center + 1);
            number += odd + even;
        }
        return number;
    }
};
