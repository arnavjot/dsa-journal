class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        unordered_map<int, int> seen;               // same as Two Sum I, ignores the sorting
        for (int i = 0; i < numbers.size(); i++) {
            int rem = target - numbers[i];
            if (seen.count(rem)) return {seen[rem] + 1, i + 1};
            seen[numbers[i]] = i;
        }
        return {};
    }
};
