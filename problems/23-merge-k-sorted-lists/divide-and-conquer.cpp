class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode* dummy = new ListNode(0);
        ListNode* temp = dummy;
        while (list1 != NULL && list2 != NULL) {
            if (list1->val < list2->val) {
                temp->next = list1;
                list1 = list1->next;
                temp = temp->next;
            } else {
                temp->next = list2;
                list2 = list2->next;
                temp = temp->next;
            }
        }
        if (list1 != NULL)
            temp->next = list1;
        else
            temp->next = list2;
        return dummy->next;
    }
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty()) {
            return NULL;
        }

        while (lists.size() > 1) {
            vector<ListNode*> temp;
            for (int i = 0; i < lists.size(); i += 2) {
                ListNode* l1 = lists[i];
                ListNode* l2 = nullptr;
                if (i + 1 < lists.size()) {
                    l2 = lists[i + 1];
                }
                temp.push_back(mergeTwoLists(l1, l2));
            }
            lists = temp;
        }
        return lists[0];
    }
};
