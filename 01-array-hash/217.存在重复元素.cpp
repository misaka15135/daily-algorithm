/*
 * @lc app=leetcode.cn id=217 lang=cpp
 *
 * [217] 存在重复元素
 */

// @lc code=start
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_map<int, int> check;
        
        for (int i = 0; i < nums.size(); i++) {
            if (check.find(nums[i]) == check.end()) check.emplace(nums[i], 0);
            else return true;
        }

        return false;
    }
};
// @lc code=end

