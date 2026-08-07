#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
    struct Factors {
        int a = 0, b = 0, c = 0, d = 0; // powers of 2, 3, 5, 7
    };

    bool factorize(long long t, Factors& f) {
        while (t % 2 == 0) { f.a++; t /= 2; }
        while (t % 3 == 0) { f.b++; t /= 3; }
        while (t % 5 == 0) { f.c++; t /= 5; }
        while (t % 7 == 0) { f.d++; t /= 7; }
        return t == 1;
    }

    Factors consume(Factors f, int dig) {
        if (dig == 2) f.a = max(0, f.a - 1);
        else if (dig == 3) f.b = max(0, f.b - 1);
        else if (dig == 4) f.a = max(0, f.a - 2);
        else if (dig == 5) f.c = max(0, f.c - 1);
        else if (dig == 6) { f.a = max(0, f.a - 1); f.b = max(0, f.b - 1); }
        else if (dig == 7) f.d = max(0, f.d - 1);
        else if (dig == 8) f.a = max(0, f.a - 3);
        else if (dig == 9) f.b = max(0, f.b - 2);
        return f;
    }

    int getMinLen(const Factors& f) {
        int min_23 = 1e9;
        for (int x = 0; x <= min(f.a, f.b); ++x) {
            int rem_a = max(0, f.a - x);
            int rem_b = max(0, f.b - x);
            int eights = (rem_a + 2) / 3;
            int nines = (rem_b + 1) / 2;
            min_23 = min(min_23, x + eights + nines);
        }
        return f.c + f.d + min_23;
    }

    // Correct greedily-constructed smallest suffix
    string buildSmallestSuffix(int len, Factors f) {
        string res = "";
        for (int i = 0; i < len; ++i) {
            int rem_len = len - 1 - i;
            for (int dig = 1; dig <= 9; ++dig) {
                Factors next_f = consume(f, dig);
                if (getMinLen(next_f) <= rem_len) {
                    res += to_string(dig);
                    f = next_f;
                    break;
                }
            }
        }
        return res;
    }

public:
    string smallestNumber(string num, long long t) {
        Factors target_f;
        if (!factorize(t, target_f)) return "-1";

        int n = num.length();

        vector<Factors> pref_rem(n + 1);
        pref_rem[0] = target_f;
        
        int first_zero = -1;
        for (int i = 0; i < n; ++i) {
            if (num[i] == '0') {
                first_zero = i;
                break;
            }
            pref_rem[i + 1] = consume(pref_rem[i], num[i] - '0');
        }

        if (first_zero == -1) {
            Factors rem = pref_rem[n];
            if (rem.a == 0 && rem.b == 0 && rem.c == 0 && rem.d == 0) {
                return num;
            }
        }

        int limit = (first_zero == -1) ? n - 1 : first_zero;

        for (int p = limit; p >= 0; --p) {
            Factors current_f = pref_rem[p];
            int start_dig = num[p] - '0' + 1;
            int rem_len = n - 1 - p;

            for (int dig = start_dig; dig <= 9; ++dig) {
                Factors next_f = consume(current_f, dig);
                if (getMinLen(next_f) <= rem_len) {
                    string ans = num.substr(0, p) + to_string(dig);
                    ans += buildSmallestSuffix(rem_len, next_f);
                    return ans;
                }
            }
        }

        int target_len = max(n + 1, getMinLen(target_f));
        return buildSmallestSuffix(target_len, target_f);
    }
};