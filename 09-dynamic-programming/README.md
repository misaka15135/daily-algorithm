# 09 · 动态规划

> 对应计划：第 13–16 周（2027-01-11 ～ 2027-02-07）  
> 核心题量：72 题

## 本节目标

- 能按「定义状态 → 转移方程 → 初始化 → 遍历顺序 → 返回答案」五步解题。
- 掌握线性 DP、网格 DP、背包、股票、打家劫舍、子序列、区间 DP、树形 DP、状态压缩。
- 能用滚动数组优化空间。
- 能区分「什么时候用 DP、什么时候用贪心/回溯」。

## 前置知识

### 1. 五步法

1. **状态定义**：`dp[i]` / `dp[i][j]` 表示什么。
2. **转移方程**：当前状态由哪些旧状态转移而来。
3. **初始化**：边界状态的值。
4. **遍历顺序**：保证用到的旧状态已经计算。
5. **返回答案**：`dp[n]` / `max(dp[...])`。

### 2. 常见状态设计

| 问题 | 状态 |
| --- | --- |
| 爬楼梯/斐波那契 | `dp[i]` 走到第 i 阶的方法数 |
| 打家劫舍 | `dp[i]` 前 i 间房的最大金额 |
| 背包 | `dp[j]` 容量 j 的最大价值 |
| LIS | `dp[i]` 以 a[i] 结尾的最长递增子序列长度 |
| LCS | `dp[i][j]` a 前 i 个、b 前 j 个的最长公共子序列 |
| 编辑距离 | `dp[i][j]` a 前 i 个变成 b 前 j 个的最少操作数 |
| 区间 DP | `dp[l][r]` 区间 [l,r] 的最优值 |
| 树形 DP | `dp[u][0/1]` 以 u 为根的子树，选/不选 u |

### 3. 背包问题

**0-1 背包**：每个物品只能选一次。

```text
for each item i:
    for j from capacity down to w[i]:
        dp[j] = max(dp[j], dp[j - w[i]] + v[i])
```

**完全背包**：每个物品可以选无限次。

```text
for each item i:
    for j from w[i] to capacity:
        dp[j] = max(dp[j], dp[j - w[i]] + v[i])
```

**组合数 vs 排列数**：

- 外层物品、内层容量 → 组合（不考虑顺序）。
- 外层容量、内层物品 → 排列（考虑顺序）。

### 4. 股票问题状态机

```text
dp[i][0] = 第 i 天不持股的最大收益
dp[i][1] = 第 i 天持股的最大收益
dp[i][0] = max(dp[i-1][0], dp[i-1][1] + price[i])
dp[i][1] = max(dp[i-1][1], dp[i-1][0] - price[i])
```

有冷冻期/手续费时，增加对应状态或调整转移。

### 5. 区间 DP

```text
for len from 2 to n:
    for l from 0 to n-len:
        r = l + len - 1
        for k from l to r-1:
            dp[l][r] = min/max(dp[l][r], dp[l][k] + dp[k+1][r] + cost)
```

### 6. 状态压缩

用二进制位表示集合，适合 `n <= 20` 的选取问题。

```text
dp[mask] = 处理完集合 mask 的最优值
for mask:
    for i not in mask:
        dp[mask | (1 << i)] = ...
```

## 核心模板

### 线性 DP：打家劫舍

```cpp
int rob(vector<int>& a) {
    int n = a.size();
    if (n == 0) return 0;
    int prev2 = 0, prev1 = 0;
    for (int x : a) {
        int cur = max(prev1, prev2 + x);
        prev2 = prev1;
        prev1 = cur;
    }
    return prev1;
}
```

### 0-1 背包

```cpp
int knapsack(vector<int>& w, vector<int>& v, int cap) {
    vector<int> dp(cap + 1, 0);
    for (int i = 0; i < (int)w.size(); ++i)
        for (int j = cap; j >= w[i]; --j)
            dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
    return dp[cap];
}
```

### 完全背包：零钱兑换

```cpp
int coinChange(vector<int>& coins, int amount) {
    vector<int> dp(amount + 1, INT_MAX / 2);
    dp[0] = 0;
    for (int c : coins)
        for (int j = c; j <= amount; ++j)
            dp[j] = min(dp[j], dp[j - c] + 1);
    return dp[amount] >= INT_MAX / 2 ? -1 : dp[amount];
}
```

### LIS：O(n²) 与 O(n log n)

```cpp
// O(n²)
int lengthOfLIS1(vector<int>& a) {
    int n = a.size(), ans = 0;
    vector<int> dp(n, 1);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j)
            if (a[j] < a[i]) dp[i] = max(dp[i], dp[j] + 1);
        ans = max(ans, dp[i]);
    }
    return ans;
}

// O(n log n)：维护长度为 len 的递增子序列的最小结尾
int lengthOfLIS2(vector<int>& a) {
    vector<int> tails;
    for (int x : a) {
        auto it = lower_bound(tails.begin(), tails.end(), x);
        if (it == tails.end()) tails.push_back(x);
        else *it = x;
    }
    return tails.size();
}
```

### 编辑距离

```cpp
int minDistance(string a, string b) {
    int n = a.size(), m = b.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1));
    for (int i = 0; i <= n; ++i) dp[i][0] = i;
    for (int j = 0; j <= m; ++j) dp[0][j] = j;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            if (a[i - 1] == b[j - 1]) dp[i][j] = dp[i - 1][j - 1];
            else dp[i][j] = 1 + min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
        }
    return dp[n][m];
}
```

### 区间 DP：戳气球

```cpp
int maxCoins(vector<int>& nums) {
    int n = nums.size();
    vector<int> a(n + 2, 1);
    for (int i = 0; i < n; ++i) a[i + 1] = nums[i];
    vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));
    for (int len = 1; len <= n; ++len)
        for (int l = 1; l + len - 1 <= n; ++l) {
            int r = l + len - 1;
            for (int k = l; k <= r; ++k)
                dp[l][r] = max(dp[l][r],
                    dp[l][k - 1] + a[l - 1] * a[k] * a[r + 1] + dp[k + 1][r]);
        }
    return dp[1][n];
}
```

### 树形 DP：打家劫舍 III

```cpp
pair<int,int> dfs(TreeNode* u) { // {不选 u, 选 u}
    if (!u) return {0, 0};
    auto [l0, l1] = dfs(u->left);
    auto [r0, r1] = dfs(u->right);
    int notPick = max(l0, l1) + max(r0, r1);
    int pick = u->val + l0 + r0;
    return {notPick, pick};
}
```

## 例题拆解

### 70. 爬楼梯（Easy）

- `dp[i] = dp[i-1] + dp[i-2]`，`dp[0]=1, dp[1]=1`。
- 可以用两个变量滚动。
- 复杂度：时间 `O(n)`，空间 `O(1)`。

### 322. 零钱兑换（Medium）

- 完全背包求最少个数：`dp[j] = min(dp[j], dp[j-c] + 1)`。
- 初始化 `dp[0]=0`，其余为无穷大。
- 遍历顺序：外层硬币、内层容量从 `c` 到 `amount`。
- 复杂度：时间 `O(amount × n)`，空间 `O(amount)`。

### 300. 最长递增子序列（Medium）

- `dp[i]` 表示以 `a[i]` 结尾的 LIS 长度，`O(n²)`。
- 进阶：维护 `tails` 数组，二分替换，`O(n log n)`。
- 注意 `tails` 不是真正的 LIS，只用于求长度。

### 72. 编辑距离（Hard）

- 三种操作对应三个方向：删除 `dp[i-1][j]+1`、插入 `dp[i][j-1]+1`、替换 `dp[i-1][j-1]+1`。
- 字符相等时直接继承 `dp[i-1][j-1]`。
- 复杂度：时间 `O(nm)`，空间 `O(nm)`，可滚动到 `O(m)`。

### 312. 戳气球（Hard）

- 反过来思考「最后戳破哪个气球」，把问题分成左右两个独立子区间。
- 在数组两端补 `1`，`dp[l][r]` 表示戳破开区间 `(l,r)` 内所有气球的最大收益。
- 复杂度：时间 `O(n³)`，空间 `O(n²)`。

## 常见坑点

- 状态定义含糊，导致转移方程写不出来；先用一句话说清 `dp[i]` 的含义。
- 0-1 背包内层循环写成正序，变成完全背包。
- 完全背包的组合/排列遍历顺序搞反。
- 初始化错误：求最小值时忘记把 `dp` 初始化为无穷大，求最大值时忘记初始化为 0。
- 遍历顺序错误：区间 DP 必须先枚举长度，再枚举左端点。
- LIS 的 `lower_bound` 与 `upper_bound` 用错：严格递增用 `lower_bound`，非递减用 `upper_bound`。
- 股票问题状态转移漏掉冷冻期/手续费/交易次数限制。
- 树形 DP 没有考虑「选父节点就不能选子节点」的约束。
- 状态压缩的 `mask` 范围是 `1<<n`，不是 `n`。
- 空间优化后仍按二维方式访问，导致覆盖顺序错误。

## 题目清单

### 第 13 周 · DP I：线性 DP、网格路径、打家劫舍（18 题）

- [70](https://leetcode.cn/problems/climbing-stairs/) 爬楼梯 (E) · [746](https://leetcode.cn/problems/min-cost-climbing-stairs/) 使用最小花费爬楼梯 (E) · [1137](https://leetcode.cn/problems/n-th-tribonacci-number/) 第 N 个泰波那契数 (E)
- [121](https://leetcode.cn/problems/best-time-to-buy-and-sell-stock/) 买卖股票的最佳时机 (E) · [198](https://leetcode.cn/problems/house-robber/) 打家劫舍 (M) · [213](https://leetcode.cn/problems/house-robber-ii/) 打家劫舍 II (M)
- [62](https://leetcode.cn/problems/unique-paths/) 不同路径 (M) · [63](https://leetcode.cn/problems/unique-paths-ii/) 不同路径 II (M) · [64](https://leetcode.cn/problems/minimum-path-sum/) 最小路径和 (M)
- [120](https://leetcode.cn/problems/triangle/) 三角形最小路径和 (M) · [91](https://leetcode.cn/problems/decode-ways/) 解码方法 (M) · [139](https://leetcode.cn/problems/word-break/) 单词拆分 (M)
- [152](https://leetcode.cn/problems/maximum-product-subarray/) 乘积最大子数组 (M) · [221](https://leetcode.cn/problems/maximal-square/) 最大正方形 (M) · [279](https://leetcode.cn/problems/perfect-squares/) 完全平方数 (M)
- [322](https://leetcode.cn/problems/coin-change/) 零钱兑换 (M) · [343](https://leetcode.cn/problems/integer-break/) 整数拆分 (M) · [740](https://leetcode.cn/problems/delete-and-earn/) 删除并获得点数 (M)

### 第 14 周 · DP II：背包、股票买卖、划分型 DP（18 题）

- [416](https://leetcode.cn/problems/partition-equal-subset-sum/) 分割等和子集 (M) · [474](https://leetcode.cn/problems/ones-and-zeroes/) 一和零 (M) · [494](https://leetcode.cn/problems/target-sum/) 目标和 (M)
- [518](https://leetcode.cn/problems/coin-change-ii/) 零钱兑换 II (M) · [1049](https://leetcode.cn/problems/last-stone-weight-ii/) 最后一块石头的重量 II (M) · [377](https://leetcode.cn/problems/combination-sum-iv/) 组合总和 Ⅳ (M)
- [337](https://leetcode.cn/problems/house-robber-iii/) 打家劫舍 III (M) · [123](https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-iii/) 买卖股票的最佳时机 III (H) · [188](https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-iv/) 买卖股票的最佳时机 IV (H)
- [309](https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-with-cooldown/) 买卖股票的最佳时机含冷冻期 (M) · [714](https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/) 买卖股票的最佳时机含手续费 (M) · [879](https://leetcode.cn/problems/profitable-schemes/) 盈利计划 (H)
- [1155](https://leetcode.cn/problems/number-of-dice-rolls-with-target-sum/) 掷骰子等于目标和的方法数 (M) · [638](https://leetcode.cn/problems/shopping-offers/) 大礼包 (M) · [983](https://leetcode.cn/problems/minimum-cost-for-tickets/) 最低票价 (M)
- [1105](https://leetcode.cn/problems/filling-bookcase-shelves/) 填充书架 (M) · [1043](https://leetcode.cn/problems/partition-array-for-maximum-sum/) 分隔数组以得到最大和 (M) · [1235](https://leetcode.cn/problems/maximum-profit-in-job-scheduling/) 规划兼职工作 (H)

### 第 15 周 · DP III：子序列、字符串编辑、LIS/LCS（18 题）

- [300](https://leetcode.cn/problems/longest-increasing-subsequence/) 最长递增子序列 (M) · [1143](https://leetcode.cn/problems/longest-common-subsequence/) 最长公共子序列 (M) · [72](https://leetcode.cn/problems/edit-distance/) 编辑距离 (M)
- [44](https://leetcode.cn/problems/wildcard-matching/) 通配符匹配 (H) · [97](https://leetcode.cn/problems/interleaving-string/) 交错字符串 (M) · [115](https://leetcode.cn/problems/distinct-subsequences/) 不同的子序列 (H)
- [132](https://leetcode.cn/problems/palindrome-partitioning-ii/) 分割回文串 II (H) · [516](https://leetcode.cn/problems/longest-palindromic-subsequence/) 最长回文子序列 (M) · [583](https://leetcode.cn/problems/delete-operation-for-two-strings/) 两个字符串的删除操作 (M)
- [647](https://leetcode.cn/problems/palindromic-substrings/) 回文子串 (M) · [712](https://leetcode.cn/problems/minimum-ascii-delete-sum-for-two-strings/) 两个字符串的最小ASCII删除和 (M) · [718](https://leetcode.cn/problems/maximum-length-of-repeated-subarray/) 最长重复子数组 (M)
- [1035](https://leetcode.cn/problems/uncrossed-lines/) 不相交的线 (M) · [1092](https://leetcode.cn/problems/shortest-common-supersequence/) 最短公共超序列 (H) · [1312](https://leetcode.cn/problems/minimum-insertion-steps-to-make-a-string-palindrome/) 让字符串成为回文串的最少插入次数 (H)
- [354](https://leetcode.cn/problems/russian-doll-envelopes/) 俄罗斯套娃信封问题 (H) · [673](https://leetcode.cn/problems/number-of-longest-increasing-subsequence/) 最长递增子序列的个数 (M) · [1027](https://leetcode.cn/problems/longest-arithmetic-subsequence/) 最长等差数列 (M)

### 第 16 周 · DP IV：区间 DP、树形 DP、状态压缩、记忆化（18 题）

- [312](https://leetcode.cn/problems/burst-balloons/) 戳气球 (H) · [546](https://leetcode.cn/problems/remove-boxes/) 移除盒子 (H) · [664](https://leetcode.cn/problems/strange-printer/) 奇怪的打印机 (H)
- [1000](https://leetcode.cn/problems/minimum-cost-to-merge-stones/) 合并石头的最低成本 (H) · [1039](https://leetcode.cn/problems/minimum-score-triangulation-of-polygon/) 多边形三角剖分的最低得分 (M) · [1130](https://leetcode.cn/problems/minimum-cost-tree-from-leaf-values/) 叶值的最小代价生成树 (M)
- [1547](https://leetcode.cn/problems/minimum-cost-to-cut-a-stick/) 切棍子的最小成本 (H) · [1563](https://leetcode.cn/problems/stone-game-v/) 石子游戏 V (H) · [486](https://leetcode.cn/problems/predict-the-winner/) 预测赢家 (M)
- [877](https://leetcode.cn/problems/stone-game/) 石子游戏 (M) · [1140](https://leetcode.cn/problems/stone-game-ii/) 石子游戏 II (M) · [375](https://leetcode.cn/problems/guess-number-higher-or-lower-ii/) 猜数字大小 II (M)
- [968](https://leetcode.cn/problems/binary-tree-cameras/) 监控二叉树 (H) · [979](https://leetcode.cn/problems/distribute-coins-in-binary-tree/) 在二叉树中分配硬币 (M) · [1473](https://leetcode.cn/problems/paint-house-iii/) 粉刷房子 III (H)
- [1335](https://leetcode.cn/problems/minimum-difficulty-of-a-job-schedule/) 工作计划的最低难度 (H) · [691](https://leetcode.cn/problems/stickers-to-spell-word/) 贴纸拼词 (H) · [847](https://leetcode.cn/problems/shortest-path-visiting-all-nodes/) 访问所有节点的最短路径 (H)

## 已完成题目

- [10.正则表达式匹配.cpp](10.正则表达式匹配.cpp)
