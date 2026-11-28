
class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n = items.size();
        vector<int> cnt(n + 1, 0);

        int minPrice = INT_MAX;

        for (auto &x : items) {
            cnt[x[0]]++;
            minPrice = min(minPrice, x[1]);
        }

        vector<int> gain(n + 1, 0);

        for (int i = 1; i <= n; i++) {
            for (int j = i; j <= n; j += i) {
                gain[i] += cnt[j];
            }
            gain[i]--;
        }

        vector<pair<int, int>> v;

        for (auto &x : items) {
            int f = x[0], p = x[1];

            if (gain[f] > 0 && p < 2 * minPrice) {
                v.push_back({p, gain[f]});
            }
        }

        sort(v.begin(), v.end());

        long long ans = 0;

        for (auto &[price, count] : v) {
            int take = min(count, budget / price);

            ans += 2LL * take;
            budget -= take * price;
        }

        ans += budget / minPrice;

        return ans;
    }
};
