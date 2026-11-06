class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        priority_queue<pair<int, int>> pq;          // max-heap of {distance², index}: farthest on top
        for (int i = 0; i < points.size(); i++) {
            int d = points[i][0] * points[i][0] + points[i][1] * points[i][1];
            pq.push({d, i});
            if (pq.size() > k) pq.pop();            // drop the farthest: it can't be in the k closest
        }
        vector<vector<int>> ans;
        while (!pq.empty()) {
            ans.push_back(points[pq.top().second]);
            pq.pop();
        }
        return ans;
    }
};
