class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        vector<string> ans;

        int l = 0, r = 0;

        // Count minimum invalid '(' and ')'
        for (char ch : s) {
            if (ch == '(') {
                l++;
            } 
            else if (ch == ')') {
                if (l > 0)
                    l--;
                else
                    r++;
            }
        }

        unordered_set<string> st;

        function<void(int, int, int, string, int)> solve =
            [&](int i, int left, int right, string curr, int balance) {

            if (i == s.size()) {
                if (left == 0 && right == 0 && balance == 0) {
                    st.insert(curr);
                }
                return;
            }

            char ch = s[i];

            if (ch == '(') {

                // Remove '('
                if (left > 0) {
                    solve(i + 1, left - 1, right, curr, balance);
                }

                // Keep '('
                solve(i + 1, left, right, curr + ch, balance + 1);

            } 
            else if (ch == ')') {

                // Remove ')'
                if (right > 0) {
                    solve(i + 1, left, right - 1, curr, balance);
                }

                // Keep ')' only when balance > 0
                if (balance > 0) {
                    solve(i + 1, left, right, curr + ch, balance - 1);
                }

            } 
            else {
                // Letter
                solve(i + 1, left, right, curr + ch, balance);
            }
        };

        solve(0, l, r, "", 0);

        for (auto &x : st)
            ans.push_back(x);

        return ans;
    }
};