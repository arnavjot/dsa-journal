// Recursion - O(2^n) time, O(n) stack space
class Solution {
public:
    bool solveUsingRecursion(vector<int>& arr, int index, int sum, int target){
        if(index >= arr.size()){
            return 0;
        }
        if(sum > target ){
            return 0;
        }
        if(sum == target){
            return true;
        }
        bool include = solveUsingRecursion(arr, index+1, sum + arr[index], target);
        bool exclude = solveUsingRecursion(arr, index+1, sum, target);

        return include || exclude;

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
        return solveUsingRecursion(nums, 0, 0, totalSum / 2);
    }
};
