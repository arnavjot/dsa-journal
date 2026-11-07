class Solution {
public:
    void inorder(TreeNode* root, vector<int>& vals) {
        if (!root) return;
        inorder(root->left, vals);
        vals.push_back(root->val);       // in-order of a BST = sorted
        inorder(root->right, vals);
    }
    int kthSmallest(TreeNode* root, int k) {
        vector<int> vals;
        inorder(root, vals);
        return vals[k - 1];
    }
};
