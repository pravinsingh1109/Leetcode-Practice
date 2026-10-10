class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {
        vector<int> diff;
        int n = nums1.size();
        long long total = 0;
        int mx = 0;

        for (int i = 0; i < n; i++) {
            int d = abs(nums1[i] - nums2[i]);
            diff.push_back(d);
            total += d;
            mx = max(mx, d);
        }

        long long k = (long long)k1 + k2;

        if (total <= k)
            return 0;

        int low = 0, high = mx;

        while (low < high) {
            int mid = low + (high - low) / 2;
            long long operations = 0;

            for (int d : diff) {
                if (d > mid)
                    operations += d - mid;
            }

            if (operations <= k)
                high = mid;
            else
                low = mid + 1;
        }

        int level = low;
        long long used = 0, ans = 0;

        for (int d : diff) {
            if (d > level)
                used += d - level;

            long long x = min(d, level);
            ans += x * x;
        }

        long long remaining = k - used;

        if (level > 0)
            ans -= remaining * (2LL * level - 1);

        return ans;
    }
};