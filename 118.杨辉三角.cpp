/*
 * @lc app=leetcode.cn id=118 lang=cpp
 *
 * [118] 杨辉三角
 */

// @lc code=start
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> back = {};
        back.push_back({1});
        if (numRows == 1) return back;

        vector<int> newv = {};
        for (int i = 1; i < numRows; i++) {
            newv = back[i - 1];
            for (int j = i - 1; j > 0; j--) {
                newv[j] = newv[j] + newv[j - 1];
            }
            newv.push_back(1);
            back.push_back(newv);
        }
        return back;
    }
};
// @lc code=end

