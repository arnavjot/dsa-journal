// Greedy: merge every triplet that doesn't overshoot the target - O(n) time, O(1) space
class Solution {
public:
    bool mergeTriplets(vector<vector<int>>& triplets, vector<int>& target) {
        bool found[3] = {false, false, false};
        for (auto& t : triplets) {
            if (t[0] > target[0] || t[1] > target[1] || t[2] > target[2]) {
                continue;                          // would push some value past the target
            }
            for (int k = 0; k < 3; k++) {
                if (t[k] == target[k]) found[k] = true;
            }
        }
        return found[0] && found[1] && found[2];
    }
};
