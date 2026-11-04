/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:
    void serializeHelper(TreeNode* root, string& serializedData) {
        if (root == nullptr) {
            serializedData += "#,";
            return;
        }

        serializedData += to_string(root->val) + ",";
        serializeHelper(root->left, serializedData);
        serializeHelper(root->right, serializedData);
    }
    
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string serializedData = "";
        serializeHelper(root, serializedData);
        return serializedData;
    }

    TreeNode* deserializeHelper(queue<string>& q) {
        string currentValue = q.front();
        q.pop();

        if (currentValue == "#")
            return nullptr;

        TreeNode* root = new TreeNode(stoi(currentValue));

        root->left = deserializeHelper(q);
        root->right = deserializeHelper(q);

        return root;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        string currentValue = "";
        queue<string> q;

        for (char ch : data) {
            if (ch == ',') {
                q.push(currentValue);
                currentValue = "";
            } else {
                currentValue += ch;
            }
        }

        return deserializeHelper(q);
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));
