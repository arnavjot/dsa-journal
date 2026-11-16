// Sort intervals and queries, min-heap of (size, right) - O((n + q) log n + q log q) time, O(n + q) space
class Solution {
public:
    vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries) {
        sort(intervals.begin(), intervals.end());                 // by left end
        vector<int> order(queries.size());
        for (int k = 0; k < queries.size(); k++) order[k] = k;
        sort(order.begin(), order.end(), [&](int a, int b) { return queries[a] < queries[b]; });

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> heap;  // (size, right)
        vector<int> ans(queries.size(), -1);
        int i = 0;
        for (int k : order) {
            int q = queries[k];
            while (i < intervals.size() && intervals[i][0] <= q) {   // starts at or before q
                heap.push({intervals[i][1] - intervals[i][0] + 1, intervals[i][1]});
                i++;
            }
            while (!heap.empty() && heap.top().second < q) {        // ended before q: useless from now on
                heap.pop();
            }
            if (!heap.empty()) ans[k] = heap.top().first;
        }
        return ans;
    }
};
