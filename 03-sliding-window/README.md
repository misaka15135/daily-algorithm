# 03 · 滑动窗口

> 对应计划：第 5 周（2026-11-16 ～ 2026-11-22）  
> 核心题量：18 题

## 本节目标

- 区分定长窗口与不定长窗口，能写出稳定的窗口模板。
- 理解「什么时候扩大右边界、什么时候收缩左边界」。
- 掌握用哈希表维护窗口内计数。
- 掌握单调队列求窗口最大值/最小值。

## 前置知识

### 1. 窗口的两种类型

| 类型 | 特点 | 典型题 |
| --- | --- | --- |
| 定长窗口 | 窗口长度固定为 k | 438、567、643 |
| 不定长窗口 | 满足条件时收缩左边界 | 3、76、209、1004 |

### 2. 不定长窗口的通用结构

```text
for right in 0..n-1:
    加入 a[right]
    while 窗口不满足条件:
        移除 a[left]
        left++
    用当前窗口更新答案
```

关键：`while` 而不是 `if`，因为左边界可能需要连续收缩多次。

### 3. 适用条件

- 窗口扩大/缩小后，条件具有单调性：例如「字符种数」「和」「不同整数个数」。
- 如果数组含负数且要求「和恰好为 K」，窗口不单调，应改用前缀和 + 哈希。

### 4. 单调队列

用于维护窗口内的最大值/最小值。队列中存下标，保证对应值单调递减（最大值）或递增（最小值）。每次右移时：

1. 弹出队尾所有不再可能成为最值的元素；
2. 加入当前下标；
3. 弹出队首已滑出窗口的下标。

## 核心模板

### 不定长窗口：最小覆盖子串

```cpp
string minWindow(string s, string t) {
    unordered_map<char, int> need, window;
    for (char c : t) ++need[c];
    int valid = 0, left = 0;
    int start = 0, len = INT_MAX;
    for (int right = 0; right < (int)s.size(); ++right) {
        char c = s[right];
        if (need.count(c)) {
            ++window[c];
            if (window[c] == need[c]) ++valid;
        }
        while (valid == (int)need.size()) {
            if (right - left + 1 < len) {
                start = left;
                len = right - left + 1;
            }
            char d = s[left++];
            if (need.count(d)) {
                if (window[d] == need[d]) --valid;
                --window[d];
            }
        }
    }
    return len == INT_MAX ? "" : s.substr(start, len);
}
```

### 定长窗口：找到所有字母异位词

```cpp
vector<int> findAnagrams(string s, string p) {
    vector<int> ans;
    int n = s.size(), m = p.size();
    if (n < m) return ans;
    array<int, 26> need{}, win{};
    for (char c : p) ++need[c - 'a'];
    for (int i = 0; i < m; ++i) ++win[s[i] - 'a'];
    if (win == need) ans.push_back(0);
    for (int i = m; i < n; ++i) {
        ++win[s[i] - 'a'];
        --win[s[i - m] - 'a'];
        if (win == need) ans.push_back(i - m + 1);
    }
    return ans;
}
```

### 单调队列：滑动窗口最大值

```cpp
vector<int> maxSlidingWindow(vector<int>& a, int k) {
    deque<int> q; // 存下标，值单调递减
    vector<int> ans;
    for (int i = 0; i < (int)a.size(); ++i) {
        while (!q.empty() && a[q.back()] <= a[i]) q.pop_back();
        q.push_back(i);
        if (q.front() <= i - k) q.pop_front();
        if (i >= k - 1) ans.push_back(a[q.front()]);
    }
    return ans;
}
```

## 例题拆解

### 3. 无重复字符的最长子串（Medium）

- 用 `last[c]` 记录字符上一次出现的位置，左边界直接跳到 `max(left, last[c]+1)`。
- 复杂度：时间 `O(n)`，空间 `O(字符集)`。

### 76. 最小覆盖子串（Hard）

- `need` 记录目标计数，`valid` 记录已经满足的字符种数。
- 当 `valid == need.size()` 时，窗口可行，尝试收缩左边界并更新答案。
- 复杂度：时间 `O(n)`，空间 `O(字符集)`。

### 239. 滑动窗口最大值（Hard）

- 单调队列存下标，队首是当前窗口最大值。
- 注意先弹出窗口外的队首，再取答案。
- 复杂度：时间 `O(n)`，空间 `O(k)`。

### 209. 长度最小的子数组（Medium）

- 正数数组，窗口和随右边界单调增加，可以用滑动窗口。
- 如果含负数，则不能滑窗，改用前缀和 + 二分或哈希。

## 常见坑点

- 收缩条件写成 `if`，导致窗口仍然不合法。
- 更新答案的时机错误：有的题在扩张后更新，有的在收缩到合法后更新。
- 定长窗口先加右边再减左边，顺序不能反。
- 单调队列中存值而不是下标，无法判断元素是否滑出窗口。
- `valid` 的增减条件写反：只有「恰好等于」时才改变 `valid`。
- 字符集大小不确定时，用 `unordered_map` 而不是固定数组。

## 题目清单

### 第 5 周 · 滑动窗口：定长、不定长、单调队列（18 题）

- [3](https://leetcode.cn/problems/longest-substring-without-repeating-characters/) 无重复字符的最长子串 (M) · [76](https://leetcode.cn/problems/minimum-window-substring/) 最小覆盖子串 (H) · [239](https://leetcode.cn/problems/sliding-window-maximum/) 滑动窗口最大值 (H)
- [209](https://leetcode.cn/problems/minimum-size-subarray-sum/) 长度最小的子数组 (M) · [438](https://leetcode.cn/problems/find-all-anagrams-in-a-string/) 找到字符串中所有字母异位词 (M) · [567](https://leetcode.cn/problems/permutation-in-string/) 字符串的排列 (M)
- [219](https://leetcode.cn/problems/contains-duplicate-ii/) 存在重复元素 II (E) · [220](https://leetcode.cn/problems/contains-duplicate-iii/) 存在重复元素 III (H) · [424](https://leetcode.cn/problems/longest-repeating-character-replacement/) 替换后的最长重复字符 (M)
- [1004](https://leetcode.cn/problems/max-consecutive-ones-iii/) 最大连续1的个数 III (M) · [713](https://leetcode.cn/problems/subarray-product-less-than-k/) 乘积小于 K 的子数组 (M) · [862](https://leetcode.cn/problems/shortest-subarray-with-sum-at-least-k/) 和至少为 K 的最短子数组 (H)
- [187](https://leetcode.cn/problems/repeated-dna-sequences/) 重复的DNA序列 (M) · [395](https://leetcode.cn/problems/longest-substring-with-at-least-k-repeating-characters/) 至少有 K 个重复字符的最长子串 (M) · [480](https://leetcode.cn/problems/sliding-window-median/) 滑动窗口中位数 (H)
- [904](https://leetcode.cn/problems/fruit-into-baskets/) 水果成篮 (M) · [643](https://leetcode.cn/problems/maximum-average-subarray-i/) 子数组最大平均数 I (E) · [1423](https://leetcode.cn/problems/maximum-points-you-can-obtain-from-cards/) 可获得的最大点数 (M)

## 已完成题目

- [30.串联所有单词的子串.cpp](30.串联所有单词的子串.cpp)
