// Greedy: the smallest card left must start a group - O(n log n) time, O(n) space
class Solution {
public:
    bool isNStraightHand(vector<int>& hand, int groupSize) {
        if (hand.size() % groupSize != 0) return false;
        map<int, int> count;                       // card → copies left, sorted
        for (int x : hand) count[x]++;

        while (!count.empty()) {
            int first = count.begin()->first;      // smallest card left
            for (int x = first; x < first + groupSize; x++) {
                auto it = count.find(x);
                if (it == count.end()) return false;   // a needed card is missing
                if (--it->second == 0) count.erase(it);
            }
        }
        return true;
    }
};
