// Floyd's cycle check with a do-while loop - O(log n) time, O(1) space
class Solution {
private:
    int findSquare(int n) {
        int ans = 0;
        while (n != 0) { // n > 0
            int num = n % 10;
            ans += num * num;
            n = n / 10;
        }
        return ans;
    }

public:
    bool isHappy(int n) {
        int slow = n;
        int fast = n;
        do {
            slow = findSquare(slow);
            fast = findSquare(findSquare(fast));
            if (slow == 1) {
                return true;
            }
        } while (slow != fast);
        return false;
    }
};
