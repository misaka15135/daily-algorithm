/*
 * @lc app=leetcode.cn id=73 lang=cpp
 *
 * [73] 矩阵置零
 */

// @lc code=start
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();

        unordered_set<int> zeroRows, zeroCols;

        for (int r = 0; r < m; r++) {
            for (int c = 0; c < n; c++) {
                if (matrix[r][c] == 0) {
                    zeroRows.insert(r);
                    zeroCols.insert(c);
                }
            }
        }

        for (int r : zeroRows) {
            for (int c = 0; c < n; c++) matrix[r][c] = 0;
        }

        for (int c : zeroCols) {
            for (int r = 0; r < m; r++) matrix[r][c] = 0;
        }
    }
};
// @lc code=end

