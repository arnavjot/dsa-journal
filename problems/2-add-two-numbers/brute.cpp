// Turn each list into a number, add, turn the sum back into a list.
// Looks fine, but FAILS on LeetCode: lists can have 100 digits, and
// unsigned long long only holds about 20 digits, so it overflows.
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        unsigned long long a = 0, b = 0, place = 1;
        for (ListNode* p = l1; p != NULL; p = p->next) { a += p->val * place; place *= 10; }
        place = 1;
        for (ListNode* p = l2; p != NULL; p = p->next) { b += p->val * place; place *= 10; }

        unsigned long long s = a + b;
        ListNode* dummy = new ListNode(0);
        ListNode* temp = dummy;
        do {                                  // do-while so 0 + 0 still makes one node
            temp->next = new ListNode(s % 10);
            temp = temp->next;
            s /= 10;
        } while (s > 0);
        return dummy->next;
    }
};
