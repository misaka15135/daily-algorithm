# 01 · 数组与哈希

> 对应计划：第 1–2 周（2026-10-19 ～ 2026-11-01）  
> 核心题量：36 题

## 本节目标

- 熟练掌握数组的线性遍历、原地修改、区间统计。
- 能把「查找/计数/去重」问题转化为哈希表操作。
- 掌握前缀和、差分数组、二维前缀和三种区间工具。
- 能正确处理矩阵的边界、旋转、螺旋遍历。

## 前置知识

### 1. 数组的物理特性

- 数组在内存中连续存放，支持 `O(1)` 随机访问，但插入/删除中间元素是 `O(n)`。
- `vector<int> a(n)` 默认初始化为 0；`vector<int> a(n, -1)` 指定初值。
- `a.size()` 返回 `size_t`（无符号），做减法前先确认不会下溢。

### 2. 哈希表

- `unordered_map<int,int>`：键值映射，均摊 `O(1)` 插入/查询。
- `unordered_set<int>`：只关心存在性。
- 需要有序遍历时用 `map` / `set`，代价是 `O(log n)`。
- 自定义键（如 `pair`、`vector`）需要提供哈希函数，或编码成整数/字符串。

### 3. 前缀和

一维：

```text
pre[0] = 0
pre[i+1] = pre[i] + a[i]
sum(l..r) = pre[r+1] - pre[l]
```

二维：

```text
S[i+1][j+1] = S[i][j+1] + S[i+1][j] - S[i][j] + a[i][j]
矩形 (r1,c1)-(r2,c2) = S[r2+1][c2+1] - S[r1][c2+1] - S[r2+1][c1] + S[r1][c1]
```

### 4. 差分数组

用于「区间加、最后统一查询」：

```text
diff[l] += v; diff[r+1] -= v;
前缀和还原：a[i] = a[i-1] + diff[i]
```

### 5. 矩阵遍历

- 螺旋遍历：维护 `top / bottom / left / right` 四个边界，每走完一条边就收缩。
- 旋转 90°：先转置再左右翻转（顺时针），或先上下翻转再转置（逆时针）。
- 矩阵置零：用第一行/第一列做标记，避免额外 `O(mn)` 空间。

## 核心模板

### 前缀和 + 哈希：统计和为 K 的子数组

```cpp
int subarraySum(vector<int>& nums, int k) {
    unordered_map<int, int> cnt{{0, 1}}; // 空前缀出现 1 次
    int pre = 0, ans = 0;
    for (int x : nums) {
        pre += x;
        if (cnt.count(pre - k)) ans += cnt[pre - k];
        ++cnt[pre];
    }
    return ans;
}
```

### 原地哈希：把值 x 放到下标 x-1

```cpp
// 适用于 1..n 的排列/缺失数字问题
for (int i = 0; i < n; ++i)
    while (nums[i] >= 1 && nums[i] <= n && nums[nums[i] - 1] != nums[i])
        swap(nums[i], nums[nums[i] - 1]);
```

### 螺旋矩阵

```cpp
vector<int> spiralOrder(vector<vector<int>>& a) {
    vector<int> ans;
    if (a.empty()) return ans;
    int top = 0, bottom = a.size() - 1;
    int left = 0, right = a[0].size() - 1;
    while (top <= bottom && left <= right) {
        for (int j = left; j <= right; ++j) ans.push_back(a[top][j]);
        ++top;
        for (int i = top; i <= bottom; ++i) ans.push_back(a[i][right]);
        --right;
        if (top <= bottom)
            for (int j = right; j >= left; --j) ans.push_back(a[bottom][j]);
        --bottom;
        if (left <= right)
            for (int i = bottom; i >= top; --i) ans.push_back(a[i][left]);
        ++left;
    }
    return ans;
}
```

## 例题拆解

### 1. 两数之和（Easy）

- 思路：边遍历边把 `nums[i] -> i` 存入哈希表；对当前 `x` 查 `target - x` 是否出现过。
- 关键：先查再存，避免同一个元素用两次。
- 复杂度：时间 `O(n)`，空间 `O(n)`。

### 560. 和为 K 的子数组（Medium）

- 思路：子数组和 `sum(l..r) = pre[r] - pre[l-1]`，转化为「当前前缀和减去 K 是否作为历史前缀和出现过」。
- 关键：`cnt[0] = 1`，表示空前缀；前缀和可能为负，不能用双指针。
- 复杂度：时间 `O(n)`，空间 `O(n)`。

### 41. 缺失的第一个正数（Hard）

- 思路：答案一定在 `[1, n+1]`。把每个在范围内的数 `x` 交换到下标 `x-1`，最后扫描第一个 `nums[i] != i+1`。
- 关键：`while` 而不是 `if`，因为一次交换后新换来的数可能还需要归位；重复值要跳过。
- 复杂度：时间 `O(n)`（每个数最多归位一次），空间 `O(1)`。

### 48. 旋转图像（Medium）

- 顺时针 90°：先沿主对角线转置，再左右翻转每一行。
- 逆时针 90°：先上下翻转，再转置。
- 复杂度：时间 `O(n²)`，空间 `O(1)`。

## 常见坑点

- 哈希表计数时忘记初始化 `{0: 1}`，导致从下标 0 开始的子数组漏算。
- 前缀和可能溢出 `int`，必要时用 `long long`。
- 有负数时「和为 K 的子数组」不能用滑动窗口。
- 矩阵螺旋遍历在 `top > bottom` 或 `left > right` 后仍继续遍历，导致重复。
- 原地哈希交换时没有跳过重复值，造成死循环。
- `vector.size()` 与 `int` 混用产生无符号下溢。

## 题目清单

### 第 1 周 · 数组与哈希 I：遍历、哈希映射、矩阵基础（18 题）

- [1](https://leetcode.cn/problems/two-sum/) 两数之和 (E) · [49](https://leetcode.cn/problems/group-anagrams/) 字母异位词分组 (M) · [128](https://leetcode.cn/problems/longest-consecutive-sequence/) 最长连续序列 (M)
- [169](https://leetcode.cn/problems/majority-element/) 多数元素 (E) · [217](https://leetcode.cn/problems/contains-duplicate/) 存在重复元素 (E) · [242](https://leetcode.cn/problems/valid-anagram/) 有效的字母异位词 (E)
- [349](https://leetcode.cn/problems/intersection-of-two-arrays/) 两个数组的交集 (E) · [350](https://leetcode.cn/problems/intersection-of-two-arrays-ii/) 两个数组的交集 II (E) · [560](https://leetcode.cn/problems/subarray-sum-equals-k/) 和为 K 的子数组 (M)
- [41](https://leetcode.cn/problems/first-missing-positive/) 缺失的第一个正数 (H) · [36](https://leetcode.cn/problems/valid-sudoku/) 有效的数独 (M) · [54](https://leetcode.cn/problems/spiral-matrix/) 螺旋矩阵 (M)
- [48](https://leetcode.cn/problems/rotate-image/) 旋转图像 (M) · [189](https://leetcode.cn/problems/rotate-array/) 轮转数组 (M) · [73](https://leetcode.cn/problems/set-matrix-zeroes/) 矩阵置零 (M)
- [118](https://leetcode.cn/problems/pascals-triangle/) 杨辉三角 (E) · [119](https://leetcode.cn/problems/pascals-triangle-ii/) 杨辉三角 II (E) · [448](https://leetcode.cn/problems/find-all-numbers-disappeared-in-an-array/) 找到所有数组中消失的数字 (E)

### 第 2 周 · 数组与哈希 II：前缀和、区间、原地修改（18 题）

- [53](https://leetcode.cn/problems/maximum-subarray/) 最大子数组和 (M) · [56](https://leetcode.cn/problems/merge-intervals/) 合并区间 (M) · [57](https://leetcode.cn/problems/insert-interval/) 插入区间 (M)
- [228](https://leetcode.cn/problems/summary-ranges/) 汇总区间 (E) · [238](https://leetcode.cn/problems/product-of-array-except-self/) 除了自身以外数组的乘积 (M) · [334](https://leetcode.cn/problems/increasing-triplet-subsequence/) 递增的三元子序列 (M)
- [274](https://leetcode.cn/problems/h-index/) H 指数 (M) · [289](https://leetcode.cn/problems/game-of-life/) 生命游戏 (M) · [303](https://leetcode.cn/problems/range-sum-query-immutable/) 区域和检索 - 数组不可变 (E)
- [304](https://leetcode.cn/problems/range-sum-query-2d-immutable/) 二维区域和检索 - 矩阵不可变 (M) · [724](https://leetcode.cn/problems/find-pivot-index/) 寻找数组的中心下标 (E) · [930](https://leetcode.cn/problems/binary-subarrays-with-sum/) 和相同的二元子数组 (M)
- [974](https://leetcode.cn/problems/subarray-sums-divisible-by-k/) 和可被 K 整除的子数组 (M) · [523](https://leetcode.cn/problems/continuous-subarray-sum/) 连续的子数组和 (M) · [525](https://leetcode.cn/problems/contiguous-array/) 连续数组 (M)
- [205](https://leetcode.cn/problems/isomorphic-strings/) 同构字符串 (E) · [290](https://leetcode.cn/problems/word-pattern/) 单词规律 (E) · [454](https://leetcode.cn/problems/4sum-ii/) 四数相加 II (M)

## 已完成题目

- [31.下一个排列.cpp](31.下一个排列.cpp)
