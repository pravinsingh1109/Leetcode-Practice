#include <vector>
#include <string>

class Solution {
public:
    std::vector<int> validSequence(std::string word1, std::string word2) {
        int n = word1.length();
        int m = word2.length();

        // last[j] stores the maximum index in word1 where word2[j] is matched
        // such that suffix word2[j...m-1] can be matched exact-match (0 mismatches).
        std::vector<int> last(m + 1, -1);
        last[m] = n;

        // Step 1: Precompute `last` array from right to left
        int ptr = n - 1;
        for (int j = m - 1; j >= 0; --j) {
            while (ptr >= 0 && word1[ptr] != word2[j]) {
                ptr--;
            }
            last[j] = ptr;
            if (ptr >= 0) {
                ptr--; // Move past matched character
            }
        }

        std::vector<int> ans;
        ans.reserve(m);
        int p = 0;
        bool used_mismatch = false;

        // Step 2: Greedy matching from left to right
        for (int i = 0; i < m; ++i) {
            bool found = false;
            while (p < n) {
                bool is_match = (word1[p] == word2[i]);

                if (is_match) {
                    if (used_mismatch) {
                        // Mismatch credit already used: remaining suffix must match with 0 mismatches
                        if (last[i + 1] > p) {
                            ans.push_back(p);
                            p++;
                            found = true;
                            break;
                        }
                    } else {
                        // Mismatch credit still available: taking an exact match is ALWAYS safe 
                        // as long as the remaining word2[i+1...] can fit with at most 1 mismatch
                        ans.push_back(p);
                        p++;
                        found = true;
                        break;
                    }
                } else {
                    // Mismatch: use credit here, so remaining suffix needs 0 mismatches (last[i+1] > p)
                    if (!used_mismatch && last[i + 1] > p) {
                        used_mismatch = true;
                        ans.push_back(p);
                        p++;
                        found = true;
                        break;
                    }
                }
                p++;
            }

            if (!found) {
                return {};
            }
        }

        return ans;
    }
};