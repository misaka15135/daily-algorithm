/*
 * @lc app=leetcode.cn id=49 lang=cpp
 *
 * [49] 字母异位词分组
 */

// @lc code=start
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<int>> check;

        for (int i = 0; i < (int)strs.size(); i++) {
            string temp = strs[i];
            sort(temp.begin(), temp.end());
            check[temp].push_back(i);
        }

        vector<vector<string>> ans;
        for (auto& kv : check) {
            vector<string> group;
            for (int i : kv.second) group.push_back(strs[i]);
            ans.push_back(group);
        }
        return ans;
    }
};
// @lc code=end

