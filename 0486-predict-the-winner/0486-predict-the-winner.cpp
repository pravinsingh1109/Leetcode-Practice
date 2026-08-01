class Solution {
public:
    int dp[21][21];

    int solve(vector<int>& nums, int i, int j) {
        if (i == j) return nums[i];
        if (dp[i][j] != INT_MIN) return dp[i][j];

        int takeLeft = nums[i] - solve(nums, i + 1, j);
        int takeRight = nums[j] - solve(nums, i, j - 1);

        return dp[i][j] = max(takeLeft, takeRight);
    }

    bool predictTheWinner(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i < 21; i++)
            for (int j = 0; j < 21; j++)
                dp[i][j] = INT_MIN;

        return solve(nums, 0, n - 1) >= 0;
    }
};