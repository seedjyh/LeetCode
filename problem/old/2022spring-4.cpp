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

class Solution {
    vector<vector<int>> pos2edge;
    vector<vector<string>> edges;
public:
    bool composeCube(vector<vector<string>>& shapes) {
        pos2edge = vector<vector<int>>{
                {0, 1, 2, 3},
                {4, 5, 6, 4},
                {3, 8, 7, 11},
                {1, 9, 5, 10},
                {8, 10, 6, 7},
                {0, 9, 4, 8},
        };
        edges.resize(12);
        vector<int> indexList;
        return dfs(indexList, shapes);
    }
    bool dfs(vector<int> &indexList, vector<vector<string>> &shapes) {
        if (indexList.size() >= 6) {
            return true;
        }
        for (int i = 0; i < 6; i++) {
            bool used = false;
            for (auto x : indexList) {
                if (x == i) {
                    used = true;
                    break;
                }
            }
            if (used) {
                continue;
            }
            for (int side = 0; side < 2; side++) {
                for (int dir = 0; dir < 4; dir++) {
                    place(indexList.size(), shapes[i], side, dir);
                    if (check()) {
                        indexList.push_back(i);
                        if (dfs(indexList, shapes)) {
                            return true;
                        }
                        indexList.pop_back();
                    }
                    unplace(indexList.size(), side, dir);
                }
            }
        }
        return false;
    }
    void place(int pos, vector<string> &shape, int side, int dir) {
        auto edgeForPos = pos2edge[pos];
        vector<int> realIndex;
        if (side) {
            placeEdge(shape, 0, side)
            realIndex = vector<int>{0, 1, 2, 3};
        } else {
            realIndex = vector<int>{3, 2, 1, 0};
        }
    }
    void unplace(int pos, int side, int dir) {

    }
    bool check() {
        for (auto &ep : edges) {
            if (ep.size() == 2) {
                for (int i = 0; i < ep[0].size(); i++) {
                    if ((ep[0][i] - '0') + (ep[1][i] - '0') != 1) {
                        return false;
                    }
                }
            }
        }
        return true;
    }
};

int main() {
    vector<vector<string>> shapes{{"000","110","000"},{"110","011","000"},{"110","011","110"},{"000","010","111"},{"011","111","011"},{"011","010","000"}};
    cout << Solution().composeCube(shapes) << endl;
    return 0;
}
