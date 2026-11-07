class MedianFinder {
private:
    priority_queue<int> maxi;
    priority_queue<int, vector<int>, greater<int>> mini;
    double median;

public:
    MedianFinder() : median(0) {}

    void addNum(int num) {
        if (maxi.size() == mini.size()) {
            if (num > median) {
                mini.push(num);
                median = mini.top();
            } else {
                maxi.push(num);
                median = maxi.top();
            }
        } else if (maxi.size() == mini.size() + 1) {
            if (num > median) {
                mini.push(num);
            } else {
                int maxTop = maxi.top();
                maxi.pop();
                mini.push(maxTop);
                maxi.push(num);
            }
            median = (mini.top() + maxi.top()) / 2.0;
        } else if (mini.size() == maxi.size() + 1) {
            if (num > median) {
                int minTop = mini.top();
                mini.pop();
                maxi.push(minTop);
                mini.push(num);
            } else {
                maxi.push(num);
            }
            median = (mini.top() + maxi.top()) / 2.0;
        }
    }

    double findMedian() {
        return median;
    }
};
