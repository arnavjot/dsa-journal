class WordDictionary {
    vector<string> words;
public:
    WordDictionary() {}

    void addWord(string word) { words.push_back(word); }

    bool search(string word) {
        for (string& w : words) {                 // compare against every stored word
            if (w.size() != word.size()) continue;
            bool ok = true;
            for (int i = 0; i < w.size() && ok; i++)
                if (word[i] != '.' && word[i] != w[i]) ok = false;
            if (ok) return true;
        }
        return false;
    }
};
