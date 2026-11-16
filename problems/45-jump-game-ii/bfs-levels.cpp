// Greedy BFS by levels: each jump covers a window of indexes - O(n) time, O(1) space
class Solution {
public:
    int jump(vector<int>& nums) {
        int jumps = 0, curEnd = 0, farthest = 0;
        for (int i = 0; i < (int)nums.size() - 1; i++) {
            farthest = max(farthest, i + nums[i]);   // best reach from this window
            if (i == curEnd) {                       // window used up: take a jump
                jumps++;
                curEnd = farthest;
            }
        }
        return jumps;
    }
};
