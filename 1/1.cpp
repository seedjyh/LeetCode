//------------------------------------------------------------------------------
// Solution for LeetCode Problem 1: Two Sum
// Developer: Yonghang Jiang(seedjyh@gmail.com)
//------------------------------------------------------------------------------

// #include <stdio.h>
// #include <vector>
// #include <map>
// using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> result;
        map<int, int> nums_locations;
        for (int i = 0; i < nums.size(); i++)
        {
            map<int, int>::const_iterator ite = nums_locations.find(target - nums[i]);
            if (ite != nums_locations.end())
            {
                result.push_back(ite->second);
                result.push_back(i);
                break;
            }
            nums_locations[nums[i]] = i;
        }
        return result;
    }
};

// int main()
// {
//     vector<int> input;
//     input.push_back(3);
//     input.push_back(2);
//     input.push_back(4);
//     Solution s;
//     vector<int> result = s.twoSum(input, 6);
//     printf("ans: %d\n", result.size());
//     for (int i = 0; i < result.size(); i++)
//     {
//         printf("[%d]\n", result[i]);
//     }
//     return 0;
// }
