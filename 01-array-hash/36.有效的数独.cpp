/*
 * @lc app=leetcode.cn id=36 lang=cpp
 *
 * [36] 有效的数独
 */

// @lc code=start
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        int i = 0;
        vector<char> cols[9];
        vector<char> boas[9];
        for (vector<char> a : board) {
            if (!unit(a)) return false;
            int j = 0;
            while (j < 9) {
                cols[j].push_back(a[j]);
                boas[i / 3 * 3 + j / 3 ].push_back(a[j]);
                j++;
            }
            i++;
        }

        for (vector<char> a : cols) {
            if (!unit(a)) return false;
        }
        for (vector<char> a : boas) {
            if (!unit(a)) return false;
        }

        return true;
    }

    bool unit(vector<char>& unit) {
        unordered_set<char> check = {};
        for (char s : unit) {
            if (s == '.') continue;
            auto it = check.find(s);
            if (it == check.end()) check.emplace(s);
            else return false;
        }
        return true;
    }
};
// @lc code=end

