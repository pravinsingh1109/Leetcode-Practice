class Solution {
public:
    int uniquePaths(vector<vector<int>>& grid) {
        const int MOD = 1e9 + 7;

        int m = grid.size();
        int n = grid[0].size();

        vector<vector<int>> right(m, vector<int>(n, -1));
        vector<vector<int>> down(m, vector<int>(n, -1));

        // Precompute mirror transitions
        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {

                if (grid[i][j] == 1) {

                    // Enter mirror while moving Right
                    if (i + 1 < m) {
                        if (grid[i + 1][j] == 0)
                            right[i][j] = (i + 1) * n + j;
                        else
                            right[i][j] = down[i + 1][j];
                    }

                    // Enter mirror while moving Down
                    if (j + 1 < n) {
                        if (grid[i][j + 1] == 0)
                            down[i][j] = i * n + j + 1;
                        else
                            down[i][j] = right[i][j + 1];
                    }
                }
            }
        }

        vector<vector<int>> dp(m, vector<int>(n, 0));
        dp[0][0] = 1;

        // Count paths
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                if (grid[i][j] == 1 || dp[i][j] == 0)
                    continue;

                long long ways = dp[i][j];

                // Move Right
                if (j + 1 < n) {
                    int dest;

                    if (grid[i][j + 1] == 0)
                        dest = i * n + j + 1;
                    else
                        dest = right[i][j + 1];

                    if (dest != -1) {
                        int x = dest / n;
                        int y = dest % n;

                        dp[x][y] = (dp[x][y] + ways) % MOD;
                    }
                }

                // Move Down
                if (i + 1 < m) {
                    int dest;

                    if (grid[i + 1][j] == 0)
                        dest = (i + 1) * n + j;
                    else
                        dest = down[i + 1][j];

                    if (dest != -1) {
                        int x = dest / n;
                        int y = dest % n;

                        dp[x][y] = (dp[x][y] + ways) % MOD;
                    }
                }
            }
        }

        return dp[m - 1][n - 1];
    }
};