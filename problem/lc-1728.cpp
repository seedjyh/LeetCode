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


class TopologicalSorting {
    class Node {
    public:
        Node(int id) {
            this->id = id;
            this->prevCount = 0;
            this->next.clear();
        };
        int id;
        int prevCount;
        set<int> next;
    };

    map<int, Node *> id2node;
public:
    TopologicalSorting() {};

    void SetID(int id) {
        getNode(id);
    }

    void SetOrder(int before, int after) {
        Node *beforeNode = getNode(before);
        Node *afterNode = getNode(after);
        if (before == after) {
            return;
        }
        if (beforeNode->next.find(after) == beforeNode->next.end()) {
            afterNode->prevCount++;
            beforeNode->next.insert(after);
        }
    }

    Node *getNode(int id) {
        if (this->id2node.find(id) == id2node.end()) {
            this->id2node[id] = new Node(id);
        }
        return this->id2node[id];
    }

    int Size() const {
        return this->id2node.size();
    }

    vector<int> Sort() {
        vector<int> result;
        queue<int> noPrevNodes;
        // find nodes without prev
        for (auto ite: id2node) {
            if (ite.second->prevCount == 0) {
                noPrevNodes.push(ite.first);
            }
        }
        // start work
        while (!noPrevNodes.empty()) {
            int topNodeID = noPrevNodes.front();
            noPrevNodes.pop();
            result.push_back(topNodeID);
            Node *topNode = id2node[topNodeID];
            for (auto nextNodeID: topNode->next) {
                Node *nextNode = id2node[nextNodeID];
                nextNode->prevCount--;
                if (nextNode->prevCount == 0) {
                    noPrevNodes.push(nextNodeID);
                }
            }
            id2node.erase(topNodeID);
            delete topNode;
        }
        // 允许出现循环
        return result;
    }
};

class Position {
public:
    int r;
    int c;
    bool operator==(const Position &other) const {
        return this->r == other.r && this->c == other.c;
    };
};

typedef enum {
    TurnMouse = 0,
    TurnCat = 1,
}Turn;

class State {
public:
    Position cat;
    Position mouse;
    Turn turn;
    int key() const {
        return (turn << 12) | (cat.r << 9) | (cat.c << 6) | (mouse.r << 3) | mouse.c;
    }
};

typedef enum  {
    WinnerUnknown = 0,
    WinnerMouse = 1,
    WinnerCat = 2,
}Winner;

class StateValue {
public:
    int stepToEnd;
    Winner winner;
};

class Solution {
    Position foodPosition, catStartPosition, mouseStartPosition;
    int R;
    int C;
    vector<string> grid;
    int catJump;
    int mouseJump;
    // my data
    TopologicalSorting ts;
    unordered_map<int, StateValue> key2value;
public:
    bool canMouseWin(vector<string> &grid, int catJump, int mouseJump) {
        R = grid.size();
        C = grid[0].size();
        this->catJump = catJump;
        this->mouseJump = mouseJump;
        this->grid = grid;
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                switch (grid[i][j]) {
                    case 'C': catStartPosition = Position{i, j}; break;
                    case 'M': mouseStartPosition = Position{i, j}; break;
                    case 'F': foodPosition = Position{i, j}; break;
                };
            }
        }
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                Position mousePosition{i, j};
                if (grid[i][j] == '#') {
                    continue;
                }
                for (int k = 0; k < R; k++) {
                    for (int l = 0; l < C; l++) {
                        Position catPosition{k, l};
                        if (grid[k][l] == '#') {
                            continue;
                        }
                        expendState(State{catPosition, mousePosition, TurnMouse});
                        expendState(State{catPosition, mousePosition, TurnCat});
                    }
                }
            }
        }
        vector<int> sortedStates = ts.Sort();
        for (auto key : sortedStates) {
            if (key2value.find(key) == key2value.end()) {
                continue;
            }
            // check
        }
        State startState{catStartPosition, mouseStartPosition, TurnMouse};
        auto ite = key2value.find(startState.key());
        if (ite != key2value.end()) {
            if (ite->second.winner == WinnerMouse && ite->second.stepToEnd <= 1000) {
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    }
    void expendState(const State &raw) {
        if (raw.cat == raw.mouse) {
            if (raw.cat == foodPosition) {
                if (raw.turn == TurnCat) {
                    key2value[raw.key()] = StateValue{0, WinnerCat};
                } else {
                    key2value[raw.key()] = StateValue{0, WinnerMouse};
                }
            } else {
                key2value[raw.key()] = StateValue{0, WinnerCat};
            }
            return;
        } else {
            if (raw.cat == foodPosition) {
                key2value[raw.key()] = StateValue{0, WinnerCat};
                return;
            } else if (raw.mouse == foodPosition) {
                key2value[raw.key()] = StateValue{0, WinnerMouse};
                return;
            }
        }
        static const vector<int> dirs{-1, 0, 1, 0, -1};
        if (raw.turn == TurnCat) {
            for (int di = 0; di < 4; di++) {
                for (int step = 0; step <= catJump; step++) {
                    State next = raw;
                    next.cat.r += dirs[di] * step;
                    next.cat.c += dirs[di + 1] * step;
                    next.turn = TurnMouse;
                    if (next.cat.r < 0 || next.cat.r >= R || next.cat.c < 0 || next.cat.c >= C) {
                        break;
                    }
                    if (grid[next.cat.r][next.cat.c] == '#') {
                        break;
                    }
                    ts.SetOrder(next.key(), raw.key());
                }
            }
        } else { // turnMouse
            for (int di = 0; di < 4; di++) {
                for (int step = 0; step <= mouseJump; step++) {
                    State next = raw;
                    next.mouse.r += dirs[di] * step;
                    next.mouse.c += dirs[di + 1] * step;
                    next.turn = TurnCat;
                    if (next.mouse.r < 0 || next.mouse.r >= R || next.mouse.c < 0 || next.mouse.c >= C) {
                        break;
                    }
                    if (grid[next.mouse.r][next.mouse.c] == '#') {
                        break;
                    }
                    ts.SetOrder(next.key(), raw.key());
                }
            }
        }
    }
};

int main() {
    vector<string> grid{"C...#", "...#F", "....#", "M...."};
    int catJump = 2;
    int mouseJump = 5;
    cout << Solution().canMouseWin(grid, catJump, mouseJump) << endl;
    return 0;
}
