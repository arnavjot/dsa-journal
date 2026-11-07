class Solution {
public:
    ListNode* detectCycle(ListNode* head) {
        unordered_set<ListNode*> seen;
        ListNode* cur = head;
        while (cur != NULL) {
            if (seen.count(cur)) {
                return cur;          // first node we visit twice = cycle start
            }
            seen.insert(cur);
            cur = cur->next;
        }
        return NULL;
    }
};
