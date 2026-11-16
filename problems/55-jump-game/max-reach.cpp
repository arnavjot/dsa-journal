// Greedy: track the farthest index reachable so far - O(n) time, O(1) space
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int maxReach = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (i > maxReach) {
                return false;              // stuck: nothing so far can reach i
            }
            maxReach = max(maxReach, i + nums[i]);
        }
        return true;
    }
};
