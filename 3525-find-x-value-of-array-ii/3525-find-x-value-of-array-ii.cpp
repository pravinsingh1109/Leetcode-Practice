class Solution {
public:
    struct Node {
        int prod;
        int cnt[5];

        Node(int p = 1) {
            prod = p;
            for (int i = 0; i < 5; i++)
                cnt[i] = 0;
        }
    };

    int k;
    int size;
    vector<Node> tree;

    Node mergeNode(const Node& a, const Node& b) {
        Node res;

        res.prod = (1LL * a.prod * b.prod) % k;

        // Prefixes completely inside left part
        for (int r = 0; r < k; r++) {
            res.cnt[r] = a.cnt[r];
        }

        // Prefixes which take all left + some prefix of right
        for (int r = 0; r < k; r++) {
            if (b.cnt[r] == 0)
                continue;

            int nr = (1LL * a.prod * r) % k;
            res.cnt[nr] += b.cnt[r];
        }

        return res;
    }

    Node makeLeaf(int value) {
        Node node(value % k);
        node.cnt[value % k] = 1;
        return node;
    }

    void update(int pos, int value) {
        pos += size;
        tree[pos] = makeLeaf(value);

        pos >>= 1;

        while (pos >= 1) {
            tree[pos] = mergeNode(tree[pos << 1], tree[pos << 1 | 1]);
            pos >>= 1;
        }
    }

    Node query(int l, int r) {
        Node leftRes(1 % k);
        Node rightRes(1 % k);

        l += size;
        r += size;

        while (l < r) {
            if (l & 1) {
                leftRes = mergeNode(leftRes, tree[l]);
                l++;
            }

            if (r & 1) {
                --r;
                rightRes = mergeNode(tree[r], rightRes);
            }

            l >>= 1;
            r >>= 1;
        }

        return mergeNode(leftRes, rightRes);
    }

    vector<int> resultArray(vector<int>& nums, int k,
                            vector<vector<int>>& queries) {
        this->k = k;

        int n = nums.size();

        size = 1;
        while (size < n)
            size <<= 1;

        tree.assign(2 * size, Node(1 % k));

        for (int i = 0; i < n; i++) {
            tree[size + i] = makeLeaf(nums[i]);
        }

        for (int i = size - 1; i >= 1; i--) {
            tree[i] = mergeNode(tree[i << 1], tree[i << 1 | 1]);
        }

        vector<int> ans;
        ans.reserve(queries.size());

        for (auto& q : queries) {
            int index = q[0];
            int value = q[1];
            int start = q[2];
            int x = q[3];

            update(index, value);

            Node res = query(start, n);

            ans.push_back(res.cnt[x]);
        }

        return ans;
    }
};