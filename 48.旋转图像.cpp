/*
 * @lc app=leetcode.cn id=48 lang=cpp
 *
 * [48] 旋转图像
 */

// @lc code=start
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int times = matrix.size() / 2;
        vector<int> sufferv = {};

        for (int i = 0; i < times; i++) {
            sufferv.assign(matrix[i].begin() + i, matrix[i].begin() + (matrix.size() - i));

            for (int j = i; j < (int)matrix.size() - 1 - i; j++) {
                matrix[i][j] = matrix[matrix.size() - 1 - j][i];
            }
            for (int j = i; j < (int)matrix.size() - 1 - i; j++) {
                matrix[j + 1][i] = matrix[matrix.size() - 1 - i][j + 1];
            }
            for (int j = i; j < (int)matrix.size() - 1 - i; j++) {
                matrix[matrix.size() - 1 - i][j + 1] = matrix[matrix.size() - 2 - j][matrix.size() - 1 - i];
            }
            for (int j = i; j < (int)matrix.size() - 1 - i; j++) {
                matrix[j][matrix.size() - 1 - i] = sufferv[j - i];
            }
            
        }
    }
};
// @lc code=end

