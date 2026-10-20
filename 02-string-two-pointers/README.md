# 02 · 字符串与双指针

> 对应计划：第 3–4 周（2026-11-02 ～ 2026-11-15）  
> 核心题量：36 题

## 本节目标

- 熟练处理字符串的反转、回文、分割、数字与字符转换。
- 掌握双指针的三类用法：对撞指针、快慢指针、分离双指针。
- 理解 KMP 的 `next` 数组含义，能手写字符串匹配。
- 能把「有序数组 + 目标值」问题转化为对撞双指针。

## 前置知识

### 1. C++ 字符串基础

- `string s` 可修改；`s[i]` 返回 `char`；`s.substr(pos, len)` 是 `O(len)` 拷贝。
- `s.size()` 是无符号类型，`s.size() - 1` 在空串时会下溢。
- 字符判断：`isdigit`、`isalpha`、`isalnum`、`tolower`、`toupper`（注意传 `unsigned char`）。
- 数字与字符串：`to_string(x)`、`stoi(s)`、`stoll(s)`。

### 2. 双指针的三种形态

| 形态 | 移动方式 | 典型问题 |
| --- | --- | --- |
| 对撞指针 | `l++` / `r--`，向中间靠拢 | 两数之和 II、三数之和、盛水容器、回文 |
| 快慢指针 | 同向，`fast` 先走 | 删除重复项、移除元素、链表找环 |
| 分离双指针 | 两个数组各一个指针 | 合并有序数组、区间交集 |

### 3. 回文的两种求法

- 中心扩展：枚举 `2n-1` 个中心，向两边扩展，`O(n²)`，适合求最长回文子串。
- Manacher：`O(n)`，面试中了解即可，能手写中心扩展优先。

### 4. KMP

`next[i]`（或 `pi[i]`）表示 `pattern[0..i]` 的最长相等前后缀长度。匹配失败时，模式串指针回退到 `next[j-1]`，而不是回到 0。

## 核心模板

### 对撞双指针：三数之和

```cpp
vector<vector<int>> threeSum(vector<int>& a) {
    sort(a.begin(), a.end());
    vector<vector<int>> ans;
    int n = a.size();
    for (int i = 0; i < n - 2; ++i) {
        if (i > 0 && a[i] == a[i - 1]) continue;      // 跳过重复的第一个数
        int l = i + 1, r = n - 1;
        while (l < r) {
            int s = a[i] + a[l] + a[r];
            if (s < 0) ++l;
            else if (s > 0) --r;
            else {
                ans.push_back({a[i], a[l], a[r]});
                while (l < r && a[l] == a[l + 1]) ++l; // 跳过重复的第二个数
                while (l < r && a[r] == a[r - 1]) --r; // 跳过重复的第三个数
                ++l; --r;
            }
        }
    }
    return ans;
}
```

### 中心扩展：最长回文子串

```cpp
pair<int,int> expand(const string& s, int l, int r) {
    while (l >= 0 && r < (int)s.size() && s[l] == s[r]) { --l; ++r; }
    return {l + 1, r - 1}; // 闭区间
}
// 枚举中心
for (int i = 0; i < n; ++i) {
    auto [l1, r1] = expand(s, i, i);       // 奇数长度
    auto [l2, r2] = expand(s, i, i + 1);   // 偶数长度
    // 取更长者
}
```

### KMP 前缀函数

```cpp
vector<int> prefixFunction(const string& p) {
    int m = p.size();
    vector<int> pi(m, 0);
    for (int i = 1; i < m; ++i) {
        int j = pi[i - 1];
        while (j > 0 && p[i] != p[j]) j = pi[j - 1];
        if (p[i] == p[j]) ++j;
        pi[i] = j;
    }
    return pi;
}

int strStr(string s, string p) {
    if (p.empty()) return 0;
    auto pi = prefixFunction(p);
    for (int i = 0, j = 0; i < (int)s.size(); ++i) {
        while (j > 0 && s[i] != p[j]) j = pi[j - 1];
        if (s[i] == p[j]) ++j;
        if (j == (int)p.size()) return i - j + 1;
    }
    return -1;
}
```

## 例题拆解

### 5. 最长回文子串（Medium）

- 中心扩展：每个位置作为奇数中心 `(i,i)` 和偶数中心 `(i,i+1)` 扩展。
- 复杂度：时间 `O(n²)`，空间 `O(1)`。
- 进阶：Manacher `O(n)`，但不要为了炫技牺牲正确性。

### 15. 三数之和（Medium，已完成）

- 先排序，固定第一个数，剩下两数用对撞指针。
- 三个位置都要去重；去重是这题最大的坑。
- 复杂度：时间 `O(n²)`，空间 `O(1)`（不计排序栈）。

### 28. 找出字符串中第一个匹配项的下标（Easy，已完成）

- 暴力 `O(nm)` 可以过；面试要求 `O(n+m)` 时写 KMP。
- `pi` 数组的含义是「最长相等前后缀」，不是「回退到哪个下标」，但回退时用 `pi[j-1]`。

### 42. 接雨水（Hard）

- 双指针：维护 `leftMax` 和 `rightMax`，每次移动较矮的一侧。
- 某一列的水量 = `min(leftMax, rightMax) - height[i]`。
- 复杂度：时间 `O(n)`，空间 `O(1)`。

## 常见坑点

- `while (l < r && a[l] == a[l+1])` 去重后忘了 `++l`，造成死循环或重复答案。
- 三数之和/四数之和的加法溢出 `int`。
- 翻转字符串中的单词：先整体反转再局部反转，注意多余空格。
- KMP 的 `pi` 数组下标从 0 开始，回退用 `pi[j-1]`，不要写成 `pi[j]`。
- `string::npos` 与 `-1` 混用；`find` 返回 `size_t`。
- 大小写转换传负 `char` 是未定义行为，先转 `unsigned char`。

## 题目清单

### 第 3 周 · 字符串与双指针 I：反转、回文、字符串基础（18 题）

- [5](https://leetcode.cn/problems/longest-palindromic-substring/) 最长回文子串 (M) · [6](https://leetcode.cn/problems/zigzag-conversion/) Z 字形变换 (M) · [8](https://leetcode.cn/problems/string-to-integer-atoi/) 字符串转换整数 (atoi) (M)
- [9](https://leetcode.cn/problems/palindrome-number/) 回文数 (E) · [58](https://leetcode.cn/problems/length-of-last-word/) 最后一个单词的长度 (E) · [125](https://leetcode.cn/problems/valid-palindrome/) 验证回文串 (E)
- [151](https://leetcode.cn/problems/reverse-words-in-a-string/) 反转字符串中的单词 (M) · [344](https://leetcode.cn/problems/reverse-string/) 反转字符串 (E) · [345](https://leetcode.cn/problems/reverse-vowels-of-a-string/) 反转字符串中的元音字母 (E)
- [387](https://leetcode.cn/problems/first-unique-character-in-a-string/) 字符串中的第一个唯一字符 (E) · [415](https://leetcode.cn/problems/add-strings/) 字符串相加 (E) · [443](https://leetcode.cn/problems/string-compression/) 压缩字符串 (M)
- [541](https://leetcode.cn/problems/reverse-string-ii/) 反转字符串 II (E) · [557](https://leetcode.cn/problems/reverse-words-in-a-string-iii/) 反转字符串中的单词 III (E) · [680](https://leetcode.cn/problems/valid-palindrome-ii/) 验证回文串 II (E)
- [283](https://leetcode.cn/problems/move-zeroes/) 移动零 (E) · [75](https://leetcode.cn/problems/sort-colors/) 颜色分类 (M) · [167](https://leetcode.cn/problems/two-sum-ii-input-array-is-sorted/) 两数之和 II - 输入有序数组 (M)

### 第 4 周 · 字符串与双指针 II：KMP、模拟、对撞指针（18 题）

- [42](https://leetcode.cn/problems/trapping-rain-water/) 接雨水 (H) · [43](https://leetcode.cn/problems/multiply-strings/) 字符串相乘 (M) · [68](https://leetcode.cn/problems/text-justification/) 文本左右对齐 (H)
- [71](https://leetcode.cn/problems/simplify-path/) 简化路径 (M) · [165](https://leetcode.cn/problems/compare-version-numbers/) 比较版本号 (M) · [179](https://leetcode.cn/problems/largest-number/) 最大数 (M)
- [537](https://leetcode.cn/problems/complex-number-multiplication/) 复数乘法 (M) · [392](https://leetcode.cn/problems/is-subsequence/) 判断子序列 (E) · [409](https://leetcode.cn/problems/longest-palindrome/) 最长回文串 (E)
- [451](https://leetcode.cn/problems/sort-characters-by-frequency/) 根据字符出现频率排序 (M) · [459](https://leetcode.cn/problems/repeated-substring-pattern/) 重复的子字符串 (E) · [468](https://leetcode.cn/problems/validate-ip-address/) 验证IP地址 (M)
- [481](https://leetcode.cn/problems/magical-string/) 神奇字符串 (M) · [522](https://leetcode.cn/problems/longest-uncommon-subsequence-ii/) 最长特殊序列 II (M) · [524](https://leetcode.cn/problems/longest-word-in-dictionary-through-deleting/) 通过删除字母匹配到字典里最长单词 (M)
- [539](https://leetcode.cn/problems/minimum-time-difference/) 最小时间差 (M) · [520](https://leetcode.cn/problems/detect-capital/) 检测大写字母 (E) · [551](https://leetcode.cn/problems/student-attendance-record-i/) 学生出勤记录 I (E)

## 已完成题目

- [11.盛最多水的容器.cpp](11.盛最多水的容器.cpp)
- [13.罗马数字转整数.cpp](13.罗马数字转整数.cpp)
- [14.最长公共前缀.cpp](14.最长公共前缀.cpp)
- [15.三数之和.cpp](15.三数之和.cpp)
- [16.最接近的三数之和.cpp](16.最接近的三数之和.cpp)
- [18.四数之和.cpp](18.四数之和.cpp)
- [26.删除有序数组中的重复项.cpp](26.删除有序数组中的重复项.cpp)
- [27.移除元素.cpp](27.移除元素.cpp)
- [28.找出字符串中第一个匹配项的下标.cpp](28.找出字符串中第一个匹配项的下标.cpp)
