/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    void solve (TreeNode* root, int level, vector<int>& rightView) {
        if(root == NULL) return;
        if(level == rightView.size()) {
            rightView.push_back(root->val);
        }
        solve(root->right, level + 1, rightView);
        solve(root->left, level + 1, rightView); // reverse these two for left view
    }
    vector<int> rightSideView(TreeNode* root) {
        vector<int> rightView;
        solve(root, 0, rightView);
        return rightView;
    }
};
