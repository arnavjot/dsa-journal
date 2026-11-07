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
    TreeNode* solve(unordered_map<int, int>& valueToIndexMap, vector<int>& preorder, vector<int>& inorder, int& preIndex, int inorderStart, int inorderEnd) {
        if (preIndex >= preorder.size() || inorderStart > inorderEnd) {
            return nullptr;
        }

        int element = preorder[preIndex];
        preIndex++;
        TreeNode* root = new TreeNode(element);
        int position = valueToIndexMap[element];

        root->left = solve(valueToIndexMap, preorder, inorder, preIndex, inorderStart, position - 1);
        root->right = solve(valueToIndexMap, preorder, inorder, preIndex, position + 1, inorderEnd);

        return root;
    }

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        unordered_map<int, int> valueToIndexMap;
        for (int i = 0; i < inorder.size(); i++) {
            valueToIndexMap[inorder[i]] = i;
        }
        int preIndex = 0;
        return solve(valueToIndexMap, preorder, inorder, preIndex, 0, inorder.size() - 1);
    }
};
