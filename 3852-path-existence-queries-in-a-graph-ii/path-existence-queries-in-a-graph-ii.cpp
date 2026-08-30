class Solution {
public:
    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff,
                                     vector<vector<int>>& queries) {
        vector<pair<int, int>> a(n);

        for (int i = 0; i < n; i++)
            a[i] = {nums[i], i};

        sort(a.begin(), a.end());

        // pos[node] = position of node in sorted order
        vector<int> pos(n);
        vector<int> val(n);

        for (int i = 0; i < n; i++) {
            val[i] = a[i].first;
            pos[a[i].second] = i;
        }

        // Every consecutive pair with difference <= maxDiff is connected.
        // Therefore each connected component is a continuous segment.
        vector<int> component(n, 0);

        for (int i = 1; i < n; i++) {
            component[i] = component[i - 1];

            if (val[i] - val[i - 1] > maxDiff)
                component[i]++;
        }

        // up[k][i] = position reached after 2^k jumps
        // We jump to the farthest position reachable in one edge.
        const int LOG = 18; // 2^17 > 1e5

        vector<vector<int>> up(LOG, vector<int>(n));

        int r = 0;

        for (int i = 0; i < n; i++) {
            r = max(r, i);

            while (r + 1 < n && val[r + 1] - val[i] <= maxDiff)
                r++;

            up[0][i] = r;
        }

        for (int k = 1; k < LOG; k++) {
            for (int i = 0; i < n; i++) {
                up[k][i] = up[k - 1][up[k - 1][i]];
            }
        }

        vector<int> ans;

        for (auto &q : queries) {
            int u = pos[q[0]];
            int v = pos[q[1]];

            if (u == v) {
                ans.push_back(0);
                continue;
            }

            if (component[u] != component[v]) {
                ans.push_back(-1);
                continue;
            }

            if (u > v)
                swap(u, v);

            // Find minimum number of jumps needed to reach v.
            int cur = u;
            int steps = 0;

            for (int k = LOG - 1; k >= 0; k--) {
                if (up[k][cur] < v) {
                    cur = up[k][cur];
                    steps += (1 << k);
                }
            }

            // One final edge from cur to v.
            ans.push_back(steps + 1);
        }

        return ans;
    }
};