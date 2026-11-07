class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        stack<TreeNode*> st;
        TreeNode* cur = root;
        while (cur != nullptr || !st.empty()) {
            while (cur != nullptr) {      // go as far left as possible
                st.push(cur);
                cur = cur->left;
            }
            cur = st.top(); st.pop();     // the next smallest value
            k--;
            if (k == 0) return cur->val;
            cur = cur->right;             // then visit its right subtree
        }
        return -1;
    }
};
