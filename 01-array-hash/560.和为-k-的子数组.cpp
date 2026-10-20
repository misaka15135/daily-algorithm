/*
 * @lc app=leetcode.cn id=560 lang=cpp
 *
 * [560] 和为 K 的子数组
 */

// @lc code=start
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
    unordered_map<int, int> cnt;
    cnt[0] = 1;              // 空前缀
    int pre = 0, ans = 0;

    for (int x : nums) {
        pre += x;
        if (cnt.count(pre - k)) ans += cnt[pre - k];
        cnt[pre]++;          // 当前前缀和加入表
    }
    return ans;
    }
};
// @lc code=end

