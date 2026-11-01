class Solution {
public:
    void dfs(TreeNode* node, int depth, vector<vector<int>>& ans) {
        if (node == nullptr) return;
        if (depth == ans.size()) ans.push_back({});   // first node at this depth opens a new level
        ans[depth].push_back(node->val);              // left before right keeps each level in order
        dfs(node->left, depth + 1, ans);
        dfs(node->right, depth + 1, ans);
    }
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        dfs(root, 0, ans);
        return ans;
    }
};
