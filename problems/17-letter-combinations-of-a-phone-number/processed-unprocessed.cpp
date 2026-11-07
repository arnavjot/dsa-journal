class Solution {
public:
    vector<string> generateCombinations(string p, string up) {
        if (up.empty()) {
            return {p};
        }
        vector<string> mapping = { "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };
        
        int digit = up[0] - '0';
        vector<string> list;
        for (char ch : mapping[digit]) {
            vector<string> sublist = generateCombinations(p + ch, up.substr(1));
            list.insert(list.end(), sublist.begin(), sublist.end());
        }
        return list;
    }
    
    vector<string> letterCombinations(string digits) {
        if (digits.empty()) return {};
        return generateCombinations("", digits);
    }
};
