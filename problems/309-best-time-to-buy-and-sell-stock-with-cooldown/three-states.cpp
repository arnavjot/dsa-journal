// State machine: best profit while holding, just after selling, and resting - O(n) time, O(1) space
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int hold = INT_MIN / 2;   // own a share (impossible before any day, so very low)
        int sold = 0;             // sold today: must rest tomorrow
        int rest = 0;             // own nothing and free to buy
        for (int p : prices) {
            int prevSold = sold;
            sold = hold + p;                  // sell the share held until today
            hold = max(hold, rest - p);       // keep holding, or buy today (only from rest: cooldown)
            rest = max(rest, prevSold);       // do nothing; yesterday's sale finishes its cooldown
        }
        return max(sold, rest);
    }
};
