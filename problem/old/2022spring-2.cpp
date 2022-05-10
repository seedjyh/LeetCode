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
int toKey(int r, int c) {
    return r * 100 + c;
}

class Node {
public:
    int r;
    int c;
    int toKey() {
        return r * 100 + c;
    }
};

Node fromKey(int key) {
    return Node{
            key / 100,
            key % 100
    };
}

class Solution {
public:
    int conveyorBelt(vector<string>& matrix, vector<int>& start, vector<int>& end) {
        int R = matrix.size();
        int C = matrix[0].size();
        vector<vector<int>> dis(R, vector<int>(C, 100000));
        set<int> boundary; // 位于边缘； grey
        // start
        vector<int> dirs{-1, 0, 1, 0, -1};
        vector<Node> flowDir(256);
        flowDir['^'] = Node{-1, 0};
        flowDir['v'] = Node{1, 0};
        flowDir['<'] = Node{0, -1};
        flowDir['>'] = Node{0, 1};
        // handle start node
        dis[start[0]][start[1]] = 0;
        boundary.insert(toKey(start[0], start[1]));
        auto flow = [&](int r, int c) {
            int nowDis = dis[r][c];
            while (true) {
                const Node &dirNode = flowDir[matrix[r][c]];
                int nextR = r + dirNode.r;
                int nextC = c + dirNode.c;
                if (nextR < 0 || nextR >= R || nextC < 0 || nextC >= C) {
                    break;
                }
                if (dis[nextR][nextC] <= nowDis) {
                    break;
                }
                dis[nextR][nextC] = nowDis;
                boundary.insert(toKey(nextR, nextC));
                r = nextR;
                c = nextC;
            }
        };
        flow(start[0], start[1]);
        for (int step = 1;; step++) {
//            // dump
//            cout << "step:" << step - 1 << ": ";
//            for (auto k : boundary) {
//                cout << "(" << fromKey(k).r << ", " << fromKey(k).c << "), ";
//            }
//            cout << endl;
            // dump end
            // load from boundary
            queue<int> pq;
            for (auto k : boundary) {
                pq.push(k);
            }
            boundary.clear();
            // span
            while (!pq.empty()) {
                int nowKey = pq.front();
                pq.pop();
                Node nowNode = fromKey(nowKey);
                for (int di = 0; di < 4; di++) {
                    Node nextNode{nowNode.r + dirs[di], nowNode.c + dirs[di + 1]};
                    if (nextNode.r < 0 || nextNode.r >= R || nextNode.c < 0 || nextNode.c >= C) {
                        continue;
                    }
                    if (dis[nextNode.r][nextNode.c] <= step) {
                        continue;
                    }
                    int nextKey = nextNode.toKey();
                    dis[nextNode.r][nextNode.c] = step;
                    boundary.insert(nextKey);
                    flow(nextNode.r, nextNode.c);
                }
            }
            if (dis[end[0]][end[1]] < 100000) {
                return dis[end[0]][end[1]];
            }
        }
        return -1;
    }
};

int main() {
    vector<string> matrix{">>v","v^<","<><"};
    vector<int> start{0, 1};
    vector<int> end{2, 0};
    cout << Solution().conveyorBelt(matrix, start, end) << endl;
    return 0;
}
