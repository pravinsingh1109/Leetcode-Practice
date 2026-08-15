class Solution {
public:
    int longestSubsequence(vector<int>& nums) {
        int n = nums.size();
        int xr = 0;

        for (int x : nums)
            xr ^= x;

        if (xr != 0)
            return n;

        // Total XOR is 0. Remove one non-zero element.
        for (int x : nums) {
            if (x != 0)
                return n - 1;
        }

        return 0;
    }
};