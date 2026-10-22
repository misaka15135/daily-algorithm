/*
 * @lc app=leetcode.cn id=54 lang=cpp
 *
 * [54] 螺旋矩阵
 */

// @lc code=start
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int left = 0;
        int up = 0;
        int right = matrix[0].size() - 1;
        int down = matrix.size() - 1;

        int shor = right <= down ? right + 1 : down + 1; 
        int min = (right <= down ? right + 1 : down + 1) / 2;
        bool inner = right == down && right % 2 == 0;

        vector<int> back = {};

        while (min-- > 0) {
            toRight(back, matrix, left, up, right, down);
            toDown(back, matrix, left, up, right, down);
            toLeft(back, matrix, left, up, right, down);
            toUp(back, matrix, left, up, right, down);
        }

        if (shor % 2 != 0) {
            if (right > down) toRight(back, matrix, left, up, right, down);
            else if (right < down) toDown(back, matrix, left, up, right, down);
            else if (inner) back.push_back(matrix[matrix.size() / 2][matrix[0].size() / 2]);
        }

        return back;
    }

    void toRight(vector<int>& have, vector<vector<int>>& matrix, int& left, int& up, int& right, int& down) {
        for (int i = left; i <= right; i++) {
            have.push_back(matrix[up][i]);
        }
        up++;
    }
    void toDown(vector<int>& have, vector<vector<int>>& matrix, int& left, int& up, int& right, int& down) {
        for (int i = up; i <= down; i++) {
            have.push_back(matrix[i][right]);
        }
        right--;
    }
    void toLeft(vector<int>& have, vector<vector<int>>& matrix, int& left, int& up, int& right, int& down) {
        for (int i = right; i >= left; i--) {
            have.push_back(matrix[down][i]);
        }
        down--;
    }
    void toUp(vector<int>& have, vector<vector<int>>& matrix, int& left, int& up, int& right, int& down) {
        for (int i = down; i >= up; i--) {
            have.push_back(matrix[i][left]);
        }
        left++;
    }
};
// @lc code=end

