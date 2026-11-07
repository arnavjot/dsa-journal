class MedianFinder {
    vector<int> a;                                     // all numbers, kept sorted
public:
    MedianFinder() {}

    void addNum(int num) {
        a.insert(upper_bound(a.begin(), a.end(), num), num);   // O(n) shift
    }

    double findMedian() {
        int n = a.size();
        if (n % 2) return a[n / 2];
        return (a[n / 2 - 1] + (double)a[n / 2]) / 2.0;
    }
};
