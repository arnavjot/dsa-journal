class Solution {
public:

    string signature(string key) {
        vector<int> freq(26, 0);
        for(char ch : key) {
            freq[ch - 'a']++;
        }

        string signature = "";
        for(int i = 0; i < freq.size(); i++) {
            signature += to_string(freq[i]);
            signature += "#";
        }
        return signature;
    }
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>>ans;
        unordered_map<string, vector<string>> groups;

        for (int i = 0; i < strs.size(); i++) {
            string key = signature(strs[i]);
            groups[key].push_back(strs[i]);
        }
        for (const auto& group : groups) {
            ans.push_back(group.second);
        }
        return ans;
    }
};
