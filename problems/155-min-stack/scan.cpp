class MinStack {
public:
    vector<int> st;

    MinStack() {}

    void push(int val) { st.push_back(val); }
    void pop() { st.pop_back(); }
    int top() { return st.back(); }

    int getMin() {                     // scans the whole stack every time: O(n)
        int m = st[0];
        for (int x : st) m = min(m, x);
        return m;
    }
};
