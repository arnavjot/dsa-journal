// Binary exponentiation (fast power) - O(log n) time, O(1) space
class Solution {
public:
    double myPow(double x, int n) {
        long long N = n;          // -INT_MIN overflows int, so use long long
        if (N < 0) {
            x = 1 / x;
            N = -N;
        }
        double ans = 1;
        while (N > 0) {
            if (N & 1) {
                ans *= x;         // this bit of N is set: use the current power
            }
            x *= x;               // x, x^2, x^4, x^8, ...
            N >>= 1;
        }
        return ans;
    }
};
