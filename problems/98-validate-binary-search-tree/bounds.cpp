class Solution {
public:
    bool validate(TreeNode* root, long lowerBound, long upperBound) {
        if (!root) return true;
        if (root->val <= lowerBound || root->val >= upperBound) return false;

        return validate(root->left, lowerBound, root->val) && validate(root->right, root->val, upperBound);
    }

    bool isValidBST(TreeNode* root) {
        return validate(root, LONG_MIN, LONG_MAX);
    }
};
