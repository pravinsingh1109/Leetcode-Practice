class Solution {
public:
    int maxPalindromes(string s, int k) {
        int n = s.size();
        
        // dp[i][j] = whether s[i..j] is a palindrome
        vector<vector<bool>> dp(n, vector<bool>(n, false));

        // Build palindrome table
        for (int len = 1; len <= n; len++) {
            for (int i = 0; i + len - 1 < n; i++) {
                int j = i + len - 1;

                if (len == 1)
                    dp[i][j] = true;
                else if (len == 2)
                    dp[i][j] = (s[i] == s[j]);
                else
                    dp[i][j] = (s[i] == s[j] && dp[i + 1][j - 1]);
            }
        }

        // best[i] = maximum number of valid non-overlapping
        // palindromes using s[0..i-1]
        vector<int> best(n + 1, 0);

        for (int i = 1; i <= n; i++) {
            // Don't take a palindrome ending at i-1
            best[i] = best[i - 1];

            // Try every palindrome of length >= k ending at i-1
            for (int start = 0; start <= i - k; start++) {
                if (dp[start][i - 1]) {
                    best[i] = max(best[i],
                                  best[start] + 1);
                }
            }
        }

        return best[n];
    }
};