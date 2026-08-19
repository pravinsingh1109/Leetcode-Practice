class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        unordered_map<int, int> mp;

        for (auto &r : reservedSeats) {
            int row = r[0], seat = r[1];

            // Only seats 2..9 affect possible groups.
            if (seat >= 2 && seat <= 9)
                mp[row] |= (1 << seat);
        }

        int ans = (n - mp.size()) * 2;

        for (auto &[row, mask] : mp) {
            bool left  = !(mask & ((1 << 2) | (1 << 3) | (1 << 4) | (1 << 5)));
            bool right = !(mask & ((1 << 6) | (1 << 7) | (1 << 8) | (1 << 9)));
            bool mid   = !(mask & ((1 << 4) | (1 << 5) | (1 << 6) | (1 << 7)));

            if (left && right)
                ans += 2;
            else if (left || right || mid)
                ans += 1;
        }

        return ans;
    }
};