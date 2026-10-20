/*
 * @lc app=leetcode.cn id=1 lang=cpp
 *
 * [1] 两数之和
 */
#include<vector>
#include<unordered_map>
using namespace std;

// @lc code=start
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> check;
        for (int i = 0; i < nums.size(); i++) {
            auto it = check.find(target - nums[i]);
            if (it != check.end()) return {it->second, i};
            check.emplace(nums[i], i);
        }

        return {};
    }
};
// @lc code=end

