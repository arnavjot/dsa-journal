class Solution {
public:
    void reorderList(ListNode* head) {
        vector<ListNode*> nodes;
        for (ListNode* t = head; t != NULL; t = t->next) nodes.push_back(t);

        int i = 0, j = nodes.size() - 1;
        while (i < j) {
            nodes[i]->next = nodes[j];   // front → back
            i++;
            if (i == j) break;
            nodes[j]->next = nodes[i];   // back → next front
            j--;
        }
        if (!nodes.empty()) nodes[i]->next = NULL;   // the new tail
    }
};
