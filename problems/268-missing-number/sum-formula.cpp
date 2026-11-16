// Sum of 0..n minus the array sum - O(n) time, O(1) space
class Solution {
public:
    int missingNumber(vector<int> & nums) {
        int n = nums.size();
        int total = n * (n + 1) / 2; // sum of 0 to n
        int sum = 0;
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];
        }
        return total - sum;
    }
};
