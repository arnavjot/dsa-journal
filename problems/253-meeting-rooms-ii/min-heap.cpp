// Sort by start, min-heap of end times - O(n log n) time, O(n) space
class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end());
        priority_queue<int, vector<int>, greater<int>> ends;   // end time of each busy room
        int rooms = 0;
        for (int i = 0; i < intervals.size(); i++) {
            if (!ends.empty() && ends.top() <= intervals[i][0]) {
                ends.pop();     // the earliest-ending room is free again: reuse it
            }
            ends.push(intervals[i][1]);
            rooms = max(rooms, (int)ends.size());
        }
        return rooms;
    }
};
