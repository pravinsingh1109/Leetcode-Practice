class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        const int MAXX = 2048;

        vector<vector<char>> dp(4, vector<char>(MAXX, 0));
        dp[0][0] = 1;

        for (int v : nums) {
            for (int cnt = 2; cnt >= 0; --cnt) {
                for (int x = 0; x < MAXX; ++x) {
                    if (dp[cnt][x])
                        dp[cnt + 1][x ^ v] = 1;
                }
            }
        }

        vector<char> seen(MAXX, 0);

        // Triplets with repeated indices always reduce to a single array value.
        for (int v : nums) seen[v] = 1;

        // Triplets with three distinct indices.
        for (int x = 0; x < MAXX; ++x)
            if (dp[3][x]) seen[x] = 1;

        int ans = 0;
        for (int x = 0; x < MAXX; ++x)
            ans += seen[x];

        return ans;
    }
};