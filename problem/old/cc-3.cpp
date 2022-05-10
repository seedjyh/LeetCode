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


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    TreeNode(int x, TreeNode *l, TreeNode *r) : val(x), left(l), right(r) {}
};


class Solution {
    set<int> nodes;
public:
    int getNumber(TreeNode* root, vector<vector<int>>& ops) {
        int ans = 0;
        init(root);
        for (int i = (int)ops.size() - 1; i >= 0; i--) {
            int type = ops[i][0];
            int x = ops[i][1];
            int y = ops[i][2];
            vector<int> removed;
            for (auto ite = nodes.lower_bound(x); ite != nodes.end(); ++ite) {
                if (*ite <= y) {
                    removed.push_back(*ite);
                } else {
                    break;
                }
            }
            for (auto x : removed) {
                if (type == 1) {
                    ans++;
                }
                nodes.erase(x);
            }
        }
        return ans;
    }
    void init(const TreeNode *root) {
        if (root == nullptr) {
            return;
        }
        init(root->left);
        init(root->right);
        nodes.insert(root->val);
        return;
    }
};
int main() {
    TreeNode *root = new TreeNode(
        4,
        new TreeNode(
            2,
            new TreeNode(1),
            nullptr
        ),
        new TreeNode(
            7,
            new TreeNode(
                5,
                nullptr,
                new TreeNode(6)
            ),
            nullptr
        )
    );
    vector<vector<int>> ops{
            {0,2,2}, {1,1,5}, {0,4,5}, {1,5,7},
    };
    cout << Solution().getNumber(root, ops) << endl;
    return 0;
}
