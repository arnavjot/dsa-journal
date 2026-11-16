// Greedy: extend the part to the last occurrence of every letter in it - O(n) time, O(1) space
class Solution {
public:
    vector<int> partitionLabels(string s) {
        int last[26];
        for (int i = 0; i < s.size(); i++) {
            last[s[i] - 'a'] = i;                  // last index of each letter
        }
        vector<int> ans;
        int start = 0, end = 0;
        for (int i = 0; i < s.size(); i++) {
            end = max(end, last[s[i] - 'a']);      // this part must reach at least here
            if (i == end) {                        // every letter seen so far ends by i
                ans.push_back(end - start + 1);
                start = i + 1;
            }
        }
        return ans;
    }
};
