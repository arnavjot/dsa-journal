// Expand around center - O(n^2) time, O(1) extra space
class Solution {
public:
    string expand(string s , int i , int j){
        string str="";
        while(i>=0 && j<=s.length() && s[i]==s[j]){
            i--;
            j++;
        }
        str = s.substr(i+1,j-i-1);
        return str;
    }
    string longestPalindrome(string s) {
        string maxi = "";
        for(int center = 0; center < s.length(); center++){
            string odd = expand(s,center,center);
            string even = expand(s,center,center + 1);

            if(odd.length() > maxi.length()){
                maxi = odd;
            }
            if(even.length() > maxi.length()){
                maxi = even;
            }
        }

        return maxi;
    }
};
