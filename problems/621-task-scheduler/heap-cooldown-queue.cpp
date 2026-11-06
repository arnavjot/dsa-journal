class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        vector<int> freq(26, 0);
        for (char task : tasks) {
            freq[task - 'A']++;
        }
        priority_queue<int> maxHeap;
        for (int count : freq) {
            if (count > 0) {
                maxHeap.push(count);
            }
        }
        queue<pair<int, int>> q;
        int time = 0;
        while (!maxHeap.empty() || !q.empty()) {
            time++;
            if (!q.empty() && q.front().second <= time) {
                maxHeap.push(q.front().first);
                q.pop();
            }
            if (!maxHeap.empty()) {
                int count = maxHeap.top();
                maxHeap.pop();
                count--;
                if (count > 0) {
                    q.push({count, time + n + 1});
                }
            }
        }
        return time;
    }
};
