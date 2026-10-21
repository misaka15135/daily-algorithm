/*
 * @lc app=leetcode.cn id=349 lang=cpp
 *
 * [349] 两个数组的交集
 */

// @lc code=start
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        vector<int> back ={};

        unordered_set<int> check1(nums1.begin(), nums1.end());
        unordered_set<int> check2(nums2.begin(), nums2.end());

        for (int i : check1) {
            if (check2.count(i)) back.push_back(i);
        }

        return back;
    }
};
// @lc code=end

