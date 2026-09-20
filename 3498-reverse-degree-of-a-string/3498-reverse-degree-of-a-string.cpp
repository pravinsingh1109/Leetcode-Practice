class Solution {
public:
    int reverseDegree(string s) {
        int ans = 0;

        for (int i = 0; i < s.length(); i++) {
            int reversedValue = 'z' - s[i] + 1;
            int position = i + 1;

            ans += reversedValue * position;
        }

        return ans;
    }
};