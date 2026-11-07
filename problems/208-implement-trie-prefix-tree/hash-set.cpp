class Trie {
    unordered_set<string> words, prefixes;
public:
    Trie() {}

    void insert(string word) {
        words.insert(word);
        for (int len = 1; len <= word.size(); len++)
            prefixes.insert(word.substr(0, len));   // every prefix: O(L²) work per insert
    }

    bool search(string word) { return words.count(word); }

    bool startsWith(string prefix) { return prefixes.count(prefix); }
};
