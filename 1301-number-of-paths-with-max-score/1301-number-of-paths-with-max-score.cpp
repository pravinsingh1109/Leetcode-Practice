class Solution {
public:
    vector<int> pathsWithMaxScore(vector<string>& board) {
        const int MOD = 1e9 + 7;
        int n = board.size();

        vector<vector<int>> score(n, vector<int>(n, -1));
        vector<vector<int>> ways(n, vector<int>(n, 0));

        score[n - 1][n - 1] = 0;
        ways[n - 1][n - 1] = 1;

        for (int i = n - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {

                if (board[i][j] == 'X')
                    continue;

                if (i == n - 1 && j == n - 1)
                    continue;

                int best = -1;

                if (i + 1 < n && score[i + 1][j] != -1)
                    best = max(best, score[i + 1][j]);

                if (j + 1 < n && score[i][j + 1] != -1)
                    best = max(best, score[i][j + 1]);

                if (i + 1 < n && j + 1 < n && score[i + 1][j + 1] != -1)
                    best = max(best, score[i + 1][j + 1]);

                if (best == -1)
                    continue;

                long long count = 0;

                if (i + 1 < n && score[i + 1][j] == best)
                    count = (count + ways[i + 1][j]) % MOD;

                if (j + 1 < n && score[i][j + 1] == best)
                    count = (count + ways[i][j + 1]) % MOD;

                if (i + 1 < n && j + 1 < n &&
                    score[i + 1][j + 1] == best)
                    count = (count + ways[i + 1][j + 1]) % MOD;

                score[i][j] = best;

                if (board[i][j] >= '1' && board[i][j] <= '9')
                    score[i][j] += board[i][j] - '0';

                ways[i][j] = count;
            }
        }

        // Check reachability using score, NOT ways.
        if (score[0][0] == -1)
            return {0, 0};

        return {score[0][0], ways[0][0]};
    }
};