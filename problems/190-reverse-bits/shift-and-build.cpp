// Take bits off the right of n, push them onto the right of ans - O(32) time, O(1) space
class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t ans = 0;
        for (int k = 0; k < 32; k++) {
            ans = (ans << 1) | (n & 1);   // make room, then copy n's lowest bit
            n >>= 1;
        }
        return ans;
    }
};
