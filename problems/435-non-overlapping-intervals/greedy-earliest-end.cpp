// Greedy: sort by end, keep the one that ends first - O(n log n) time, O(1) extra space
class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        if (intervals.empty()) return 0;

        // sort by end time
        sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
        });
        int count = 0;
        int prevEnd = intervals[0][1];
        for (int i = 1; i < intervals.size(); i++) {
            if (intervals[i][0] < prevEnd) {
                count++;
            } else {
                prevEnd = intervals[i][1];
            }
        }
        return count;
    }
};

// This is the classic activity selection problem greedy strategy.
// Sorting by start time doesn't guarantee minimal removals
// it may trap you with a huge interval like [1,100] and force you to discard many smaller ones.

// Time → 0-----------------------------------------------------------100

// [1,100]  ──────────────────────────────────────────────────────────
// [1,11]   ──────
// [2,12]     ───────
// [11,22]           ──────────

//If you take [1,100] first, you can't take any others.
// If you take [1,11], you can still take [11,22].
// That's why the greedy strategy prefers the earliest end.
