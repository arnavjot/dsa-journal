class Solution {
public:
    int search(vector<int>& nums, int target) {
        for (int i = 0; i < nums.size(); i++) {   // ignores that the array is sorted
            if (nums[i] == target) {
                return i;
            }
        }
        return -1;
    }
};
