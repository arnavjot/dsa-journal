class Solution {
public:
    int lastStoneWeight(vector<int>& stones) {
        while (stones.size() > 1) {
            sort(stones.begin(), stones.end());        // two heaviest at the end: O(n log n) each round
            int first = stones.back(); stones.pop_back();
            int second = stones.back(); stones.pop_back();
            if (first != second) stones.push_back(first - second);
        }
        return stones.empty() ? 0 : stones[0];
    }
};
