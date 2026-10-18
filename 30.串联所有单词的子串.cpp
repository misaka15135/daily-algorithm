/*
 * @lc app=leetcode.cn id=30 lang=cpp
 *
 * [30] 串联所有单词的子串
 */

// @lc code=start
class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        int numofwords = words.size();
        int lengthofone = words[0].length();
        int leangthofall = lengthofone * words.size();
        vector<int> back = {};

        unordered_map<string, int> check = {};

        for (int i = 0; i < numofwords; i++) {
            check[words[i]]++;
        } 

        unordered_map<string, int> real = check;
        for (auto& entry : real) {
            entry.second = 0;
        }

        for (int i = 0; i + leangthofall <= (int)s.size(); ++i) {
            unordered_map<string, int> real;   // 窗口内实时计数，每个 i 重新清空
            bool ok = true;

            for (int j = 0; j < numofwords; ++j) {
                string w = s.substr(i + j * lengthofone, lengthofone);
                auto it = check.find(w);
                if (it == check.end()) { ok = false; break; }       // 词表里没有 → 不匹配
                if (++real[w] > it->second) { ok = false; break; }  // 该词用量已到上限
            }

            if (ok) back.push_back(i);
        }
        return back;

    }
};
// note : 确实困难，不知道用什么工具的话真不好做，这题提醒补充一下map和unordered_map的用法
// @lc code=end

