class Solution {
public:
    vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {
        int n = nums.size();

        // {value, original index}
        vector<pair<int, int>> a;
        for (int i = 0; i < n; i++) {
            a.push_back({nums[i], i});
        }

        sort(a.begin(), a.end());

        vector<int> ans(n);

        int start = 0;

        while (start < n) {
            int end = start;

            // Values can belong to the same group if consecutive
            // sorted values differ by <= limit.
            while (end + 1 < n &&
                   a[end + 1].first - a[end].first <= limit) {
                end++;
            }

            // All indices in this group can be freely rearranged.
            // Put the sorted values at the sorted original indices.
            vector<int> indices;

            for (int i = start; i <= end; i++) {
                indices.push_back(a[i].second);
            }

            sort(indices.begin(), indices.end());

            for (int i = start; i <= end; i++) {
                ans[indices[i - start]] = a[i].first;
            }

            start = end + 1;
        }

        return ans;
    }
};