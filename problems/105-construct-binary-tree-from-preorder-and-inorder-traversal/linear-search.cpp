class Solution {
public:
    TreeNode* build(vector<int>& pre, vector<int>& in, int& p, int lo, int hi) {
        if (lo > hi) return nullptr;
        TreeNode* root = new TreeNode(pre[p++]);
        int pos = lo;
        while (in[pos] != root->val) pos++;   // search the root in inorder: O(n) per node
        root->left = build(pre, in, p, lo, pos - 1);
        root->right = build(pre, in, p, pos + 1, hi);
        return root;
    }
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int p = 0;
        return build(preorder, inorder, p, 0, inorder.size() - 1);
    }
};
