/*
 * @lc app=leetcode.cn id=18 lang=cpp
 *
 * [18] 四数之和
 */

// @lc code=start
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        if (nums.size() < 4)
            return vector<vector<int>>({});
        sort(nums.begin(), nums.end());

        vector<vector<int>> back ={};

        int left1 = 0;

        for (; left1 < nums.size() - 3; left1++){
            for (int right1 = nums.size() - 1; right1 > left1 + 2; right1--){

                    long need = long(target) - (nums[left1] + nums[right1]);
                    int left2 = left1 + 1;
                    int right2 = right1 - 1;

                    while (left2 < right2){
                        if (need > (nums[left2] + nums[right2])){
                            left2++;
                        }else if (need < (nums[left2] + nums[right2])){
                            right2--;
                        }else{
                            back.push_back({nums[left1], nums[left2], nums[right2], nums[right1]});
                            left2++;
                            right2--;
                        }
                    }
            
            }
        }

        sort(back.begin(), back.end());
        back.erase(unique(back.begin(), back.end()), back.end());
        return back;
    }
};

// note : 没什么好说的，我还以为是15题的进阶版，结果外圈直接暴力循环就行了
// 看了前面的算法，主要提升技巧是合适的剪枝，比如如果前几个加起来就比target大了，直接break,如果加上最后几个都比target小，直接continue到下一个
// @lc code=end

