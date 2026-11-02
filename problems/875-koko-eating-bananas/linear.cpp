class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int maxPile = *max_element(piles.begin(), piles.end());
        for (int k = 1; k <= maxPile; k++) {             // try every speed from slowest up
            long long hours = 0;
            for (int pile : piles) hours += (pile + k - 1) / k;
            if (hours <= h) return k;                     // first speed that fits
        }
        return maxPile;
    }
};
