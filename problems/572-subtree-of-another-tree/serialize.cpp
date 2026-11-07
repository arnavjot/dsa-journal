class Solution {
public:
    // Preorder with markers: "^" before every value and "#" for NULL, so "2" can't match inside "12".
    void ser(TreeNode* node, string& s) {
        if (node == nullptr) { s += ",#"; return; }
        s += ",^" + to_string(node->val);
        ser(node->left, s);
        ser(node->right, s);
    }
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        string a, b;
        ser(root, a);
        ser(subRoot, b);
        return a.find(b) != string::npos;   // KMP would make this O(m + n) guaranteed
    }
};
