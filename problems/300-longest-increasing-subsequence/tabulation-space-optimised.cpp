// Tabulation, two rows - O(n^2) time, O(n) space
class Solution {
public:
    int solveUsingTabulationSO(vector<int>& nums) {
        int n = nums.size();
        vector<int> currrow(n + 1, 0);
        vector<int> nextrow(n + 1, 0);

        for (int curr_index = n - 1; curr_index >= 0; curr_index--) {
            for (int prev_index = curr_index - 1; prev_index >= -1;
                 prev_index--) {

                int include = 0;
                if (prev_index == -1 || nums[curr_index] > nums[prev_index]) {
                    include = 1 + nextrow[curr_index + 1];
                }
                int exclude = 0 + nextrow[prev_index + 1];
                currrow[prev_index + 1] = max(include, exclude);
            }
            nextrow = currrow;
        }
        return nextrow[0];
    }

    int lengthOfLIS(vector<int>& nums) {
        return solveUsingTabulationSO(nums);
    }
};
