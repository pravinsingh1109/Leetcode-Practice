#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string s;
    int i = 0;

    // Parse an expression until ',' or '}'
    set<string> parse() {
        set<string> ans;
        ans.insert("");

        while (i < s.size() && s[i] != '}' && s[i] != ',') {
            set<string> part;

            if (s[i] == '{') {
                part = parseBrace();
            } else {
                part.insert(string(1, s[i]));
                i++;
            }

            // Cartesian product / concatenation
            set<string> temp;

            for (const string &a : ans) {
                for (const string &b : part) {
                    temp.insert(a + b);
                }
            }

            ans = temp;
        }

        return ans;
    }

    // Parse {...}
    set<string> parseBrace() {
        i++; // skip '{'

        set<string> ans = parse();

        while (i < s.size() && s[i] == ',') {
            i++; // skip ','

            set<string> part = parse();

            ans.insert(part.begin(), part.end());
        }

        i++; // skip '}'

        return ans;
    }

    vector<string> braceExpansionII(string expression) {
        s = expression;
        i = 0;

        set<string> result = parse();

        return vector<string>(result.begin(), result.end());
    }
};