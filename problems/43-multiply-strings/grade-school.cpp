// Grade-school multiplication: digit i times digit j lands at positions i + j and i + j + 1 - O(m*n) time, O(m+n) space
class Solution {
public:
    string multiply(string num1, string num2) {
        int m = num1.size(), n = num2.size();
        vector<int> pos(m + n, 0);
        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                int mul = (num1[i] - '0') * (num2[j] - '0');
                int sum = mul + pos[i + j + 1];
                pos[i + j + 1] = sum % 10;     // ones digit stays here
                pos[i + j] += sum / 10;        // carry moves one place left
            }
        }
        string ans;
        for (int d : pos) {
            if (!(ans.empty() && d == 0)) ans.push_back(d + '0');   // skip leading zeros
        }
        return ans.empty() ? "0" : ans;
    }
};
