// Tabulation, two rows - O(n * target) time, O(target) space
class Solution {
public:
    bool solveUsingTabulationSO(vector<int> &arr, int target){
        int n = arr.size();
        //vector<vector<int> > dp(n+2, vector<int>(target+1, 0));
        vector<int> curr(target + 1,0);
        vector<int> next(target + 1,0);
        //base case analysis
        curr[target] = 1;
        next[target] = 1;

        for(int index = n-1; index >= 0; index--){
            for(int sum = target; sum >= 0; sum--){
                bool include = 0;
                if(sum + arr[index] <= target)
                    include = next[sum + arr[index]];

                bool exclude = next[sum];
                curr[sum] = (include || exclude);
            }
            next = curr;
        }
        return next[0];
    }



    bool canPartition(vector<int>& nums) {
        int index = 0;
        int totalSum = 0;
        for(int i = 0; i<nums.size(); i++){
            totalSum += nums[i];
        }
            if(totalSum & 1){
                //odd
                return false;
            }
            int target = totalSum / 2;
            int currSum = 0;
            vector<vector<int> > dp(nums.size()+1, vector<int>(target+1, -1));
            bool ans = solveUsingTabulationSO(nums,target);
            return ans;
        }
};
