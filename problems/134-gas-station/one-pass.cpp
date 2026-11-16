// Greedy one pass: restart after any station where the tank goes negative - O(n) time, O(1) space
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int total = 0, tank = 0, start = 0;
        for (int i = 0; i < gas.size(); i++) {
            total += gas[i] - cost[i];
            tank += gas[i] - cost[i];
            if (tank < 0) {          // can't get from start to i + 1: no station in start..i works
                start = i + 1;
                tank = 0;
            }
        }
        return total >= 0 ? start : -1;   // enough gas overall → start works
    }
};
