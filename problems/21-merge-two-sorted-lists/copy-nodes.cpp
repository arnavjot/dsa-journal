class Solution {
public:
    //MY SOLUTION - INITIAL
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode* temp1 = list1;
        ListNode* temp2 = list2;
        ListNode* head = new ListNode();
        if (temp1 == NULL) {
            return list2;
        }
        if (temp2 == NULL) {
            return list1;
        }
        if (temp1->val <= temp2->val) {
            head->val = temp1->val;
            temp1 = temp1->next;
        } else {
            head->val = temp2->val;
            temp2 = temp2->next;
        }

        ListNode* temp3 = head;
        while (temp1 != NULL && temp2 != NULL) {
            if (temp1->val <= temp2->val) {
                ListNode* node = new ListNode(temp1->val);
                temp3->next = node;
                temp1 = temp1->next;
                temp3 = temp3->next;
            } else {
                ListNode* node = new ListNode(temp2->val);
                temp3->next = node;
                temp2 = temp2->next;
                temp3 = temp3->next;
            }
        }
        while (temp1 != NULL) {
            ListNode* node = new ListNode(temp1->val);
            temp3->next = node;
            temp1 = temp1->next;
            temp3 = temp3->next;
        }
        while (temp2 != NULL) {
            ListNode* node = new ListNode(temp2->val);
            temp3->next = node;
            temp2 = temp2->next;
            temp3 = temp3->next;
        }
        return head;
    }
};
