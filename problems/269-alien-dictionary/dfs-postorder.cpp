class Solution {
public:
    // state: 0 = not visited, 1 = on the current path, 2 = finished
    bool dfs(int u, vector<vector<bool>>& edge, vector<int>& state, string& out) {
        state[u] = 1;
        for (int v = 0; v < 26; v++) {
            if (edge[u][v]) {
                if (state[v] == 1) {
                    return false;                  // back onto the path: a cycle
                }
                if (state[v] == 0 && !dfs(v, edge, state, out)) {
                    return false;
                }
            }
        }
        state[u] = 2;
        out += char('a' + u);                      // added after every letter that must follow it
        return true;
    }

    string alienOrder(vector<string>& words) {
        vector<vector<bool>> edge(26, vector<bool>(26, false));
        vector<bool> present(26, false);
        for (string& w : words) {
            for (char c : w) {
                present[c - 'a'] = true;
            }
        }

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
                    return "";
                }
                continue;
            }
            edge[a[j] - 'a'][b[j] - 'a'] = true;
        }

        vector<int> state(26, 0);
        string out;
        for (int c = 0; c < 26; c++) {
            if (present[c] && state[c] == 0) {
                if (!dfs(c, edge, state, out)) {
                    return "";
                }
            }
        }
        reverse(out.begin(), out.end());
        return out;
    }
};
