class Solution {
public:
    bool check(int x, int t) {
        int prod = 1;
        while (x > 0) {
            prod *= (x % 10);
            x /= 10;
        }
        return prod % t == 0;
    }

    int smallestNumber(int n, int t) {
        while (!check(n, t)) n++;
        return n;
    }
};