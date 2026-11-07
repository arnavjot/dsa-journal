class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        vector<ListNode*> all;                       // every node from every list
        for (ListNode* l : lists)
            for (ListNode* t = l; t != NULL; t = t->next) all.push_back(t);
        sort(all.begin(), all.end(), [](ListNode* a, ListNode* b) { return a->val < b->val; });
        for (int i = 0; i + 1 < (int)all.size(); i++) all[i]->next = all[i + 1];
        if (all.empty()) return NULL;
        all.back()->next = NULL;
        return all[0];
    }
};
