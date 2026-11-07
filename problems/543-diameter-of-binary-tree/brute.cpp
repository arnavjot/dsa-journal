class Solution {
public:
    int height(TreeNode* root) {
        if (root == NULL) return 0;
        return 1 + max(height(root->left), height(root->right));
    }
    int diameterOfBinaryTree(TreeNode* root) {
        if (root == NULL) return 0;
        int through = height(root->left) + height(root->right);   // recomputes heights at every node
        return max({through, diameterOfBinaryTree(root->left), diameterOfBinaryTree(root->right)});
    }
};
