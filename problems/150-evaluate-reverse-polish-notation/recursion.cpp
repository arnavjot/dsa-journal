class Solution {
public:
    // Read from the END: the last token is the final operator (or a lone number).
    // Its right operand is the expression just before it, then its left operand before that.
    int i;
    int eval(vector<string>& t) {
        string tok = t[i--];
        if (tok != "+" && tok != "-" && tok != "*" && tok != "/") return stoi(tok);
        int b = eval(t);              // right side is built first when reading backwards
        int a = eval(t);
        if (tok == "+") return a + b;
        if (tok == "-") return a - b;
        if (tok == "*") return a * b;
        return a / b;
    }
    int evalRPN(vector<string>& tokens) {
        i = tokens.size() - 1;
        return eval(tokens);
    }
};
