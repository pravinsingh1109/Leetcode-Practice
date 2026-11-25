class Solution {
public:
    int minMoves2(vector<int>& nums) {
        sort(nums.begin(), nums.end());

        int median = nums[nums.size() / 2];
        long long ans = 0;

        for (int x : nums)
            ans += abs((long long)x - median);

        return ans;
    }
};