class Solution {
public:
    int sortableIntegers(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;

        for (int k = 1; k <= n; ++k) {
            if (n % k != 0) continue;

            bool valid = true;
            int prevMax = -1;

            for (int start = 0; start < n; start += k) {
                int mn = nums[start];
                int mx = nums[start];
                int descents = 0;

                for (int j = start; j < start + k; ++j) {
                    mn = min(mn, nums[j]);
                    mx = max(mx, nums[j]);

                    int next = (j + 1 == start + k)
                                   ? nums[start]
                                   : nums[j + 1];

                    if (nums[j] > next) {
                        ++descents;
                    }
                }

                if (descents > 1 || (start > 0 && prevMax > mn)) {
                    valid = false;
                    break;
                }

                prevMax = mx;
            }

            if (valid) {
                ans += k;
            }
        }

        return ans;
    }
};