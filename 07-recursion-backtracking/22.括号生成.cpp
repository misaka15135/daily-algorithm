/*
 * @lc app=leetcode.cn id=22 lang=cpp
 *
 * [22] 括号生成
 */

// @lc code=start
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> back ={};
        if (n == 1) {
            back.push_back("()");
            return back;
        }
        back = generateParenthesis(n - 1);
        
        int times = back.size();
        for (int i = 0; i < times; i++) {
            string now = back[0];
            back.erase(back.begin());
            back.push_back("(" + now + ")");
        }

        for (int i = 1; i < n; i++) {
            vector<string> temp1 = generateParenthesis(i);
            vector<string> temp2 = generateParenthesis(n - i);
            int temp1_size = temp1.size();
            int temp2_size = temp2.size();

            for (int i = 0; i < temp1_size; i++) {
                string now = temp1[0];
                temp1.erase(temp1.begin());
                for (int i = 0; i < temp2_size; i++) {
                    back.push_back(now + temp2[i]);
                }
            }
            
        }

        sort(back.begin(), back.end());
        back.erase(unique(back.begin(), back.end()), back.end());

        return back;
    }
};

// note : 对vector使用erase方法清除第一项的时候，采用.erase(vector_name.begin()),而不是.erase(0,1)
// @lc code=end

