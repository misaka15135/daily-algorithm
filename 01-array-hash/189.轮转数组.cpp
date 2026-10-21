/*
 * @lc app=leetcode.cn id=189 lang=cpp
 *
 * [189] 轮转数组
 */

// @lc code=start
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        while (k > nums.size()) k-= nums.size(); 
        if (nums.size() == 1 || nums.size() == k) return;
        int temp = 0;
        int j = 0;
        int z = 0;

            for (int i = nums.size() - 1; i >= nums.size() - k; i--) {
                j = i;
                temp = nums[i];
                while (j - k >= 0) {
                    nums[j] = nums[j - k];
                    j -= k;
                }
                nums[j] = temp;
                if (j == 0) z = k - nums.size() + i;
            }
        

            if (z > 0) {
                reverse(nums.begin(), nums.begin() + k);        // 前 k 个整体反转
                reverse(nums.begin(), nums.begin() + z);        // 前 z 个反转
                reverse(nums.begin() + z, nums.begin() + k);    // 剩下 k-z 个反转
            }

    }
};
//note : 可以使用reverse将vector反转
// @lc code=end

