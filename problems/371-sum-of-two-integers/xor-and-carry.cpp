// XOR adds without carry, AND << 1 is the carry; repeat until no carry - O(32) time, O(1) space
class Solution {
public:
    int getSum(int a, int b) {
        while (b != 0) {
            unsigned int carry = (unsigned int)(a & b) << 1;   // unsigned: shifting a negative int is undefined in C++
            a = a ^ b;                                         // sum without the carries
            b = (int)carry;
        }
        return a;
    }
};
