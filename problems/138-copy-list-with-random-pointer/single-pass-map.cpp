/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Solution {
public:
    //single pass hashmap - more complex
    Node* copyRandomList(Node* head) {
        if (head == NULL)
            return head;

        unordered_map<Node*, Node*> nodes;
        nodes[head] = new Node(head->val);
        Node* temp = head;

        while (temp != NULL) {
            Node* nextNode = temp->next;
            Node* randomNode = temp->random;

            if (nextNode != NULL) {
                if (nodes.find(nextNode) == nodes.end()) {
                    nodes[nextNode] = new Node(nextNode->val);
                }
                nodes[temp]->next = nodes[nextNode];
            }

            if (randomNode != NULL) {
                if (nodes.find(randomNode) == nodes.end()) {
                    nodes[randomNode] = new Node(randomNode->val);
                }
                nodes[temp]->random = nodes[randomNode];
            }

            temp = temp->next;
        }

        return nodes[head];
    }
};
