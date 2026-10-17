/*
 * @lc app=leetcode.cn id=26 lang=cpp
 *
 * [26] 删除有序数组中的重复项
 */

// @lc code=start
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.size() == 0) {
            return 0;
        }

        int all = nums.size();
        int now_position = 0;
        int now_val = nums[0];

        for (int i = 1; i < all; i++) {
            if (nums[i] != now_val) {
                now_val = nums[i];
                now_position++;
                nums[now_position] = now_val;
            }
        }
        return now_position + 1;
    }
};

// note : 太简单了,都不知道写什么
// @lc code=end

