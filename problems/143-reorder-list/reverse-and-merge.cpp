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
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* curr = head;

        while (curr != nullptr) {
            ListNode* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        return prev; 
    }
    ListNode* middleNode(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast != NULL && fast->next != NULL) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }
    void reorderList(ListNode* head) {
         if(head == NULL || head->next == NULL){
            return;
        }
        
        ListNode* mid = middleNode(head);
        ListNode* hs = reverseList(mid);
        ListNode* hf = head;

        while(hf != NULL && hs != NULL){
            ListNode* temp = hf->next;
            hf->next = hs;
            hf = temp;

            temp = hs->next;
            hs->next = hf;
            hs = temp;
        }
        
        //setting next of last node in list to null
        if(hf != NULL){
            hf->next = NULL;
        }
        
    }
};
