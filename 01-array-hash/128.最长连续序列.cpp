/*
 * @lc app=leetcode.cn id=128 lang=cpp
 *
 * [128] 最长连续序列
 */

// @lc code=start
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> check = {nums.begin(), nums.end()};

        int best = 0;

        for (int num : check) {
            if (check.count(num - 1)) continue;

            int y = num;
            while(check.count(++y));

            best = max(best, (y - num));

        }
        return best;

    }
};
// @lc code=end

