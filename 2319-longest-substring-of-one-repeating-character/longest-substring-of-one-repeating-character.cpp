class Solution {
public:
    struct Node {
        int pref, suff, best, len;
        char lc, rc;

        Node() : pref(0), suff(0), best(0), len(0), lc(0), rc(0) {}
        Node(char c) : pref(1), suff(1), best(1), len(1), lc(c), rc(c) {}
    };

    vector<Node> seg;
    string s;

    Node merge(Node a, Node b) {
        if (a.len == 0) return b;
        if (b.len == 0) return a;

        Node res;
        res.len = a.len + b.len;
        res.lc = a.lc;
        res.rc = b.rc;

        res.pref = a.pref;
        if (a.pref == a.len && a.rc == b.lc)
            res.pref = a.len + b.pref;

        res.suff = b.suff;
        if (b.suff == b.len && a.rc == b.lc)
            res.suff = b.len + a.suff;

        res.best = max(a.best, b.best);

        if (a.rc == b.lc)
            res.best = max(res.best, a.suff + b.pref);

        return res;
    }

    void build(int p, int l, int r) {
        if (l == r) {
            seg[p] = Node(s[l]);
            return;
        }

        int m = (l + r) / 2;
        build(p * 2, l, m);
        build(p * 2 + 1, m + 1, r);

        seg[p] = merge(seg[p * 2], seg[p * 2 + 1]);
    }

    void update(int p, int l, int r, int idx, char c) {
        if (l == r) {
            s[idx] = c;
            seg[p] = Node(c);
            return;
        }

        int m = (l + r) / 2;

        if (idx <= m)
            update(p * 2, l, m, idx, c);
        else
            update(p * 2 + 1, m + 1, r, idx, c);

        seg[p] = merge(seg[p * 2], seg[p * 2 + 1]);
    }

    vector<int> longestRepeating(string s,
                                 string queryCharacters,
                                 vector<int>& queryIndices) {
        this->s = s;
        int n = s.size();

        seg.resize(4 * n + 5);
        build(1, 0, n - 1);

        vector<int> ans;

        for (int i = 0; i < queryIndices.size(); i++) {
            update(1, 0, n - 1,
                   queryIndices[i],
                   queryCharacters[i]);

            ans.push_back(seg[1].best);
        }

        return ans;
    }
};