/*
 * @lc app=leetcode.cn id=15 lang=cpp
 *
 * [15] 三数之和
 */

// @lc code=start
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> theBack = {};
        if (nums.size() < 3) return theBack;

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
        int n = nums.size();
        quickSort(quickSort, 0, nums.size() - 1);
        for (int i = 0; i + 2 < n; i++) {
            if (nums[i] > 0) break;
            if (i > 0 && nums[i] == nums[i - 1]) continue;   // 跳过重复的 i
            int left = i + 1, right = n - 1;                 // 两端出发，向中间靠拢
            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];
                if (sum < 0)      left++;      // 和太小 → 需要更大的数 → 左指针右移
                else if (sum > 0) right--;     // 和太大 → 需要更小的数 → 右指针左移
                else {
                    theBack.push_back({nums[i], nums[left], nums[right]});
                    while (left < right && nums[left]  == nums[left + 1])  left++;
                    while (left < right && nums[right] == nums[right - 1]) right--;
                    left++; right--;
                }
            }
        }

        
        sort(theBack.begin(), theBack.end());
        theBack.erase(unique(theBack.begin(), theBack.end()), theBack.end());
        return theBack;
        
        
    }
};
// note : 双指针法要预排序，记一个快排
// 双指针法少了左边加，多了右边减
// @lc code=end

