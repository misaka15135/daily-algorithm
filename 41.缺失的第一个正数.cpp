/*
 * @lc app=leetcode.cn id=41 lang=cpp
 *
 * [41] 缺失的第一个正数
 */

// @lc code=start
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int min = INT_MAX;
        int size = nums.size();
        for (int x : nums) {
            if (x > 0 && x < min) min = x;
            if (min == 1) break;
        }

        if (min != 1) return 1;

        int temp = -1;
        int next = -1;

        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] > 0) {
                temp = nums[i];
                while (temp > 0 && temp <= size && nums[temp - 1] != temp) {
                    next = nums[temp - 1];
                    nums[temp - 1] = temp;
                    temp = next;
                }
            }
        }

        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != i + 1) return (i + 1);
        }
        return (nums.size() + 1);
    }

};
// @lc code=end

