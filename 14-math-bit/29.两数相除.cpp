/*
 * @lc app=leetcode.cn id=29 lang=cpp
 *
 * [29] 两数相除
 */

// @lc code=start
class Solution {
public:
    int divide(int dividend, int divisor) {
        if (dividend == 0) {
            return 0;
        }
        bool same = ((dividend < 0) && (divisor > 0)) || ((dividend > 0) && (divisor < 0));
        if (divisor == 1) {
            return dividend;

        }
        if (divisor == -1) {
            return dividend == INT_MIN ? INT_MAX : -dividend;
        }

        long abs_de_L = long(0); 
        long abs_ds_L = long(0); 

        bool big = 0;

        int abs_de = 0;
        int abs_ds = 0;

        if (dividend == INT_MIN) {
            abs_de_L = long(2147483648);
            big = 1;
        }else {
            abs_de = long(dividend < 0 ? -dividend : dividend);
        }

        if (divisor == INT_MIN) {
            abs_ds_L = long(2147483648);
            big = 1;
        }else {
            abs_ds = long(divisor < 0 ? -divisor : divisor);
        }
        
        int i = 0;
        long max = 2147483647;

        if (abs_de_L == long(0) && abs_ds_L == long(0)) {
            while (abs_de >= abs_ds && i < max) {
                abs_de -= abs_ds;
                i++;
            }
        }  else {
            if (abs_de_L == long(0)) abs_de_L = long(abs_de);
            if (abs_ds_L == long(0)) abs_ds_L = long(abs_ds);
            while (abs_de_L >= abs_ds_L && i < max) {
                abs_de_L -= abs_ds_L;
                i++;
            }
        } 

        if (same) {
            if (big){
                if (abs_de_L >= abs_ds_L) return INT_MIN;
                return -i;
            }
            if (abs_de >= abs_ds) return INT_MIN;
            return -i;
        }

        return i;
        
    }
};

// note : 太恶心了这道题，太多情况要考虑了
// @lc code=end

