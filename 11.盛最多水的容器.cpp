/*
 * @lc app=leetcode.cn id=11 lang=cpp
 *
 * [11] 盛最多水的容器
 */

// @lc code=start
class Solution {
public:
    int maxArea(vector<int>& height) {
        int max_area = 0;

        int left_height = height[0];
        for (int left = 0; left <= height.size() -2; left++)
        {
            if (height[left] < left_height)
                continue;
            left_height = height[left];
            int higher = height[height.size() - 1];
            int theShort = height[left] <= height[height.size() - 1] ? height[left] : height[height.size() - 1];
            max_area = theShort * (height.size() - 1 - left) >= max_area ? theShort * (height.size() - 1 - left) : max_area;

            for(int right = height.size() - 1; right > left; right--){
                if (height[right] <= higher)
                    continue;
                higher = height[right];
                if (higher >= height[left]){
                    max_area = (right - left) * height[left] >= max_area ? (right - left) * height[left] : max_area;
                    break;
                }
                else{
                    int area_now = (right -left) * higher;
                    max_area = max_area >= area_now ? max_area : area_now;
                }
            }
        }
        return max_area;
    }

};
// @lc code=end

