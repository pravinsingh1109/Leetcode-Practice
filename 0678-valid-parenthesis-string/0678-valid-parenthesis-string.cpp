class Solution {
public:
    bool checkValidString(string s) {
        int low = 0;   // minimum possible open brackets
        int high = 0;  // maximum possible open brackets

        for (char c : s) {
            if (c == '(') {
                low++;
                high++;
            }
            else if (c == ')') {
                low--;
                high--;
            }
            else { // '*'
                low--;   // '*' as ')'
                high++;  // '*' as '('
            }

            if (high < 0)
                return false;

            if (low < 0)
                low = 0;
        }

        return low == 0;
    }
};