class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == NULL) return NULL;
        if (root->val == p->val) return p;
        if (root->val == q->val) return q;

        TreeNode* leftAns = lowestCommonAncestor(root->left, p, q);
        TreeNode* rightAns = lowestCommonAncestor(root->right, p, q);
        
        if (!leftAns && !rightAns) return NULL;
        else if (leftAns && !rightAns) return leftAns;
        else if (!leftAns && rightAns) return rightAns;
        else return root;
    }
};
