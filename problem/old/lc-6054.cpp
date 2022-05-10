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

int INT_MAX = 2147483647;

typedef long long LL;

class Pos {
public:
    int r;
    int c;
};

class Solution {
    int R;
    int C;
    vector<vector<int>> burnt;
    vector<int> dirs;
public:
    int maximumMinutes(vector<vector<int>>& grid) {
        R = grid.size();
        C = grid[0].size();
        burnt = vector<vector<int>>(R, vector<int>(C, INT_MAX));
        dirs = vector<int>{-1, 0, 1, 0, -1};
        // burn
        queue<Pos> pq;
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                if (grid[i][j] == 1) {
                    burnt[i][j] = 0;
                    pq.push({i, j});
                }
            }
        }
        while (!pq.empty()) {
            auto now = pq.front();
            pq.pop();
            for (int di = 0; di < 4; di++) {
                auto next = Pos{now.r + dirs[di], now.c + dirs[di + 1]};
                if (next.r < 0 || next.r >= R || next.c < 0 || next.c >= C) {
                    continue;
                }
                if (grid[next.r][next.c] != 0) {
                    continue;
                }
                if (burnt[next.r][next.c] < burnt[now.r][now.c] + 1) {
                    continue;
                }
                burnt[next.r][next.c] = burnt[now.r][now.c] + 1;
                pq.push(next);
            }
        }
        // burn dump
//        for (int i = 0; i < R; i++) {
//            for (int j = 0; j < C; j++) {
//                if (grid[i][j] == 2) {
//                    cout << " W";
//                } else if (burnt[i][j] == INT_MAX) {
//                    cout << " S";
//                } else {
//                    printf("%2d", burnt[i][j]);
//                }
//                cout << " ";
//            }
//            cout << endl;
//        }
        int lo = 0;
        int hi = 1e9;
        while (lo + 1 < hi) {
            int mid = (lo + hi) / 2;
            if (check(grid, mid)) {
                lo = mid;
            } else {
                hi = mid - 1;
            }
        }
        if (check(grid, hi)) {
            return hi;
        } else if (check(grid, lo)) {
            return lo;
        } else {
            return -1;
        }
    }
    bool check(const vector<vector<int>>& grid, int wait) {
        vector<vector<int>> arrive(R, vector<int>(C, INT_MAX));
        queue<Pos> pq;
        arrive[0][0] = wait;
        pq.push({0, 0});
        while (!pq.empty()) {
            auto now = pq.front();
            pq.pop();
            for (int di = 0; di < 4; di++) {
                auto next = Pos{now.r + dirs[di], now.c + dirs[di + 1]};
                if (next.r < 0 || next.r >= R || next.c < 0 || next.c >= C) {
                    continue;
                }
                if (grid[next.r][next.c] == 2) {
                    continue;
                }
                if (arrive[next.r][next.c] != INT_MAX) {
                    continue;
                }
                if (next.r == R - 1 && next.c == C - 1) {
                    if (arrive[now.r][now.c] + 1 <= burnt[next.r][next.c]) {
                        return true;
                    } else {
                        return false;
                    }
                }
                if (arrive[now.r][now.c] + 1 >= burnt[next.r][next.c]) {
                    continue;
                }
                arrive[next.r][next.c] = arrive[now.r][now.c] + 1;
                pq.push(next);
            }
        }
        return false;
    }
};

int main() {
    vector<vector<int>> grid{{0,2,0,0,0,0,0,0,0,2,0,2,0,2,2,0,2,0,0,0,0,0},{0,0,0,2,2,2,0,2,0,0,0,0,0,0,0,0,0,0,2,2,2,2},{0,2,2,2,2,2,2,2,2,0,2,2,2,0,2,2,2,0,0,2,0,2},{0,0,2,0,0,0,2,0,2,2,2,2,2,2,2,2,2,2,0,0,0,0},{2,0,0,0,2,0,0,0,0,2,0,0,0,0,0,0,0,2,2,0,2,0},{0,0,2,0,2,0,2,2,0,0,0,2,2,2,2,0,2,2,0,0,2,0},{2,2,2,0,2,2,2,2,2,2,0,0,0,0,2,0,0,2,2,0,2,0},{0,0,0,0,0,0,0,0,0,2,0,2,0,2,2,2,2,2,2,0,2,0},{2,0,2,0,2,0,2,0,2,2,0,2,0,0,0,0,2,0,2,0,2,2},{0,0,2,0,2,0,2,0,2,2,0,2,2,0,2,0,0,0,2,2,2,2},{0,2,2,0,2,0,2,0,2,1,0,0,2,2,2,0,2,0,0,2,0,0},{0,2,2,0,2,2,2,0,2,2,2,0,0,0,2,0,2,2,0,0,0,2},{0,2,2,0,2,0,0,0,0,0,2,2,0,2,2,2,1,2,2,0,2,1},{0,2,2,0,2,2,2,0,2,0,2,2,0,0,0,0,2,2,0,0,0,2},{0,2,0,0,2,0,0,0,2,0,2,0,0,2,0,2,2,0,0,2,0,0},{2,2,2,0,2,2,0,2,2,0,2,2,0,2,2,2,2,2,0,2,2,0},{0,0,0,0,2,2,0,2,0,0,2,2,0,0,0,0,0,2,0,2,0,0}};
    cout << Solution().maximumMinutes(grid) << endl;
    return 0;
}
