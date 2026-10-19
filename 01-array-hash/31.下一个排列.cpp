/*
 * @lc app=leetcode.cn id=31 lang=cpp
 *
 * [31] 下一个排列
 */

// @lc code=start
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int right = nums.size();
        int last = -1;

        for (int i = nums.size() - 1; i > 0; i--) {
        
            for (int j = i - 1; j > last; j--) {
                if (nums[i] > nums[j]) {
                    last = j;
                    right = i;
                    break;
                }
            }
        }


        if (last != -1){
            int temp = nums[last];
            nums[last] = nums[right];
            nums[right] = temp;
            clean(nums, last);
        } else {
            int left = 0;
            int right_ = nums.size() - 1;

            while (right_ > left) {
                int temp = nums[right_];
                nums[right_--] = nums[left];
                nums[left++] = temp;
            }
        }
    }

    void clean(vector<int>& nums, int pos_1) {
        for (int i = pos_1 + 1; i < nums.size(); ++i) {
            int pos = i;
            for (int j = i + 1; j < nums.size(); j++) {
                if (nums[j] < nums[pos]) pos = j;
            }
            if (pos != i) {
                int temp = nums[i];
                nums[i] = nums[pos];
                nums[pos] = temp;
            }
        }
    }

};

// note : 这个中等题就温柔多了，注意拐点换完之后的后续还需要清理就行
// @lc code=end

