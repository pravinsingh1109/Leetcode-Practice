class Solution {
public:
    long long countCommas(int n) {
        long long ans = 0;

        // Every number >= 1000 has at least one comma.
        if (n >= 1000)
            ans += n - 999;

        // Every number >= 1,000,000 would have a second comma.
        if (n >= 1000000)
            ans += n - 999999;

        return ans;
    }
};