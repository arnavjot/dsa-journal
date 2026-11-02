/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    //MY SOLUTION - BETTER
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        // ListNode* head = new ListNode();
        ListNode* head;
        if (list1 == NULL) {
            return list2;
        }
        if (list2 == NULL) {
            return list1;
        }
        if (list1->val <= list2->val) {
            head = list1;
            list1 = list1->next;
        } else {
            head = list2;
            list2 = list2->next;
        }

        ListNode* temp = head;
        while (list1 != NULL && list2 != NULL) {
            if (list1->val <= list2->val) {
                //ListNode* node = new ListNode(list1->val);
                temp->next = list1;
                list1 = list1->next;
                temp = temp->next;
            } else {
                //ListNode* node = new ListNode(list2->val);
                temp->next = list2;
                list2 = list2->next;
                temp = temp->next;
            }
        }
        // while (list1 != NULL) {
        //     ListNode* node = new ListNode(list1->val);
        //     temp->next = node;
        //     list1 = list1->next;
        //     temp = temp->next;
        // }
        // while (list2 != NULL) {
        //     ListNode* node = new ListNode(list2->val);
        //     temp->next = node;
        //     list2 = list2->next;
        //     temp = temp->next;
        // }
        if(list1 != NULL)
            temp->next = list1;
        else
            temp->next = list2;
        return head;
    }
};
