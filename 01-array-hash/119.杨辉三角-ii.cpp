/*
 * @lc app=leetcode.cn id=119 lang=cpp
 *
 * [119] 杨辉三角 II
 */

// @lc code=start
class Solution {
public:
    vector<int> getRow(int rowIndex) {
        vector<int> back = {};
        if (rowIndex == 0) {
            back.push_back({1});
        }

        if (rowIndex >= 1) {
            back.push_back({1});
            back.push_back({1});
        } 
        if (rowIndex > 1) {
            for (int i = 2; i <= rowIndex; i++){
                for (int i = back.size() - 1; i > 0; i--) {
                    back[i] += back[i - 1];
                }
                back.push_back({1});
            }
            
        }

        return back;

    }
};
// @lc code=end

