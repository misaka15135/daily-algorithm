// @before-stub-for-debug-begin
#include <vector>
#include <string>
#include "commoncppproblem10.h"

using namespace std;
// @before-stub-for-debug-end

/*
 * @lc app=leetcode.cn id=10 lang=cpp
 *
 * [10] 正则表达式匹配
 */

// @lc code=start
class Solution {
public:
    bool isMatch(string s, string p) {
        char last_s = s.empty() ? '\0' : s.back();
        char last_p = p.empty() ? '\0' : p.back();

        if (p.empty()) {
            return s.empty();
        }
        if (last_p == '*') {
            if (p.size() < 2) {
                return false;
            }
            for (int i = 0; i <= s.size(); i++)
            {
                string try_p = p.substr(0, p.size() - 2) + string(i, p[p.size() - 2]);
                bool match = false;
                match = isMatch(s, try_p);
                if (match) {
                    return true;
                }
            };
        }
        if (!s.empty() && (last_s == last_p || last_p == '.'))
        {       
            return isMatch(s.substr(0, s.size() - 1), p.substr(0, p.size() - 1));
        }
        return false;
    };
};
// @lc code=end

