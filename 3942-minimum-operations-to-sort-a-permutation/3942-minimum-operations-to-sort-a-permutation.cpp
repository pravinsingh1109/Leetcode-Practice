class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        int a = nums[0];

        bool forward = true, backward = true;

        for (int i = 0; i < n; i++) {
            if (nums[i] != (a + i) % n)
                forward = false;

            if (nums[i] != (a - i + n) % n)
                backward = false;
        }

        // nums is a rotation of [0, 1, ..., n-1]
        if (forward) {
            int k = (n - a) % n;
            return min(k, n - k + 2);
        }

        // nums is a reversed rotation
        if (backward) {
            int k = n - 1 - a;
            return min(k, n - k) + 1;
        }

        return -1;
    }
};