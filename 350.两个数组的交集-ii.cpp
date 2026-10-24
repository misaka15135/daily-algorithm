/*
 * @lc app=leetcode.cn id=350 lang=cpp
 *
 * [350] 两个数组的交集 II
 */

// @lc code=start
class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> check_1 = {};
        vector<int> back = {};
        for (int x : nums1) check_1[x]++;

        for (int x : nums2) {
            auto it = check_1.find(x);
            if (it == check_1.end()) continue;
            if (it != check_1.end() && it->second == 0 ) check_1.erase(x);
            else {
                back.push_back(x);
                it->second--;
            }

        }
        return back;

    }
};

// note ： 可以先比较size让小的建立map;
// @lc code=end

