class Solution {
public:
    int maxLength(vector<int>& nums) {
        int n = nums.size(), ans = 0;

        for (int i = 0; i < n; i++) {
            long long product = 1, l = 1;
            int g = 0;

            for (int j = i; j < n; j++) {
                product *= nums[j];
                g = gcd(g, nums[j]);
                l = lcm(l, (long long)nums[j]);

                if (product == g * l)
                    ans = max(ans, j - i + 1);

                if (product > g * l)
                    break;
            }
        }

        return ans;
    }
};