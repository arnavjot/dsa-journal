// Pop the last digit, push it onto sum, check overflow first - O(log x) time, O(1) space
class Solution {
public:
    int reverse(int x) {
        int sum = 0;
        while (x != 0) {
            if (abs(sum) > INT_MAX / 10) { // done to ensure that multiplying sum by 10 won't cause the value to exceed INT_MAX.
                return 0;
            }
            sum = sum * 10 + x % 10;
            x = x / 10;
        }
        return sum;
    }
};
