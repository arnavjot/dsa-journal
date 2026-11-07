class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& words) {
        unordered_set<string> st(words.begin(), words.end());
        if (st.find(endWord) == st.end())
            return 0;
        unordered_set<string> visited;
        queue<string> q;
        q.push(beginWord);
        visited.insert(beginWord);
        int res = 1;

        while (!q.empty()) {
            int size = q.size();

            while (size) {
                string str = q.front();
                q.pop();
                if (str == endWord)
                    return res;
                for (int i = 0; i < str.length(); i++) {
                    char original = str[i];
                    for (char c = 'a'; c <= 'z'; c++) {
                        // if(c == original) continue;
                        str[i] = c;
                        if (st.find(str) != st.end() &&
                            visited.find(str) == visited.end()) {
                            q.push(str);
                            visited.insert(str);
                        }
                    }
                    str[i] = original;
                }
                size--;
            }
            res++;
        }
        return 0;
    }
};
