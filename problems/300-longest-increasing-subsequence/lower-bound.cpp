// Binary search with lower_bound - O(n log n) time, O(n) space
class Solution {
public:
    int solveUsingBs(vector<int>& num) {
        vector<int> ans;
        // initial state
        ans.push_back(num[0]);
        for (int i = 1; i < num.size(); i++) {
            if (num[i] > ans.back()) {
                ans.push_back(num[i]);
            } else {
                // if a just greater number exists
                int index = lower_bound(ans.begin(), ans.end(), num[i]) -
                ans.begin(); // gives answer of greater num
                // replace
                ans[index] = num[i];
            }
        }
        return ans.size();
    }

    int lengthOfLIS(vector<int>& nums) {
        return solveUsingBs(nums);
    }
};
