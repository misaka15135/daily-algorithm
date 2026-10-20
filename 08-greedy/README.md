# 08 · 贪心

> 对应计划：第 12 周（2027-01-04 ～ 2027-01-10）  
> 核心题量：18 题

## 本节目标

- 理解贪心算法的适用前提：局部最优能推出全局最优。
- 掌握区间调度、区间覆盖、跳跃游戏三类经典贪心。
- 能通过「交换论证」说明贪心策略为什么正确。
- 知道什么时候贪心会失效，需要改用 DP。

## 前置知识

### 1. 贪心的两个性质

- **贪心选择性质**：每一步的局部最优选择属于某个全局最优解。
- **最优子结构**：问题的最优解包含子问题的最优解。

### 2. 交换论证

假设存在一个最优解与贪心选择不同，通过交换元素构造另一个不劣的最优解，从而证明贪心选择可以纳入最优解。面试中能说清「为什么按这个关键字排序」即可。

### 3. 区间问题

| 目标 | 排序关键字 | 遍历策略 |
| --- | --- | --- |
| 最多不重叠区间 | 右端点升序 | 选右端点最早结束的 |
| 最少箭引爆气球 | 右端点升序 | 箭放在当前区间右端点 |
| 合并区间 | 左端点升序 | 维护当前合并区间 |
| 无重叠区间（最少删除） | 右端点升序 | 统计不重叠区间数 |

### 4. 跳跃游戏

- 维护「当前能到达的最远下标」`reach`。
- 遍历时如果 `i > reach`，说明无法到达，返回 false。
- 跳跃游戏 II 需要记录「当前层的最远边界」和「下一层的最远边界」。

## 核心模板

### 区间调度：无重叠区间

```cpp
int eraseOverlapIntervals(vector<vector<int>>& intervals) {
    sort(intervals.begin(), intervals.end(),
         [](auto& a, auto& b) { return a[1] < b[1]; });
    int keep = 0, end = INT_MIN;
    for (auto& x : intervals) {
        if (x[0] >= end) { ++keep; end = x[1]; }
    }
    return intervals.size() - keep;
}
```

### 跳跃游戏

```cpp
bool canJump(vector<int>& nums) {
    int reach = 0;
    for (int i = 0; i < (int)nums.size(); ++i) {
        if (i > reach) return false;
        reach = max(reach, i + nums[i]);
    }
    return true;
}
```

### 跳跃游戏 II

```cpp
int jump(vector<int>& nums) {
    int n = nums.size();
    int end = 0, farthest = 0, steps = 0;
    for (int i = 0; i < n - 1; ++i) {
        farthest = max(farthest, i + nums[i]);
        if (i == end) { ++steps; end = farthest; }
    }
    return steps;
}
```

### 分发糖果（两次遍历）

```cpp
int candy(vector<int>& ratings) {
    int n = ratings.size();
    vector<int> c(n, 1);
    for (int i = 1; i < n; ++i)
        if (ratings[i] > ratings[i - 1]) c[i] = c[i - 1] + 1;
    for (int i = n - 2; i >= 0; --i)
        if (ratings[i] > ratings[i + 1]) c[i] = max(c[i], c[i + 1] + 1);
    return accumulate(c.begin(), c.end(), 0);
}
```

## 例题拆解

### 55. 跳跃游戏（Medium）

- 维护最远可达位置 `reach`，遍历中更新。
- 如果某个位置 `i > reach`，说明前面的跳跃无法到达这里。
- 复杂度：时间 `O(n)`，空间 `O(1)`。

### 435. 无重叠区间（Medium）

- 按右端点升序，能选就选，选完更新结束时间。
- 最少删除数 = 总区间数 - 最多不重叠区间数。
- 复杂度：时间 `O(n log n)`，空间 `O(1)`。

### 452. 用最少数量的箭引爆气球（Medium）

- 按右端点升序，箭放在当前区间右端点，能覆盖后续就继续。
- 与 435 的遍历框架几乎相同，只是统计的是「箭数」。
- 复杂度：时间 `O(n log n)`，空间 `O(1)`。

### 134. 加油站（Medium）

- 如果总油量小于总消耗，一定无解。
- 从起点开始累加，若当前剩余油量小于 0，则起点设为 `i+1`，重新开始。
- 复杂度：时间 `O(n)`，空间 `O(1)`。

### 135. 分发糖果（Hard）

- 左到右处理「右边比左边大」，右到左处理「左边比右边大」。
- 每个孩子取两次约束的较大值。
- 复杂度：时间 `O(n)`，空间 `O(n)`。

## 常见坑点

- 区间问题排序关键字选错：最多不重叠按右端点，合并区间按左端点。
- 区间端点相等时的处理（`>=` 还是 `>`）要根据题意。
- 跳跃游戏 II 中最后一层不需要再跳，循环到 `n-1` 即可。
- 分发糖果只做一次遍历，漏掉另一侧约束。
- 贪心策略没有证明，遇到反例才改用 DP。
- `int` 累加可能溢出，用 `long long`。

## 题目清单

### 第 12 周 · 贪心：区间调度、跳跃游戏、排序策略（18 题）

- [55](https://leetcode.cn/problems/jump-game/) 跳跃游戏 (M) · [45](https://leetcode.cn/problems/jump-game-ii/) 跳跃游戏 II (M) · [122](https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-ii/) 买卖股票的最佳时机 II (M)
- [135](https://leetcode.cn/problems/candy/) 分发糖果 (H) · [621](https://leetcode.cn/problems/task-scheduler/) 任务调度器 (M) · [435](https://leetcode.cn/problems/non-overlapping-intervals/) 无重叠区间 (M)
- [134](https://leetcode.cn/problems/gas-station/) 加油站 (M) · [611](https://leetcode.cn/problems/valid-triangle-number/) 有效三角形的个数 (M) · [410](https://leetcode.cn/problems/split-array-largest-sum/) 分割数组的最大值 (H)
- [455](https://leetcode.cn/problems/assign-cookies/) 分发饼干 (E) · [452](https://leetcode.cn/problems/minimum-number-of-arrows-to-burst-balloons/) 用最少数量的箭引爆气球 (M) · [763](https://leetcode.cn/problems/partition-labels/) 划分字母区间 (M)
- [738](https://leetcode.cn/problems/monotone-increasing-digits/) 单调递增的数字 (M) · [860](https://leetcode.cn/problems/lemonade-change/) 柠檬水找零 (E) · [881](https://leetcode.cn/problems/boats-to-save-people/) 救生艇 (M)
- [1005](https://leetcode.cn/problems/maximize-sum-of-array-after-k-negations/) K 次取反后最大化的数组和 (E) · [1029](https://leetcode.cn/problems/two-city-scheduling/) 两地调度 (M) · [1338](https://leetcode.cn/problems/reduce-array-size-to-the-half/) 数组大小减半 (M)

## 已完成题目

暂无。按计划完成后，把 `<题号>.<题目标题>.cpp` 放在本文件夹即可。
