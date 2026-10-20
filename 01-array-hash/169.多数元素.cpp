/*
 * @lc app=leetcode.cn id=169 lang=cpp
 *
 * [169] 多数元素
 */

// @lc code=start
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int n = nums.size();
        if (n == 1 || n == 2) return nums[0];
        int target = n / 2;

        unordered_map<int, int> check = {};
        for (int num : nums) {
            auto it = check.find(num);
            if (it == check.end()) check.emplace(num, 1);
            else {
                if (++it->second > target) return num;
            }
        }
        return -1;
    }
};
// @lc code=end

