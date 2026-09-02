class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        int odd = 0, even = 0;

        for (int x : nums1) {
            if (x % 2)
                odd++;
            else
                even++;
        }

        // If all are already same parity
        if (odd == nums1.size() || even == nums1.size())
            return true;

        // If both parities exist, we can make all elements odd
        // by subtracting an opposite-parity element.
        return true;
    }
};