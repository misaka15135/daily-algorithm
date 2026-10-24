/*
 * @lc app=leetcode.cn id=73 lang=cpp
 *
 * [73] 矩阵置零
 */

// @lc code=start
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
    bool row0 = false, col0 = false;

    // 1. 记录第一行、第一列原本是否有 0
    for (int c = 0; c < n; c++) if (matrix[0][c] == 0) row0 = true;
    for (int r = 0; r < m; r++) if (matrix[r][0] == 0) col0 = true;

    // 2. 扫描内部，把标记写到第一行/第一列
    for (int r = 1; r < m; r++)
        for (int c = 1; c < n; c++)
            if (matrix[r][c] == 0) {
                matrix[r][0] = 0;
                matrix[0][c] = 0;
            }

    // 3. 根据标记清内部（注意都从 1 开始，别碰标记本身）
    for (int r = 1; r < m; r++)
        if (matrix[r][0] == 0)
            for (int c = 1; c < n; c++) matrix[r][c] = 0;

    for (int c = 1; c < n; c++)
        if (matrix[0][c] == 0)
            for (int r = 1; r < m; r++) matrix[r][c] = 0;

    // 4. 最后处理第一行、第一列
    if (row0) for (int c = 0; c < n; c++) matrix[0][c] = 0;
    if (col0) for (int r = 0; r < m; r++) matrix[r][0] = 0;
    }
};
// @lc code=end

