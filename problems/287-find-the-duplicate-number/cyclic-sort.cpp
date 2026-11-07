class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int i = 0;
        while (i < nums.size()) {
            int correct = nums[i] - 1;           // value v belongs at index v-1
            if (nums[i] != nums[correct]) {
                swap(nums[i], nums[correct]);    // send it home
            } else {
                i++;                             // already home, or its home is taken
            }
        }
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] - 1 != i) {
                return nums[i];                  // the value that had no free home
            }
        }
        return -1;
    }
};
