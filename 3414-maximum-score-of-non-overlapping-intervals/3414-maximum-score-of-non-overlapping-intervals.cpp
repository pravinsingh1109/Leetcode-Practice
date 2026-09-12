class Solution {
public:
    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();

        // {left, right, weight, original_index}
        vector<array<long long, 4>> a;

        for (int i = 0; i < n; i++) {
            a.push_back({
                intervals[i][0],
                intervals[i][1],
                intervals[i][2],
                i
            });
        }

        // Sort by starting point
        sort(a.begin(), a.end());

        // dp[i][k] = best result using intervals from i onward,
        // choosing at most k intervals.
        //
        // Store:
        // first  = maximum score
        // second = lexicographically smallest index list
        vector<vector<pair<long long, vector<int>>>> dp(
            n + 1,
            vector<pair<long long, vector<int>>>(5)
        );

        // dp[n][k] = score 0, empty vector
        for (int k = 0; k <= 4; k++) {
            dp[n][k] = {0, {}};
        }

        // Find first interval whose left > current right
        auto getNext = [&](long long right) {
            int lo = 0, hi = n;

            while (lo < hi) {
                int mid = lo + (hi - lo) / 2;

                if (a[mid][0] > right)
                    hi = mid;
                else
                    lo = mid + 1;
            }

            return lo;
        };

        for (int i = n - 1; i >= 0; i--) {

            for (int k = 1; k <= 4; k++) {

                // Option 1: Skip current interval
                long long skipScore = dp[i + 1][k].first;
                vector<int> skipVec = dp[i + 1][k].second;

                // Option 2: Take current interval
                int next = getNext(a[i][1]);

                long long takeScore =
                    a[i][2] + dp[next][k - 1].first;

                vector<int> takeVec = dp[next][k - 1].second;
                takeVec.push_back((int)a[i][3]);

                // Sort indices because answer must be lexicographically
                // compared in increasing order.
                sort(takeVec.begin(), takeVec.end());

                if (takeScore > skipScore) {
                    dp[i][k] = {takeScore, takeVec};
                }
                else if (takeScore < skipScore) {
                    dp[i][k] = {skipScore, skipVec};
                }
                else {
                    // Same score -> lexicographically smaller indices
                    if (takeVec < skipVec)
                        dp[i][k] = {takeScore, takeVec};
                    else
                        dp[i][k] = {skipScore, skipVec};
                }
            }

            // k = 0 -> cannot choose anything
            dp[i][0] = {0, {}};
        }

        return dp[0][4].second;
    }
};