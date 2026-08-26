class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        int n = s.size();
        int left = 0, ones = 0;
        int bestLen = INT_MAX;
        string ans = "";

        for (int right = 0; right < n; right++) {
            if (s[right] == '1')
                ones++;

            while (ones > k) {
                if (s[left] == '1')
                    ones--;
                left++;
            }

            if (ones == k) {
                // Remove leading zeros to get the shortest substring.
                while (left <= right && s[left] == '0')
                    left++;

                int len = right - left + 1;

                if (len < bestLen) {
                    bestLen = len;
                    ans = s.substr(left, len);
                } else if (len == bestLen) {
                    string cur = s.substr(left, len);
                    if (ans.empty() || cur < ans)
                        ans = cur;
                }
            }
        }

        return ans;
    }
};