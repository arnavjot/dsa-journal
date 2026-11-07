class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (root == NULL) return NULL;
        queue<TreeNode*> q;                 // visit level by level instead of recursing
        q.push(root);
        while (!q.empty()) {
            TreeNode* node = q.front(); q.pop();
            swap(node->left, node->right);  // same one job per node
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        return root;
    }
};
