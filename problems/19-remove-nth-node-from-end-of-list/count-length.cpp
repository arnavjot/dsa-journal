class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        int len = 0;
        for (ListNode* t = head; t != NULL; t = t->next) len++;   // pass 1: length

        if (n == len) {                      // the node to remove is the head
            ListNode* del = head;
            head = head->next;
            delete del;
            return head;
        }

        ListNode* prev = head;               // pass 2: stop just before it
        for (int i = 1; i < len - n; i++) prev = prev->next;
        ListNode* del = prev->next;
        prev->next = del->next;
        delete del;
        return head;
    }
};
