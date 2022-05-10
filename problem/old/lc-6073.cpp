//
// Created by jyh on 1月22日.
//
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <queue>
#include <sstream>
#include <limits>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <functional>
using namespace std;

typedef long long LL;

class Solution {
public:
    int longestPath(vector<int>& parent, string s) {
        int n = s.size();
        vector<vector<int>> children(n);
        for (int i = 0; i < n; i++) {
            if (i > 0) {
                children[parent[i]].push_back(i);
            }
        }
        vector<multiset<int>> nodeLength(n);
        function<int(int)> dfs = [&](int root) {
            for (auto ch : children[root]) {
                int childAns = dfs(ch);
                if (s[ch] != s[root]) {
                    nodeLength[root].insert(childAns);
                }
            }
            if (nodeLength[root].empty()) {
                return 1;
            }
            return 1 + *(--(nodeLength[root].end()));
        };
        dfs(0);
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int nowAns = 0;
            if (nodeLength[i].size() == 0) {
                nowAns = 0;
            } else if (nodeLength[i].size() == 1) {
                nowAns = *nodeLength[i].begin();
            } else {
                auto ite = nodeLength[i].end();
                --ite;
                nowAns += *ite;
                --ite;
                nowAns += *ite;
            }
            ans = max(ans, 1 + nowAns);
        }
        return ans;
    }
};
int main() {
//    vector<int> parent{-1,0,0,1,1,2};
//    string s = "abacbe";
//    vector<int> parent{-1};
//    string s = "z";
//    vector<int> parent{-1,0};
//    string s = "mm";
    vector<int> parent{-1,0,1};
    string s = "aab";
    cout << Solution().longestPath(parent, s) << endl;
    return 0;
}
