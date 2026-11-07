class KthLargest {
    int k;
    vector<int> all;                                   // every number, kept sorted
public:
    KthLargest(int k, vector<int>& nums) : k(k), all(nums) {
        sort(all.begin(), all.end());
    }

    int add(int val) {
        all.insert(upper_bound(all.begin(), all.end(), val), val);   // O(n) shift
        return all[all.size() - k];                    // k-th from the end
    }
};
