/*
 * @lc app=leetcode.cn id=448 lang=cpp
 *
 * [448] 找到所有数组中消失的数字
 */

// @lc code=start
class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        int n = nums.size();

        // 把 nums[i] 对应的下标 nums[i]-1 标记成负数
        for (int i = 0; i < n; i++) {
            int idx = abs(nums[i]) - 1;
            if (nums[idx] > 0) nums[idx] = -nums[idx];
        }

        // 仍然是正数的下标 i，说明数字 i+1 没出现过
        vector<int> back;
        for (int i = 0; i < n; i++) {
            if (nums[i] > 0) back.push_back(i + 1);
        }
        return back;
    }
};

// note : 这用下标作布尔表谁能想到，牛了
// @lc code=end

