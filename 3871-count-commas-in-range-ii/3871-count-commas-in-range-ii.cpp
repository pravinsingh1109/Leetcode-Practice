class Solution {
public:
    long long countCommas(long long n) {
        long long ans = 0;
        
        // Numbers with 4-6 digits have 1 comma.
        // Numbers with 7-9 digits have 2 commas, etc.
        for (long long p = 1000; p <= n; p *= 1000) {
            ans += n - p + 1;
            
            // Prevent overflow (though n <= 1e15).
            if (p > n / 1000) break;
        }
        
        return ans;
    }
};