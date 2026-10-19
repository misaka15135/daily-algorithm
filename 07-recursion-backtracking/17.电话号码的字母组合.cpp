/*
 * @lc app=leetcode.cn id=17 lang=cpp
 *
 * [17] 电话号码的字母组合
 */

// @lc code=start
class Solution {
public:
    vector<string> letterCombinations(string digits) {
        static const string number2char[] = {
            "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"
        };

        vector<string> back = {""};

        for (; !digits.empty(); ){
            char now = digits[0];
            digits = digits.erase(0, 1);
            
            int times = back.size();
            for (int time = 0; time < times; time++){
                string temp = back[0];
                back.erase(back.begin());
                for (int time_2 = 0; time_2 < number2char[now - '0'].length(); time_2++){
                    back.push_back(temp + number2char[now- '0'].substr(time_2, 1));
                }
            }
            
        }
        return back;
    }
};

// note ： 当用不来c++中的enum时转用string[],vector的pop_back()只会弹出末尾元素，可以在vector和string中使用erase(n,m)删除第n到m的元素，vector要用指针begin() + n
// @lc code=end

