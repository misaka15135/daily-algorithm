/*
 * @lc app=leetcode.cn id=28 lang=cpp
 *
 * [28] 找出字符串中第一个匹配项的下标
 */

// @lc code=start
class Solution {
public:
    int strStr(string haystack, string needle) {
        if (needle.size() > haystack.size()) {
            return -1;
        }

        int hsz = haystack.size();
        int nsz = needle.size();

        for (int i = 0; i <= hsz - nsz; i++) {
            if (haystack.compare(i, nsz, needle) == 0) {
                return i;
            }
        }

        return -1;
    }
};

// note : 这道题数据结构课上其实有讲一个专门提速的算法,但当时没掌握,大概是记下每个位置已经匹配的个数来作为有用信息存储以利于下次判断,另外补一个字符串方法的用法: string a; string b; a.compare(n, m, b)
// KMP 补充: 那个算法就是 KMP. 预处理 needle 得到 next 数组, next[i] = needle[0..i] 的最长相等真前后缀长度
// (即失配后 needle 该退到哪个下标重新对齐, 主串指针 i 永不回退). 总复杂度 O(n+m), 对比上面按位 compare 的 O(n*m).
// 手写 next 时注意: 求 next 的过程和匹配过程几乎一样, 只是把 needle 和它自己匹配, 且从 j=1 开始.
// compare 用法没错: a.compare(pos, count, b) 是把 a 从 pos 起 count 个字符与 b 比较, 相等返回 0; 越界会抛 out_of_range.
// @lc code=end

