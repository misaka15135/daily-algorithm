/*
 * @lc app=leetcode.cn id=12 lang=cpp
 *
 * [12] 整数转罗马数字
 */

// @lc code=start
class Solution {
public:
    string intToRoman(int num) {
        string characterofRoma = "IVXLCDM";
        int already_have = num % 10;
        int now_position = 0;
        string result = "";
        for(; num != 0 && now_position < 4; )
        {
            if (already_have >= 5 && already_have <= 8)
            {
                result = string(1, characterofRoma[2 * now_position + 1])
       + string(already_have - 5, characterofRoma[2 * now_position])
       + result;

            }else if (already_have == 4)
            {
                result = string(1, characterofRoma[2 * now_position]) + string(1, characterofRoma[2 * now_position + 1]) + result;
            }else if (already_have == 9)
            {
                result = string(1, characterofRoma[2 * now_position]) + string(1, characterofRoma[2 * now_position + 2]) + result;
            }else
            {
                result = string(already_have, characterofRoma[2 * now_position]) + result;
            }
            num /= 10;
            now_position++;
            already_have = num % 10;
        }
        return result; 
    }
};
// @lc code=end

// note:
// string作拼接的时候不能用 int * char ,char会自动升级为int,所以要用string(n,char)来转换成string类型
