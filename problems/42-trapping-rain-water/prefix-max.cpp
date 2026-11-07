class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        vector<int> leftMax(n), rightMax(n);         // tallest bar at or left of i / at or right of i
        for (int i = 0; i < n; i++) leftMax[i] = max(height[i], i ? leftMax[i - 1] : 0);
        for (int i = n - 1; i >= 0; i--) rightMax[i] = max(height[i], i < n - 1 ? rightMax[i + 1] : 0);
        int water = 0;
        for (int i = 0; i < n; i++) water += min(leftMax[i], rightMax[i]) - height[i];
        return water;
    }
};
