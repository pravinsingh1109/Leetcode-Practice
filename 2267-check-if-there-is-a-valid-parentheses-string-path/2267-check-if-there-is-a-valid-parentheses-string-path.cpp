#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    bool hasValidPath(vector<vector<char>>& grid)
    {
        int m = grid.size();
        int n = grid[0].size();
        
        // A valid parentheses string must have even length.
        if ((m + n - 1) % 2 != 0)
            return false;
        
        // dp[i][j][bal] = true if we can reach (i,j)
        // with current balance = bal.
        vector<vector<vector<bool>>> dp(
            m,
            vector<vector<bool>>(n, vector<bool>(m + n, false))
        );
        
        int start = (grid[0][0] == '(') ? 1 : -1;
        
        if (start < 0)
            return false;
        
        dp[0][0][start] = true;
        
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (i == 0 && j == 0)
                    continue;
                
                for (int bal = 0; bal <= m + n; bal++)
                {
                    bool possible = false;
                    
                    // From top
                    if (i > 0 && dp[i - 1][j][bal])
                        possible = true;
                    
                    // From left
                    if (j > 0 && dp[i][j - 1][bal])
                        possible = true;
                    
                    if (!possible)
                        continue;
                    
                    int newBal = bal;
                    
                    if (grid[i][j] == '(')
                        newBal++;
                    else
                        newBal--;
                    
                    if (newBal >= 0 && newBal <= m + n)
                        dp[i][j][newBal] = true;
                }
            }
        }
        
        return dp[m - 1][n - 1][0];
    }
};