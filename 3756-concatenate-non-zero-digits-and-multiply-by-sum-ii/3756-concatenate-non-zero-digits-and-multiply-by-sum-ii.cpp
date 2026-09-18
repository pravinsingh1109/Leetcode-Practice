class Solution {
public:
    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        const long long MOD = 1000000007;

        int n = s.size();

        vector<long long> num(n + 1, 0);
        vector<long long> sum(n + 1, 0);
        vector<int> cnt(n + 1, 0);
        vector<long long> power10(n + 1, 1);

        for (int i = 1; i <= n; i++) {
            power10[i] = (power10[i - 1] * 10) % MOD;
        }

        for (int i = 0; i < n; i++) {
            num[i + 1] = num[i];
            sum[i + 1] = sum[i];
            cnt[i + 1] = cnt[i];

            if (s[i] != '0') {
                int digit = s[i] - '0';

                num[i + 1] = (num[i] * 10 + digit) % MOD;
                sum[i + 1] = (sum[i + 1] + digit) % MOD;
                cnt[i + 1]++;
            }
        }

        vector<int> answer;

        for (auto &q : queries) {
            int l = q[0];
            int r = q[1];

            int k = cnt[r + 1] - cnt[l];

            long long x =
                (num[r + 1] -
                (num[l] * power10[k]) % MOD + MOD) % MOD;

            long long digitSum =
                (sum[r + 1] - sum[l] + MOD) % MOD;

            long long result = (x * digitSum) % MOD;

            answer.push_back((int)result);
        }

        return answer;
    }
};