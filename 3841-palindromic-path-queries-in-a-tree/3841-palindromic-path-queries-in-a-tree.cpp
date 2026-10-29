class Solution {
public:
    vector<bool> palindromePath(int n, vector<vector<int>>& edges,
                                string s, vector<string>& queries) {
        vector<vector<int>> adj(n);

        for (auto &e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        vector<int> tin(n), tout(n), depth(n), parent(n, -1);
        vector<int> euler(n);
        int timer = 0;

        // Iterative DFS
        stack<tuple<int, int, bool>> st;
        st.push({0, -1, true});

        while (!st.empty()) {
            auto [u, p, enter] = st.top();
            st.pop();

            if (enter) {
                parent[u] = p;
                depth[u] = (p == -1 ? 0 : depth[p] + 1);
                tin[u] = timer;
                euler[timer++] = u;

                st.push({u, p, false});

                for (int i = (int)adj[u].size() - 1; i >= 0; i--) {
                    int v = adj[u][i];
                    if (v != p)
                        st.push({v, u, true});
                }
            } else {
                tout[u] = timer;
            }
        }

        int LOG = 17;
        vector<vector<int>> up(LOG, vector<int>(n));

        for (int i = 0; i < n; i++)
            up[0][i] = (parent[i] == -1 ? i : parent[i]);

        for (int k = 1; k < LOG; k++) {
            for (int i = 0; i < n; i++)
                up[k][i] = up[k - 1][up[k - 1][i]];
        }

        auto lca = [&](int u, int v) {
            if (depth[u] < depth[v])
                swap(u, v);

            int diff = depth[u] - depth[v];

            for (int k = 0; k < LOG; k++) {
                if (diff & (1 << k))
                    u = up[k][u];
            }

            if (u == v)
                return u;

            for (int k = LOG - 1; k >= 0; k--) {
                if (up[k][u] != up[k][v]) {
                    u = up[k][u];
                    v = up[k][v];
                }
            }

            return parent[u];
        };

        vector<int> bit(n + 1, 0);
        vector<int> nodeMask(n);

        auto updateBIT = [&](int idx, int val) {
            for (idx++; idx <= n; idx += idx & -idx)
                bit[idx] ^= val;
        };

        auto queryBIT = [&](int idx) {
            int res = 0;

            for (idx++; idx > 0; idx -= idx & -idx)
                res ^= bit[idx];

            return res;
        };

        for (int i = 0; i < n; i++) {
            int u = euler[i];
            nodeMask[u] = 1 << (s[u] - 'a');

            updateBIT(tin[u], nodeMask[u]);
            updateBIT(tout[u], nodeMask[u]);
        }

        vector<bool> ans;

        for (string &q : queries) {
            stringstream ss(q);
            string type;
            int u, v;

            ss >> type >> u;

            if (type == "update") {
                char c;
                ss >> c;

                int newMask = 1 << (c - 'a');
                int delta = nodeMask[u] ^ newMask;

                updateBIT(tin[u], delta);
                updateBIT(tout[u], delta);

                nodeMask[u] = newMask;
                s[u] = c;
            } else {
                ss >> v;

                int w = lca(u, v);

                // Correct path mask: no parent[w] XOR
                int pathMask = queryBIT(tin[u])
                             ^ queryBIT(tin[v])
                             ^ nodeMask[w];

                ans.push_back((pathMask & (pathMask - 1)) == 0);
            }
        }

        return ans;
    }
};