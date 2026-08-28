class Solution {
public:
    string lexPalindromicPermutation(string s, string target) {
        int n = s.size();
        int m = n / 2;

        vector<int> cnt(26);
        for (char c : s)
            cnt[c - 'a']++;

        // A palindrome is possible iff at most one character
        // has odd frequency.
        int odd = 0;
        int mid = -1;

        for (int c = 0; c < 26; c++) {
            if (cnt[c] & 1) {
                odd++;
                mid = c;
            }
        }

        if (odd > 1)
            return "";

        // Characters used in the left half.
        vector<int> half(26);
        for (int c = 0; c < 26; c++)
            half[c] = cnt[c] / 2;

        auto makePalindrome = [&](const string& left) {
            string ans = left;

            if (n & 1)
                ans += char('a' + mid);

            string rev = left;
            reverse(rev.begin(), rev.end());
            ans += rev;

            return ans;
        };

        /*
         * IMPORTANT:
         * First check whether the target's first half itself can be
         * used as the left half.
         *
         * If yes, the resulting palindrome is the smallest palindrome
         * whose left half is equal to target's left half.
         *
         * It may already be > target because of the second half.
         */
        string targetLeft = target.substr(0, m);

        vector<int> rem = half;
        bool possible = true;

        for (char c : targetLeft) {
            if (--rem[c - 'a'] < 0) {
                possible = false;
                break;
            }
        }

        if (possible) {
            string candidate = makePalindrome(targetLeft);

            if (candidate > target)
                return candidate;
        }

        /*
         * Now the equal-left-half candidate does not work.
         *
         * Therefore we need the smallest possible left half that is
         * strictly greater than targetLeft.
         *
         * Find the rightmost position where we can increase the
         * character, while keeping the prefix equal.
         */
        for (int i = m - 1; i >= 0; i--) {
            vector<int> leftCnt = half;

            // Use targetLeft[0..i-1].
            bool ok = true;

            for (int j = 0; j < i; j++) {
                int x = targetLeft[j] - 'a';

                if (leftCnt[x] == 0) {
                    ok = false;
                    break;
                }

                leftCnt[x]--;
            }

            if (!ok)
                continue;

            int cur = targetLeft[i] - 'a';

            // Smallest character greater than targetLeft[i].
            for (int c = cur + 1; c < 26; c++) {
                if (leftCnt[c] == 0)
                    continue;

                string left = targetLeft.substr(0, i);
                left += char('a' + c);
                leftCnt[c]--;

                // Complete the suffix minimally.
                for (int x = 0; x < 26; x++)
                    left.append(leftCnt[x], char('a' + x));

                return makePalindrome(left);
            }
        }

        return "";
    }
};