class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int ans = 0;
        for (int i = 0; i < prices.size(); i++) {
            for (int j = i; j < prices.size(); j++) {
                ans = max(ans, prices[j] - prices[i]);
            }
        }
        return ans;
    }
};
