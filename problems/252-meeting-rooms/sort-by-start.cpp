// Sort by start, check neighbours - O(n log n) time, O(1) extra space
class Solution {
public:
    bool canAttendMeetings(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end());
        for (int i = 1; i < intervals.size(); i++) {
            if (intervals[i][0] < intervals[i - 1][1]) {
                return false;   // starts before the previous meeting ends
            }
        }
        return true;
    }
};
