/*
 * @lc app=leetcode.cn id=13 lang=cpp
 *
 * [13] 罗马数字转整数
 */
#include<vector>

// @lc code=start
class Solution {
public:
    int romanToInt(string s) {
        string characterofRoma = "IVXLCDM";
        int result = 0;
        vector<string> position = {};
        for (;!s.empty();){
            if (s.size() == 1)
            {
                position.push_back(s);
                break;
            }
            string now = s.substr(0,2);
            if (characterofRoma.find(now[0]) < characterofRoma.find(now[1]))
            {
                position.push_back(now);
                s = s.erase(0, 2);
            }else{
                position.push_back(string(1,now[0]));
                s = s.erase(0, 1);
            }
        }
        for(const auto& pos : position){
            if (pos.size() == 2){
                if (pos == "IV")
                {
                    result += 4;
                }else if (pos == "IX")
                {
                    result += 9;
                }else if (pos == "XL")
                {
                    result += 40;
                }else if (pos == "XC")
                {
                    result += 90;
                }else if (pos == "CD")
                {
                    result += 400;
                }else if (pos == "CM")
                {
                    result += 900; 
                }
            }else{  
                if (pos == "I")
                {
                    result += 1;
                }else if (pos == "V")
                {
                    result += 5;
                }else if (pos == "X")
                {
                    result += 10;
                }else if (pos == "L")
                {
                    result += 50;
                }else if (pos == "C")
                {
                    result += 100;
                }else if (pos == "D")
                {
                    result += 500;
                }else if (pos == "M")
                {
                    result += 1000;
                }
            }
        }
        return result;
    }
};

//note : switch case 不能用string类型,只能用char类型,或者int类型,所以只能用if else来判断
// tool: string s;
// s.erase(n,m)  //删除从n开始的m个字符
// s.substr(n,m) //截取从n开始的m个字符
// vector的弹出办法是push_back,不能用append,append是string的函数

// @lc code=end

