class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (head == NULL)
            return NULL;

        unordered_map<Node*, Node*> nodes;
        Node* temp = head;

        while (temp != NULL) {
            nodes[temp] = new Node(temp->val);
            temp = temp->next;
        }

        temp = head;

        while (temp != NULL) {
            nodes[temp]->next = (temp->next == NULL) ? NULL : nodes[temp->next];

            nodes[temp]->random =
                (temp->random == NULL) ? NULL : nodes[temp->random];

            temp = temp->next;
        }

        return nodes[head];
    }
};
