class Solution {
public:
    bool linearSearch(vector<int>& nums, int target) {
        for (int num : nums) {
            if (num == target)
                return true;
        }
        return false;
    }

    int longestConsecutive(vector<int>& nums) {
        int longest = 0;

        for (int num : nums) {
            int x = num;
            int cnt = 1;
            while (linearSearch(nums, x + 1)) {
                x++;
                cnt++;
            }
            longest = max(longest, cnt);
        }
        return longest;
    }
};
