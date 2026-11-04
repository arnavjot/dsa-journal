class Solution {
public:
    int getLength(ListNode* &head) {
        int len = 0;
        ListNode* temp = head;
        while (temp) {
            len++;
            temp = temp->next;
        }
        return len;
    }

    ListNode* reverseKGroup(ListNode* head, int k) {
        // ll is empty or single node
        if (head == NULL || head->next == NULL) {
            return head;
        }
        
        // ek case mai solve krungi baaki rec sambhalega
        // atleast 2 node and k > 1 nodes
        int len = getLength(head);
        if (len < k) {
            //  no need to reverse
            return head;
        }

        ListNode* prev = NULL;
        ListNode* curr = head;
        int position = 0;

        while (position < k) {
            ListNode* forward = curr->next;
            curr->next = prev;
            prev = curr;
            curr = forward;
            position++;
        }
        // rec sambhalega
        if (curr) {
            ListNode* recHead = reverseKGroup(curr, k);
            head->next = recHead;
        }
        return prev;
    }
};
