class Solution {
public:
    bool hasCycle(ListNode* head) {
        unordered_set<ListNode*> seen;
        for (ListNode* cur = head; cur != NULL; cur = cur->next) {
            if (seen.count(cur)) return true;   // came back to a node already visited
            seen.insert(cur);
        }
        return false;
    }
};
