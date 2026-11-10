// Binary search (patience sorting) - O(n log n) time, O(n) space
class Solution {
public:
    int binarySearch(vector<int>& vec, int target) {
        int s = 0;
        int e = vec.size() - 1;

        while (s <= e) {
            int mid = s + (e - s) / 2;
            if (vec[mid] >= target) {
                e = mid - 1;
            } else {
                s = mid + 1;
            }
        }
        return s;
    }

    int solveUsingBs(vector<int>& num) {
        vector<int> ans;
        // initial state
        ans.push_back(num[0]);
        for (int i = 1; i < num.size(); i++) {
            if (num[i] > ans.back()) {
                ans.push_back(num[i]);
            } else {
                // if a just greater number exists
                int index = binarySearch(ans, num[i]);
                // replace
                ans[index] = num[i];
            }
        }
        return ans.size();
    }

    int lengthOfLIS(vector<int>& nums) {
        int curr = 0;
        int prev = -1;
        // int n = nums.size();
        //  vector<vector<int> > dp(n+1, vector<int>(n+1,-1));
        int ans = solveUsingBs(nums);
        return ans;
    }
};
