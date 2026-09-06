class Solution {
public:
    int numDistinct(string s, string t) {
        int m = t.size();
        
        vector<int> dp(m + 1, 0);
        dp[0] = 1;

        for (char c : s) {
            for (int j = m; j >= 1; --j) {
                if (c == t[j - 1]) {
                    // Prevent integer overflow
                    if (dp[j - 1] > INT_MAX - dp[j]) {
                        dp[j] = INT_MAX;
                    } else {
                        dp[j] += dp[j - 1];
                    }
                }
            }
        }

        return dp[m];
    }
};