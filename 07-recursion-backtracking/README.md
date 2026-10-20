# 07 · 递归与回溯

> 对应计划：第 10–11 周（2026-12-21 ～ 2027-01-03）  
> 核心题量：36 题

## 本节目标

- 能画出递归树，写出正确的递归终止条件和返回值。
- 掌握分治的三步：分解、解决、合并。
- 掌握回溯模板：选择 → 递归 → 撤销选择。
- 掌握组合/排列/子集/切割/棋盘五类问题的去重与剪枝。

## 前置知识

### 1. 递归三要素

1. **终止条件**：什么时候直接返回。
2. **本层做什么**：处理当前状态。
3. **返回值/副作用**：向上返回什么，或修改什么全局状态。

### 2. 递归树

把递归调用画成树，节点是状态，边是选择。递归树的深度决定栈空间，分支数决定时间复杂度。

### 3. 分治

```text
solve(problem):
    if problem is small: return base
    split into subproblems
    left = solve(left)
    right = solve(right)
    return merge(left, right)
```

典型：归并排序、快速幂、构造二叉树、为表达式设计优先级。

### 4. 回溯

回溯是带「撤销」的 DFS。关键是把路径状态恢复到进入本层之前。

```text
void backtrack(路径, 选择列表):
    if 满足结束条件:
        记录结果
        return
    for 选择 in 选择列表:
        做选择
        backtrack(路径, 新的选择列表)
        撤销选择
```

### 5. 去重

- 组合/子集：先排序，同一层中 `i > start && a[i] == a[i-1]` 时跳过。
- 排列：用 `used[i]`，若 `i > 0 && a[i] == a[i-1] && !used[i-1]` 则跳过（同一树层去重）。
- 切割：枚举切割点，判断子串是否合法。

### 6. 剪枝

- 组合总和：剩余和小于 0 时剪枝；排序后当前元素大于剩余目标时 break。
- N 皇后：列、主对角线 `r-c`、副对角线 `r+c` 三个集合判重。
- 数独：行、列、宫三个 `bool` 数组判重。

## 核心模板

### 子集

```cpp
void dfs(vector<int>& a, int start, vector<int>& path, vector<vector<int>>& ans) {
    ans.push_back(path);
    for (int i = start; i < (int)a.size(); ++i) {
        path.push_back(a[i]);
        dfs(a, i + 1, path, ans);
        path.pop_back();
    }
}
```

### 全排列（含重复元素去重）

```cpp
void dfs(vector<int>& a, vector<int>& path, vector<bool>& used,
         vector<vector<int>>& ans) {
    if (path.size() == a.size()) { ans.push_back(path); return; }
    for (int i = 0; i < (int)a.size(); ++i) {
        if (used[i]) continue;
        if (i > 0 && a[i] == a[i - 1] && !used[i - 1]) continue; // 同层去重
        used[i] = true;
        path.push_back(a[i]);
        dfs(a, path, used, ans);
        path.pop_back();
        used[i] = false;
    }
}
```

### 组合总和（可重复选取 + 剪枝）

```cpp
void dfs(vector<int>& a, int start, int remain, vector<int>& path,
         vector<vector<int>>& ans) {
    if (remain == 0) { ans.push_back(path); return; }
    for (int i = start; i < (int)a.size() && a[i] <= remain; ++i) {
        path.push_back(a[i]);
        dfs(a, i, remain - a[i], path, ans); // i 而不是 i+1：可重复选
        path.pop_back();
    }
}
```

### 快速幂（分治）

```cpp
double myPow(double x, long long n) {
    if (n == 0) return 1;
    if (n < 0) return 1 / myPow(x, -n);
    double half = myPow(x, n / 2);
    return n % 2 ? half * half * x : half * half;
}
```

## 例题拆解

### 46. 全排列（Medium）

- 路径长度等于数组长度时收集结果。
- `used` 数组标记已选元素；撤销时恢复。
- 复杂度：时间 `O(n·n!)`，空间 `O(n)`。

### 78. 子集（Medium）

- 每个节点都是答案，先 `push` 再递归。
- `start` 参数保证不重复选前面的元素。
- 复杂度：时间 `O(n·2^n)`，空间 `O(n)`。

### 51. N 皇后（Hard）

- 逐行放置皇后，用 `col`、`diag1`、`diag2` 三个集合判断冲突。
- 主对角线特征 `r - c`，副对角线特征 `r + c`。
- 找到一种放置后记录棋盘，再撤销。
- 复杂度：时间 `O(n!)`，空间 `O(n)`。

### 22. 括号生成（Medium，已完成）

- 状态：已用左括号数 `l`、右括号数 `r`。
- 选择：`l < n` 可放左括号；`r < l` 可放右括号。
- 这是「剪枝 + 回溯」的典型。

### 241. 为运算表达式设计优先级（Medium）

- 分治：枚举每个运算符作为最后计算的运算符，递归计算左右两侧。
- 用 `map<string, vector<int>>` 记忆化可去重。
- 复杂度：加泰罗尼亚数级别。

## 常见坑点

- 结果容器 push 的是 `path` 的拷贝；如果 push 引用，后续回溯会修改结果。
- 去重前没有排序，导致相同元素不相邻。
- 排列去重条件写成 `!used[i]` 或漏掉 `!used[i-1]`。
- 组合问题递归传 `i` 还是 `i+1` 取决于是否允许重复选取。
- 剪枝条件写错，提前 break 掉合法分支。
- 递归深度过大导致栈溢出（如暴力递归斐波那契），应改记忆化/迭代。
- 分治没有处理空区间/单元素边界。

## 题目清单

### 第 10 周 · 递归与分治：递归树、表达式、分治合并（18 题）

- [50](https://leetcode.cn/problems/powx-n/) Pow(x, n) (M) · [509](https://leetcode.cn/problems/fibonacci-number/) 斐波那契数 (E) · [273](https://leetcode.cn/problems/integer-to-english-words/) 整数转换英文表示 (H)
- [233](https://leetcode.cn/problems/number-of-digit-one/) 数字 1 的个数 (H) · [60](https://leetcode.cn/problems/permutation-sequence/) 排列序列 (H) · [241](https://leetcode.cn/problems/different-ways-to-add-parentheses/) 为运算表达式设计优先级 (M)
- [191](https://leetcode.cn/problems/number-of-1-bits/) 位1的个数 (E) · [95](https://leetcode.cn/problems/unique-binary-search-trees-ii/) 不同的二叉搜索树 II (M) · [372](https://leetcode.cn/problems/super-pow/) 超级次方 (M)
- [89](https://leetcode.cn/problems/gray-code/) 格雷编码 (M) · [779](https://leetcode.cn/problems/k-th-symbol-in-grammar/) 第K个语法符号 (M) · [880](https://leetcode.cn/problems/decoded-string-at-index/) 索引处的解码字符串 (M)
- [1545](https://leetcode.cn/problems/find-kth-bit-in-nth-binary-string/) 找出第 N 个二进制字符串中的第 K 位 (M) · [1922](https://leetcode.cn/problems/count-good-numbers/) 统计好数字的数目 (M) · [46](https://leetcode.cn/problems/permutations/) 全排列 (M)
- [78](https://leetcode.cn/problems/subsets/) 子集 (M) · [77](https://leetcode.cn/problems/combinations/) 组合 (M) · [39](https://leetcode.cn/problems/combination-sum/) 组合总和 (M)

### 第 11 周 · 回溯：组合、排列、子集、切割、棋盘（18 题）

- [40](https://leetcode.cn/problems/combination-sum-ii/) 组合总和 II (M) · [47](https://leetcode.cn/problems/permutations-ii/) 全排列 II (M) · [79](https://leetcode.cn/problems/word-search/) 单词搜索 (M)
- [93](https://leetcode.cn/problems/restore-ip-addresses/) 复原 IP 地址 (M) · [131](https://leetcode.cn/problems/palindrome-partitioning/) 分割回文串 (M) · [51](https://leetcode.cn/problems/n-queens/) N 皇后 (H)
- [37](https://leetcode.cn/problems/sudoku-solver/) 解数独 (H) · [212](https://leetcode.cn/problems/word-search-ii/) 单词搜索 II (H) · [216](https://leetcode.cn/problems/combination-sum-iii/) 组合总和 III (M)
- [90](https://leetcode.cn/problems/subsets-ii/) 子集 II (M) · [306](https://leetcode.cn/problems/additive-number/) 累加数 (M) · [282](https://leetcode.cn/problems/expression-add-operators/) 给表达式添加运算符 (H)
- [301](https://leetcode.cn/problems/remove-invalid-parentheses/) 删除无效的括号 (H) · [491](https://leetcode.cn/problems/non-decreasing-subsequences/) 非递减子序列 (M) · [473](https://leetcode.cn/problems/matchsticks-to-square/) 火柴拼正方形 (M)
- [698](https://leetcode.cn/problems/partition-to-k-equal-sum-subsets/) 划分为k个相等的子集 (M) · [526](https://leetcode.cn/problems/beautiful-arrangement/) 优美的排列 (M) · [784](https://leetcode.cn/problems/letter-case-permutation/) 字母大小写全排列 (M)

## 已完成题目

- [17.电话号码的字母组合.cpp](17.电话号码的字母组合.cpp)
- [22.括号生成.cpp](22.括号生成.cpp)
