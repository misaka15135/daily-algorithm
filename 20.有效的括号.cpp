/*
 * @lc app=leetcode.cn id=20 lang=cpp
 *
 * [20] 有效的括号
 */

// @lc code=start
class Solution {
public:
    bool isValid(string s) {
        vector<char> lefts = {};

        while (!s.empty()){
            char now = s[0];
            s.erase(0, 1);
            if (now == '(' || now == '[' || now == '{'){
                lefts.push_back(now);
            }else if (now == ')' || now == ']' || now == '}'){
                if (now == ')'){
                    if (lefts.empty() || lefts.back() != '('){
                        return false;
                    }
                    lefts.pop_back();
                }else if (now == ']'){
                    if (lefts.empty() || lefts.back() != '['){
                        return false;
                    }
                    lefts.pop_back();
                }else {
                    if (lefts.empty() || lefts.back() != '{'){
                        return false;
                    }
                    lefts.pop_back();
                }
            }
        }
        if (!lefts.empty())
            return false;
        
        return true;
    }
};

// note : 使用vector时注意不要在空vector上pop_back()，string使用erase如果不用重新赋值到另一个地方直接对自身使用就行，不用在前面写 xx =；
// @lc code=end

