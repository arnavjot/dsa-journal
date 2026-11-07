class Solution {
public:
    int height(TreeNode* root) {
        if (root == NULL) return 0;
        return 1 + max(height(root->left), height(root->right));
    }
    bool isBalanced(TreeNode* root) {
        if (root == NULL) return true;
        if (abs(height(root->left) - height(root->right)) > 1) return false;   // heights recomputed at every node
        return isBalanced(root->left) && isBalanced(root->right);
    }
};
