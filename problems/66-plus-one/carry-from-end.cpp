// Add 1 from the last digit, carrying past 9s - O(n) time, O(1) extra space
class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        for (int i = digits.size() - 1; i >= 0; i--) {
            if (digits[i] < 9) {
                digits[i]++;           // no carry: done
                return digits;
            }
            digits[i] = 0;             // 9 + 1 = 10: write 0, carry 1
        }
        digits.insert(digits.begin(), 1);   // every digit was 9: 999 → 1000
        return digits;
    }
};
