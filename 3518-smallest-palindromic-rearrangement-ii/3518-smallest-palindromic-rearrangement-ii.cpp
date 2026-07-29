class Solution {
public:
    static const int CAP = 1000000;
    vector<int> primes;

    Solution() {
        vector<bool> isPrime(5001, true);
        isPrime[0] = isPrime[1] = false;
        for (int i = 2; i * i <= 5000; i++) {
            if (isPrime[i]) {
                for (int j = i * i; j <= 5000; j += i)
                    isPrime[j] = false;
            }
        }
        for (int i = 2; i <= 5000; i++)
            if (isPrime[i]) primes.push_back(i);
    }

    int expFact(int n, int p) {
        int e = 0;
        while (n) {
            n /= p;
            e += n;
        }
        return e;
    }

    int binomCap(int n, int r) {
        if (r < 0 || r > n) return 0;
        r = min(r, n - r);
        long long res = 1;

        for (int p : primes) {
            if (p > n) break;
            int e = expFact(n, p) - expFact(r, p) - expFact(n - r, p);
            while (e--) {
                res *= p;
                if (res > CAP) return CAP + 1;
            }
        }
        return (int)res;
    }

    int multisetCount(vector<int>& cnt, int total) {
        long long ways = 1;
        int rem = total;

        for (int c : cnt) {
            if (c == 0) continue;
            int choose = binomCap(rem, c);
            ways *= choose;
            if (ways > CAP) return CAP + 1;
            rem -= c;
        }
        return (int)ways;
    }

    string smallestPalindrome(string s, int k) {
        vector<int> freq(26, 0);
        for (char c : s) freq[c - 'a']++;

        vector<int> half(26);
        char mid = 0;
        int len = 0;

        for (int i = 0; i < 26; i++) {
            half[i] = freq[i] / 2;
            len += half[i];
            if (freq[i] & 1) mid = char('a' + i);
        }

        if (multisetCount(half, len) < k) return "";

        string left;

        for (int pos = 0; pos < len; pos++) {
            for (int c = 0; c < 26; c++) {
                if (half[c] == 0) continue;

                half[c]--;
                int ways = multisetCount(half, len - pos - 1);

                if (ways >= k) {
                    left.push_back(char('a' + c));
                    break;
                } else {
                    k -= ways;
                    half[c]++;
                }
            }
        }

        string right = left;
        reverse(right.begin(), right.end());

        if (mid) return left + string(1, mid) + right;
        return left + right;
    }
};