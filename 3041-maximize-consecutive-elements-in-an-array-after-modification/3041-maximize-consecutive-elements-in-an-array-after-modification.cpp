class Solution {
public:
    int maxSelectedElements(vector<int>& nums) {
        sort(nums.begin(), nums.end());

        int a = 1, b = 1, ans = 1;

        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] == nums[i - 1]) {
                b = a + 1;
            }
            else if (nums[i] == nums[i - 1] + 1) {
                a++;
                b++;
            }
            else if (nums[i] == nums[i - 1] + 2) {
                a = b + 1;
                b = 1;
            }
            else {
                a = b = 1;
            }

            ans = max({ans, a, b});
        }

        return ans;
    }
};