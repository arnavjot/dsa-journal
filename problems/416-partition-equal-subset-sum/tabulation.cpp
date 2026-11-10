// Tabulation - O(n * target) time, O(n * target) space
class Solution {
public:
    bool solveUsingTabulation(vector<int> &arr, int target){
        int n = arr.size();
        vector<vector<int> > dp(n+2, vector<int>(target+1, 0));
        //base case analysis
        for(int row = 0; row <= n; row++){
            dp[row][target] = 1;
        }
        for(int index = n-1; index >= 0; index--){
            for(int sum = target; sum >= 0; sum--){
                bool include = 0;
                if(sum + arr[index] <= target)
                    include = dp[index+1][sum + arr[index]];

                bool exclude = dp[index+1][sum];
                dp[index][sum] = (include || exclude);
            }
        }
        return dp[0][0];
    }

    bool canPartition(vector<int>& nums) {
        int totalSum = 0;
        for(int i = 0; i<nums.size(); i++){
            totalSum += nums[i];
        }
        if(totalSum & 1){
            //odd
            return false;
        }
        int target = totalSum / 2;
        return solveUsingTabulation(nums, target);
    }
};
