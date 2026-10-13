// @before-stub-for-debug-begin
#include <vector>
#include <string>
using namespace std;
// @before-stub-for-debug-end

/*
 * @lc app=leetcode.cn id=14 lang=cpp
 *
 * [14] 最长公共前缀
 */

// @lc code=start
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        int min_length = 201;
        for (int i = 0; i < strs.size(); i++){
            if (strs[i].length() < min_length)
                min_length = strs[i].length();
        }

        if (min_length == 0)
            return "";

        bool is_this = true;

        string that_value = "";

        for (int i = 1; i <= min_length; i++){
            string now_have = strs[0].substr(0,i);
            for (int i = 0; i < strs.size(); i++){
                if (strs[i].find(now_have) != 0){
                    is_this = false;
                    break;
                }
            }
            if (is_this){
                that_value = now_have;
            }else{
                break;
            }
        }
        return that_value;
    }
};
// note : 第23行的判断条件==写成=了找了半天，可恶
// @lc code=end

