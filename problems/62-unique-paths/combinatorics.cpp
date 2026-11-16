// Combinatorics: choose which m-1 of the m+n-2 steps go down - O(m) time, O(1) space
class Solution {
public:
    // Intuition: If we observe examples there is a similarity in paths from
    // start to end. Each time we are taking an exactly m+n-2 number of steps to
    // reach the end.

    // From start to reach the end we need a certain number of rightward directions and a certain number of
    // downward directions. So we can figure out we need n - 1 no.of rightward direction and m - 1 no.of
    // downward direction to reach the endpoint.
    // Since we need an m + n - 2 number of steps to reach the end among those steps if we choose n - 1
    // rightward direction or m - 1 downward direction and calculate the combinations
    // (ie : m + n - 2 C n - 1 or m + n - 2 C m - 1) we'll get the total number of paths.
    int uniquePaths(int m, int n) {
        int N = n + m - 2;
        int r = m - 1;
        double res = 1;

        for (int i = 1; i <= r; i++)
            res = res * (N - r + i) / i;
        return (int)res;
    }
};
