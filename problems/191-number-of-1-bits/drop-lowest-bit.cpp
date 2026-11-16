// n & (n - 1) drops the lowest set bit - O(number of 1 bits) time, O(1) space
class Solution {
public:
    int hammingWeight(int n) {
        int count = 0;
        while (n != 0) {
            n = n & (n - 1);   // e.g. 1100 & 1011 = 1000
            count++;
        }
        return count;
    }
};
