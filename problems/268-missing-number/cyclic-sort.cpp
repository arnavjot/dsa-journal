// Cyclic sort: put every value at its own index - O(n) time, O(1) space (changes the input)
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        // cyclic sort - O(n)
        int i = 0;
        while (i < nums.size()) {
            int correct = nums[i];
            // skip the element nums[i] which is equal to size cause we cant
            // place it at its correct index
            if (nums[i] < nums.size() && nums[i] != nums[correct]) {
                swap(nums[i], nums[correct]);
            } else {
                i++;
            }
        }
        i = 0;
        while (i < nums.size()) {
            if (nums[i] != i) {
                return i;
            } else {
                i++;
            }
        }
        return nums.size();
    }
};
