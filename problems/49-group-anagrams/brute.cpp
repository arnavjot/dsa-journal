class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>>ans;
        vector<bool> visited(strs.size(), false);

        for(int i = 0; i < strs.size(); i++) {
            if (visited[i]) continue;
            vector<string> group;
            group.push_back(strs[i]);
            visited[i] = true;

            for(int j = i + 1; j < strs.size(); j++) {
                if(!visited[j] && isAnagram(strs[i],strs[j])) {
                    group.push_back(strs[j]);
                    visited[j] = true;
                }
            }
            ans.push_back(group);
        }
        return ans;
    }

    bool isAnagram(string s, string t) {
        if (s.length() != t.length()) return false;

        vector<int> freq(26, 0);
        for (int i = 0; i < s.length(); i++) {
            freq[s[i] - 'a']++;
            freq[t[i] - 'a']--;
        }
        for(int i = 0; i < s.length(); i++) {
            if (freq[s[i] - 'a'] != 0) {
                return false;
            }
        }
        return true;
    }
};
