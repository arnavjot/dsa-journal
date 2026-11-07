class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        vector<int> freq(26, 0);
        for (char t : tasks) freq[t - 'A']++;
        int maxFreq = *max_element(freq.begin(), freq.end());
        int countMax = count(freq.begin(), freq.end(), maxFreq);   // tasks tied for most frequent
        int frame = (maxFreq - 1) * (n + 1) + countMax;              // full rows of n + 1 slots, plus the last row
        return max((int)tasks.size(), frame);                       // more tasks than slots → no idles needed
    }
};
