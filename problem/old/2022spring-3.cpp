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
using namespace std;

typedef long long LL;

class TimeAns {
public:
    vector<vector<int>> v;
    TimeAns(): v(vector<vector<int>>(3, vector<int>(3, -1))){};
};

class Solution {
public:
    int getMaximumNumber(vector<vector<int>>& moles) {
        map<int, vector<vector<int>>> timeMoles; // 可能的时间
        timeMoles[0] = {};
        for (auto &m : moles) {
            timeMoles[m[0]].push_back({m[1], m[2]});
        }
        vector<int> times;
        for (auto ite : timeMoles) {
            times.push_back(ite.first);
        }
        // prepare
        vector<vector<int>> span[3][3][5];
        for (int r = 0; r < 3; r++) {
            for (int c = 0; c < 3; c++) {
                for (int step = 1; step <= 4; step++) {
                    for (int i = 0; i < 3; i++) {
                        for (int j = 0; j < 3; j++) {
                            if (abs(i - r) + abs(j - c) <= step) {
                                span[r][c][step].push_back({i, j});
                            }
                        }
                    }
                }
            }
        }
        // start
        TimeAns now;
        now.v[1][1] = 0;
        for (auto &m : timeMoles[0]) {
            if (m[0] == 1 && m[1] == 1) {
                now.v[1][1]++;
            }
        }
        vector<int> dirs{-1, 0, 1, 0, -1};
        for (int ti = 1; ti < times.size(); ti++) {
            int costTime = min(times[ti] - times[ti - 1], 4);
            if (costTime >= 4) {
                int nowMax = 0;
                for (int r = 0; r < 3; r++) {
                    for (int c = 0; c < 3; c++) {
                        nowMax = max(nowMax, now.v[r][c]);
                    }
                }
                for (int r = 0; r < 3; r++) {
                    for (int c = 0; c < 3; c++) {
                        now.v[r][c] = nowMax;
                    }
                }
            } else {
                auto pre = now;
                for (int r = 0; r < 3; r++) {
                    for (int c = 0; c < 3; c++) {
                        for (auto &sp : span[r][c][costTime]) {
                            now.v[r][c] = max(now.v[r][c], pre.v[sp[0]][sp[1]]);
                        }
                    }
                }
            }
            // 在当前层执行敲击
            for (auto &m : timeMoles[times[ti]]) {
                now.v[m[0]][m[1]]++;
            }
        }
        int ans = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                ans = max(ans, now.v[i][j]);
            }
        }
        return ans;
    }
};

int main() {
    vector<vector<int>> moles{{1,1,0}, {2,0,1},{4,2,2}};
    cout << Solution().getMaximumNumber(moles) << endl;
    moles = vector<vector<int>>{{2,0,2},{5,2,0},{4,1,0},{1,2,1},{3,0,2}};
    cout << Solution().getMaximumNumber(moles) << endl;
    moles = vector<vector<int>>{{0,1,0},{0,0,1}};
    cout << Solution().getMaximumNumber(moles) << endl;
    return 0;
}
