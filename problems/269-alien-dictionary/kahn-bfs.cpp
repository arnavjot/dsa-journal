class Solution {
public:
    string alienOrder(vector<string>& words) {
        vector<vector<bool>> edge(26, vector<bool>(26, false));
        vector<int> indegree(26, -1);              // -1: letter not in any word
        for (string& w : words) {
            for (char c : w) {
                indegree[c - 'a'] = 0;
            }
        }

        // each neighbouring pair of words gives at most one rule: the first letters that differ
        for (int i = 0; i + 1 < words.size(); i++) {
            string& a = words[i];
            string& b = words[i + 1];
            int len = min(a.size(), b.size());
            int j = 0;
            while (j < len && a[j] == b[j]) {
                j++;
            }
            if (j == len) {
                if (a.size() > b.size()) {
                    return "";                     // "abc" before "ab" can never be sorted
                }
                continue;
            }
            int u = a[j] - 'a', v = b[j] - 'a';
            if (!edge[u][v]) {
                edge[u][v] = true;                 // u comes before v
                indegree[v]++;
            }
        }

        queue<int> q;
        for (int c = 0; c < 26; c++) {
            if (indegree[c] == 0) {
                q.push(c);
            }
        }

        string order;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            order += char('a' + u);
            for (int v = 0; v < 26; v++) {
                if (edge[u][v]) {
                    indegree[v]--;
                    if (indegree[v] == 0) {
                        q.push(v);
                    }
                }
            }
        }

        int letters = 0;
        for (int c = 0; c < 26; c++) {
            if (indegree[c] != -1) {
                letters++;
            }
        }
        if (order.size() != letters) {
            return "";                             // a cycle: those letters never reached indegree 0
        }
        return order;
    }
};
