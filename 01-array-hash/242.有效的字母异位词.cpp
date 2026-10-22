/*
 * @lc app=leetcode.cn id=242 lang=cpp
 *
 * [242] 有效的字母异位词
 */

// @lc code=start
class Solution {
public:
    bool isAnagram(string s, string t) {

        if (s.length() != t.length()) return false;

        unordered_map<char, int> check = {};

        for (int i = 0; i < s.size(); i++) {
            auto it = check.find(s[i]);
            if (it == check.end()) check.emplace(s[i], 1);
            else it->second++;
        }

        unordered_map<char, int> now = {};
        for (auto it : check) {
            now.emplace(it.first, 0);
        }

        bool isright = true;

        for (char t_ : t) {
            auto it1 = now.find(t_);
            auto it2 = check.find(t_);
            if (it1 == now.end() || it1->second == it2->second) {
                isright = false;
                break;
            }
            it1->second++;
        }
        
        return isright;
    }
};

// note : 用 for (a : b) 遍历出来的a直接就是对象本身而不是指针，用其中的元素直接用.
// @lc code=end

