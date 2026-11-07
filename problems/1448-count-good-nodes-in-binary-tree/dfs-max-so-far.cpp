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
    int goodNodes(TreeNode* root) {
        return dfs(root, INT_MIN);
    }

    int dfs(TreeNode* root, int maxValue) {
        if (root == NULL) return 0;
        int count = 0;
        if (root->val >= maxValue) {
            count++;
        }
        maxValue = max(maxValue, root->val);
        count += dfs(root->left, maxValue);
        count += dfs(root->right, maxValue);

        return count;
    }
};
