/*
 * @lc app=leetcode.cn id=16 lang=cpp
 *
 * [16] 最接近的三数之和
 */

// @lc code=start
class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int final = 1000000;
        if (nums.size() < 3) return final;

        // Quick sort nums in ascending order without using sort().
        auto quickSort = [&](auto&& self, int left, int right) -> void {
            if (left >= right) return;

            int pivot = nums[(left + right) / 2];
            int i = left;
            int j = right;

            while (i <= j) {
                while (nums[i] < pivot) ++i;
                while (nums[j] > pivot) --j;

                if (i <= j) {
                    swap(nums[i], nums[j]);
                    ++i;
                    --j;
                }
            }

            self(self, left, j);
            self(self, i, right);
        };
        int now_absolute = final;
        int n = nums.size();
        quickSort(quickSort, 0, nums.size() - 1);
        for (int i = 0; i + 2 < n; i++) {
            if (i > 0 && nums[i] == nums[i - 1]) continue;   // 跳过重复的 i
            int left = i + 1, right = n - 1;                 // 两端出发，向中间靠拢
            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];
                if (sum < target){
                    if (target - sum < now_absolute){
                        final = sum;
                        now_absolute = target - sum;
                    }
                    left++;
                }
                else if (sum > target) {
                    if (sum - target < now_absolute){
                        final = sum;
                        now_absolute = sum - target;
                    }
                    right--;
                }
                else {
                    return target;
                }
            }
        }      
        return final;
    }
};

//note: 上一题简单改一下就行了
// @lc code=end

