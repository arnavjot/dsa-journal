class WordDictionary {
public:
    struct Node {
        Node* links[26];
        bool flag;
        Node() {
            flag = false;
            for (int i = 0; i < 26; i++) {
                links[i] = NULL;
            }
        }
    };

    Node* root;

    WordDictionary() {
        root = new Node();
    }

    void addWord(string word) {
        Node* node = root;
        for (char ch : word) {
            int index = ch - 'a';
            if (node->links[index] == NULL) {
                node->links[index] = new Node();
            }
            node = node->links[index];
        }

        node->flag = true;
    }

    bool search(string word) {
        return dfs(0, root, word);
    }

    bool dfs(int index, Node* node, string& word) {
        if (index == word.size()) {
            return node->flag;
        }

        char ch = word[index];
        if (ch == '.') {
            for (int i = 0; i < 26; i++) {
                if (node->links[i] != NULL) {
                    if (dfs(index + 1, node->links[i], word)) {
                        return true;
                    }
                }
            }
            return false;
        }

        int pos = ch - 'a';
        if (node->links[pos] == NULL) {
            return false;
        }
        return dfs(index + 1, node->links[pos], word);
    }
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */
