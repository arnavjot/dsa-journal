class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        int n = candidates.size();
        set<vector<int>> unique;                              // removes repeated combinations
        for (long long mask = 0; mask < (1LL << n); mask++) { // every subset: 2^n
            vector<int> pick; int sum = 0;
            for (int i = 0; i < n; i++)
                if (mask >> i & 1) { pick.push_back(candidates[i]); sum += candidates[i]; }
            if (sum == target) unique.insert(pick);
        }
        return vector<vector<int>>(unique.begin(), unique.end());
    }
};
