class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        int n = s.size();

        // Try every possible position from right to left.
        // Prefix [0..i-1] must equal target.
        for (int i = n - 1; i >= 0; --i) {
            vector<int> cnt(26, 0);

            // Characters available after fixing target[0..i-1].
            for (char c : s)
                cnt[c - 'a']++;

            bool possible = true;

            for (int j = 0; j < i; ++j) {
                int x = target[j] - 'a';
                if (cnt[x] == 0) {
                    possible = false;
                    break;
                }
                cnt[x]--;
            }

            if (!possible)
                continue;

            // At position i, choose the smallest character
            // strictly greater than target[i].
            int x = target[i] - 'a';

            for (int c = x + 1; c < 26; ++c) {
                if (cnt[c] > 0) {
                    string ans = target.substr(0, i);
                    ans += char('a' + c);
                    cnt[c]--;

                    // Smallest possible suffix.
                    for (int k = 0; k < 26; ++k) {
                        ans.append(cnt[k], char('a' + k));
                    }

                    return ans;
                }
            }
        }

        return "";
    }
};