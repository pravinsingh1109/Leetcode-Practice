#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    static const long long MOD = 1000000007;

    long long modPow(long long a, long long b) {
        long long res = 1;

        while (b > 0) {
            if (b & 1)
                res = res * a % MOD;

            a = a * a % MOD;
            b >>= 1;
        }

        return res;
    }

    int numberOfSets(int n, int k) {
        int N = n + k - 1;
        int R = 2 * k;

        // C(N, R)
        long long ans = 1;

        for (int i = 1; i <= R; i++) {
            ans = ans * (N - R + i) % MOD;
            ans = ans * modPow(i, MOD - 2) % MOD;
        }

        return ans;
    }
};