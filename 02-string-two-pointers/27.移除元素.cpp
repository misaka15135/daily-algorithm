/*
 * @lc app=leetcode.cn id=27 lang=cpp
 *
 * [27] 移除元素
 */

// @lc code=start
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        if (nums.size() == 0) {
            return 0;
        }

        int all = nums.size();
        int now_position = 0;

        for (int i = 0; i < all; i++) {
            if (nums[i] != val) {
                nums[now_position] = nums[i];
                now_position++;
            }
        }
        return now_position;
    }
};

// note : 这是题啊
// @lc code=end

