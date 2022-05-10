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
#include <cmath>
using namespace std;

typedef long long LL;
class Solution {
public:
    int largestPalindrome(int n) {
        if (n == 1) {
            return 9;
        }
        vector<LL> tens{1};
        for (int i = 1; i <= 9; i++) {
            tens.push_back(tens[i - 1] * (LL)10);
        }
        for (LL left = tens[n] - 1; left > tens[n - 1]; left--) {
            LL real = left * tens[n] + reverse(left);
            if (check(real, tens[n - 1], tens[n])) {
                return mod(real);
            }
        }
        return -1;
    }
    LL mod(LL raw) {
        return raw % 1337;
    }
    LL reverse(LL raw) {
        LL ans = 0;
        while (raw > 0) {
            ans = ans * 10 + (raw % 10);
            raw /= 10;
        }
        return ans;
    }
    bool check(LL raw, LL from, LL to) {
        auto lo = max(from, raw / to);
        auto hi = min(min(to - 1, raw / from), (LL)pow(raw, 0.5));
        for (LL a = lo; a <= hi; a++) {
            if (a > raw / a) {
                break;
            }
            if (raw % a == 0) {
                auto b = raw / a;
                if (b >= from && b < to) {
                    return true;
                }
            }
        }
        return false;
    }
};

int main() {
    cout << Solution().largestPalindrome(2) << endl;
    return 0;
}
