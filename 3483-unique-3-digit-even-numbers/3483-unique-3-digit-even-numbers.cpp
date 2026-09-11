class Solution {
public:
    int totalNumbers(vector<int>& digits) {
        int ans = 0;

        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                for (int k = 0; k < 10; k++) {
                    if (k % 2 != 0 || i == 0) continue;

                    vector<int> need = {i, j, k};
                    vector<int> cnt(10, 0), have(10, 0);

                    for (int d : digits) cnt[d]++;
                    for (int d : need) have[d]++;

                    bool ok = true;
                    for (int d = 0; d < 10; d++) {
                        if (have[d] > cnt[d]) {
                            ok = false;
                            break;
                        }
                    }

                    if (ok) ans++;
                }
            }
        }

        return ans;
    }
};