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

class Data {
public:
    int two;
    int five;
    int countZero() {
        return min(two, five);
    }
};

class Node {
public:
    Data self;
    Data right;
    Data up;
    Data down;
    Data left;
};

class Solution {
public:
    int maxTrailingZeros(vector<vector<int>>& grid) {
        int R = grid.size();
        int C = grid[0].size();
        vector<vector<Node>> nodes(R, vector<Node>(C));
        // self
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                nodes[i][j].self = getData(grid[i][j]);
            }
        }
        // up
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                if (i == 0) {
                    nodes[i][j].up = nodes[i][j].self;
                } else {
                    nodes[i][j].up = addData(nodes[i][j].self, nodes[i - 1][j].up);
                }
            }
        }
        // down
        for (int i = R - 1; i >= 0; i--) {
            for (int j = 0; j < C; j++) {
                if (i == R - 1) {
                    nodes[i][j].down = nodes[i][j].self;
                } else {
                    nodes[i][j].down = addData(nodes[i][j].self, nodes[i + 1][j].down);
                }
            }
        }
        // left
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                if (j == 0) {
                    nodes[i][j].left = nodes[i][j].self;
                } else {
                    nodes[i][j].left = addData(nodes[i][j].self, nodes[i][j - 1].left);
                }
            }
        }
        // right
        for (int i = 0; i < R; i++) {
            for (int j = C - 1; j >= 0; j--) {
                if (j == C - 1) {
                    nodes[i][j].right = nodes[i][j].self;
                } else {
                    nodes[i][j].right = addData(nodes[i][j].self, nodes[i][j + 1].right);
                }
            }
        }
        // get ans
        int ans = 0;
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                ans = max(ans, removeData(addData(nodes[i][j].up, nodes[i][j].right), nodes[i][j].self).countZero());
                ans = max(ans, removeData(addData(nodes[i][j].up, nodes[i][j].left), nodes[i][j].self).countZero());
                ans = max(ans, removeData(addData(nodes[i][j].down, nodes[i][j].right), nodes[i][j].self).countZero());
                ans = max(ans, removeData(addData(nodes[i][j].down, nodes[i][j].left), nodes[i][j].self).countZero());
            }
        }
        return ans;
    }
    Data getData(int raw) {
        Data ans{0, 0};
        while (raw > 0) {
            if (raw % 2 == 0) {
                ans.two++;
                raw /= 2;
            } else if (raw % 5 == 0) {
                ans.five++;
                raw /= 5;
            } else {
                break;
            }
        }
        return ans;
    }
    Data addData(const Data &d1, const Data &d2) {
        if (LL(d1.two + d2.two) > LL(2147483647)) {
            throw -1;
        }
        if (LL(d1.five + d2.five) > LL(2147483647)) {
            throw -1;
        }
        return Data{d1.two + d2.two, d1.five + d2.five};
    }
    Data removeData(const Data &from, const Data &to) {
        return Data{from.two - to.two, from.five - to.five};
    }
};

int main() {
    vector<vector<int>> grid{{23,17,15,3,20},{8,1,20,27,11},{9,4,6,2,21},{40,9,1,10,6},{22,7,4,5,3}};
    cout << Solution().maxTrailingZeros(grid) << endl;
    return 0;
}
