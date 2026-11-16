// Count points; for a query, try every stored point as the opposite corner - add O(1), count O(distinct points)
class DetectSquares {
public:
    vector<vector<int>> cnt;           // cnt[x][y] = how many copies of (x, y)
    vector<pair<int, int>> pts;        // each distinct point once

    DetectSquares() : cnt(1001, vector<int>(1001, 0)) {}

    void add(vector<int> point) {
        int x = point[0], y = point[1];
        if (cnt[x][y] == 0) pts.push_back({x, y});
        cnt[x][y]++;
    }

    int count(vector<int> point) {
        int x = point[0], y = point[1], ans = 0;
        for (auto [px, py] : pts) {
            // (px, py) must be the diagonal corner: same distance in x and y, not zero
            if (abs(px - x) != abs(py - y) || px == x) continue;
            ans += cnt[px][py] * cnt[x][py] * cnt[px][y];   // the other two corners
        }
        return ans;
    }
};
