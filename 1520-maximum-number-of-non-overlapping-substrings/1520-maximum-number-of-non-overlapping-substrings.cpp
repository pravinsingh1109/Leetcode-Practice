#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<string> maxNumOfSubstrings(string s) {
        vector<int> first(26, -1), last(26, -1);

        // Find first and last occurrence of every character
        for (int i = 0; i < s.size(); i++) {
            int x = s[i] - 'a';

            if (first[x] == -1)
                first[x] = i;

            last[x] = i;
        }

        vector<pair<int, int>> intervals;

        // Find all valid minimum intervals
        for (int c = 0; c < 26; c++) {
            if (first[c] == -1)
                continue;

            int l = first[c];
            int r = last[c];
            bool valid = true;

            for (int i = l; i <= r; i++) {
                int x = s[i] - 'a';

                // This character occurs before l,
                // so current substring is invalid
                if (first[x] < l) {
                    valid = false;
                    break;
                }

                r = max(r, last[x]);
            }

            if (valid)
                intervals.push_back({l, r});
        }

        // Sort by ending position
        sort(intervals.begin(), intervals.end(),
             [](const pair<int, int>& a, const pair<int, int>& b) {
                 return a.second < b.second;
             });

        vector<string> ans;
        int lastEnd = -1;

        // Greedy: choose interval with earliest ending position
        for (auto &[l, r] : intervals) {
            if (l > lastEnd) {
                ans.push_back(s.substr(l, r - l + 1));
                lastEnd = r;
            }
        }

        return ans;
    }
};