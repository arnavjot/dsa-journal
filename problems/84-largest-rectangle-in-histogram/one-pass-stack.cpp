class Solution {
public:
    int getMax(vector<int>& arr, stack<int>& stack, int maxArea, int i) {
        int area;
        int popped = stack.top();
        stack.pop();
        if (stack.empty()) {
            area = arr[popped] * i;
        } else {
            area = arr[popped] * (i - 1 - stack.top());
        }
        return max(maxArea, area);
    }
    int largestRectangleArea(vector<int>& heights) {
        stack<int> stack;
        int maxArea = 0;
        stack.push(0);
        for (int i = 1; i < heights.size(); i++) {
            while (!stack.empty() && heights[i] < heights[stack.top()]) {
                maxArea = getMax(heights, stack, maxArea, i);
            }
            stack.push(i);
        }
        int i = heights.size();
        while (!stack.empty()) {
            maxArea = getMax(heights, stack, maxArea, i);
        }
        return maxArea;
    }
};
