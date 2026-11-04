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
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (head == NULL || k == 1) {
            return head;
        }
        ListNode* dummyNode = new ListNode(0);
        dummyNode->next = head;
        ListNode* bef = dummyNode;
        ListNode* kthNode = bef;
        while (true) {//kthNode != NULL
            kthNode = bef;
            for (int i = 0; i < k && kthNode != NULL; i++) {
                // if (kthNode == NULL) {
                //     break;
                // }
                kthNode = kthNode->next;
            }
            if (kthNode == NULL) {
                break;
            }
            ListNode* start = bef->next;
            ListNode* curr = start->next;
            for (int i = 1; i < k; i++) {
                start->next = curr->next;
                curr->next = bef->next;
                bef->next = curr;
                curr = start->next;
            }
            bef = start;
        }
        return dummyNode->next;
    }
};
