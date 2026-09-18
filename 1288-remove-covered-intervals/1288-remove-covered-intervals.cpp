class Solution {
public:
    int removeCoveredIntervals(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {
            if (a[0] == b[0])
                return a[1] > b[1];
            return a[0] < b[0];
        });

        int count = 0;
        int maxRight = 0;

        for (auto &interval : intervals) {
            int left = interval[0];
            int right = interval[1];

            if (right > maxRight) {
                count++;
                maxRight = right;
            }
        }

        return count;
    }
};