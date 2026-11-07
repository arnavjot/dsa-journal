class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        queue<pair<TreeNode*, TreeNode*>> qu;    // compare matching positions level by level
        qu.push({p, q});
        while (!qu.empty()) {
            auto [a, b] = qu.front(); qu.pop();
            if (a == NULL && b == NULL) continue;
            if (a == NULL || b == NULL || a->val != b->val) return false;
            qu.push({a->left, b->left});
            qu.push({a->right, b->right});
        }
        return true;
    }
};
