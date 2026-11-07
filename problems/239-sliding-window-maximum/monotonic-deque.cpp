class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int> dq;                 // indices; their values are decreasing from front to back
        vector<int> ans;
        for (int i = 0; i < nums.size(); i++) {
            if (!dq.empty() && dq.front() == i - k) dq.pop_front();          // front fell out of the window
            while (!dq.empty() && nums[dq.back()] <= nums[i]) dq.pop_back(); // smaller ones can never be a max again
            dq.push_back(i);
            if (i >= k - 1) ans.push_back(nums[dq.front()]);                 // front = max of the window
        }
        return ans;
    }
};
