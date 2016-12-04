//------------------------------------------------------------------------------
// Solution for LeetCode Problem 3: Longest Substring Without Repeating Characters
// Developer: Yonghang Jiang(seedjyh@gmail.com)
//------------------------------------------------------------------------------

#include <stdio.h>
#include <string>
using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int result = 0;
        int last_appear[256] = {0};
        for (int i = 0; i < 256; i++)
        {
            last_appear[i] = -1; // never appeared.
        }
        
        int result_for_last_position = 0;
        for (int i = 0; i < s.size(); i++)
        {
            int result_for_here = min(result_for_last_position + 1, i - last_appear[s[i]]);
            result = max(result_for_here, result);
            last_appear[s[i]] = i; // record for later.
            result_for_last_position = result_for_here;
        }
        return result;
    }
    
    int min(int a, int b){return (a < b)?a:b;}
    int max(int a, int b){return (a > b)?a:b;}
};

int main()
{
    Solution s;
    printf("%d\n", s.lengthOfLongestSubstring(string("")));
    printf("%d\n", s.lengthOfLongestSubstring(string("abcabcbb")));
    printf("%d\n", s.lengthOfLongestSubstring(string("bbbbb")));
    printf("%d\n", s.lengthOfLongestSubstring(string("pwwkew")));
    printf("%d\n", s.lengthOfLongestSubstring(string("abba")));
    return 0;
}
