// XOR everything: pairs cancel - O(n) time, O(1) space
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int ans = 0;
        for(int i = 0; i < nums.size(); i++){
            ans = ans ^ nums[i];
        }
        return ans;
    }
};
