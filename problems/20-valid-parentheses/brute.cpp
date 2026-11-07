class Solution {
public:
    bool isValid(string s) {
        // Keep deleting adjacent "()", "[]", "{}" until nothing changes.
        // Valid strings shrink to empty. Each pass is O(n) and there can be n/2 passes.
        bool changed = true;
        while (changed) {
            changed = false;
            for (string pair : {"()", "[]", "{}"}) {
                size_t pos = s.find(pair);
                if (pos != string::npos) {
                    s.erase(pos, 2);
                    changed = true;
                }
            }
        }
        return s.empty();
    }
};
