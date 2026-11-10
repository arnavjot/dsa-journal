// Memoization - O(n * target) time, O(n * target) space
class Solution {
public:
    bool solveUsingMem(vector<int>& arr, int index, int sum, int target, vector<vector<int> > &dp){
        if(index >= arr.size()){
            return 0;
        }
        if(sum > target ){
            return 0;
        }
        if(sum == target){
            return true;
        }
        if(dp[index][sum] != -1){
            return dp[index][sum];
        }
        bool include = solveUsingMem(arr, index+1, sum+arr[index], target,dp);
        bool exclude = solveUsingMem(arr, index+1, sum, target,dp);
        dp[index][sum] = (include || exclude);
        return dp[index][sum];

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
        vector<vector<int> > dp(nums.size()+1, vector<int>(target+1, -1));
        return solveUsingMem(nums, 0, 0, target, dp);
    }
};
