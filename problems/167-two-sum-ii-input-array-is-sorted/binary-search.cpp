class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int n = numbers.size();
        for (int i = 0; i < n; i++) {
            int need = target - numbers[i];
            int s = i + 1, e = n - 1;               // partner must be to the right of i
            while (s <= e) {
                int mid = s + (e - s) / 2;
                if (numbers[mid] == need) return {i + 1, mid + 1};
                if (numbers[mid] < need) s = mid + 1;
                else e = mid - 1;
            }
        }
        return {};
    }
};
