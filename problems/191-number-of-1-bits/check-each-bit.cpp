// Check the last bit, shift right, 32 times - O(32) time, O(1) space
class Solution {
public:
    int hammingWeight(int n) {
        unsigned int x = n;
        int count = 0;
        for (int k = 0; k < 32; k++) {
            count += x & 1;    // is the lowest bit 1?
            x >>= 1;
        }
        return count;
    }
};
