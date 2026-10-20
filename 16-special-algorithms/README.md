# 16 · 特殊算法

> 对应计划：第 26 周（2027-04-12 ～ 2027-04-18）  
> 核心题量：18 题

## 本节目标

- 掌握扫描线处理区间/矩形问题。
- 理解 minimax、Nim 博弈等简单博弈模型。
- 能稳定实现模拟题（螺旋矩阵、井字棋、机器人）。
- 会做常见脑筋急转弯，先找规律再写代码。

## 前置知识

### 1. 扫描线

把区间/矩形拆成「事件」，按坐标排序后扫描：

- 区间交集：左端点 `+1`、右端点 `-1`，或用双指针。
- 矩形面积并：按 x 扫描，维护 y 方向的覆盖长度（线段树）。
- 天际线：建筑左边界入堆、右边界出堆，记录高度变化。

事件排序时要注意「同一坐标下先处理结束还是开始」，取决于题目是否把边界算作重叠。

### 2. 区间交集

两个有序区间列表求交集，用双指针：

```text
l = max(a.start, b.start)
r = min(a.end, b.end)
if l <= r: 记录 [l, r]
移动右端点较小的那个指针
```

### 3. 博弈论

- **Nim 游戏**：所有堆石子数异或，非 0 先手必胜。
- **minimax**：双方都最优，当前玩家在所有选择中取最大，对手回合取最小。
- **必败态/必胜态**：从终止状态倒推；能走到必败态的是必胜态。
- 石子游戏系列常用区间 DP 或数学结论（先手必胜/必败）。

### 4. 模拟

- 明确状态：位置、方向、时间、棋盘。
- 用方向数组 `dirs[4][2]` 处理转向。
- 边界和碰撞规则逐条实现，先写清规则再写代码。

### 5. 脑筋急转弯

- 先手玩小数据找规律。
- 关注奇偶性、对称性、不变量。
- 证明往往比代码更重要；代码通常很短。

## 核心模板

### 区间列表的交集

```cpp
vector<vector<int>> intervalIntersection(vector<vector<int>>& a,
                                         vector<vector<int>>& b) {
    vector<vector<int>> ans;
    int i = 0, j = 0;
    while (i < (int)a.size() && j < (int)b.size()) {
        int l = max(a[i][0], b[j][0]);
        int r = min(a[i][1], b[j][1]);
        if (l <= r) ans.push_back({l, r});
        if (a[i][1] < b[j][1]) ++i;
        else ++j;
    }
    return ans;
}
```

### 扫描线：天际线问题（事件 + 堆）

```cpp
vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
    vector<pair<int,int>> events; // {x, height}，负高度表示左边界
    for (auto& b : buildings) {
        events.push_back({b[0], -b[2]});
        events.push_back({b[1], b[2]});
    }
    sort(events.begin(), events.end());
    multiset<int> heights{0};
    vector<vector<int>> ans;
    int prev = 0;
    for (int i = 0; i < (int)events.size();) {
        int x = events[i].first;
        while (i < (int)events.size() && events[i].first == x) {
            int h = events[i].second;
            if (h < 0) heights.insert(-h);
            else heights.erase(heights.find(h));
            ++i;
        }
        int cur = *heights.rbegin();
        if (cur != prev) { ans.push_back({x, cur}); prev = cur; }
    }
    return ans;
}
```

### Nim 游戏

```cpp
bool canWinNim(int n) {
    return n % 4 != 0;
}
```

### minimax：预测赢家（区间 DP）

```cpp
bool predictTheWinner(vector<int>& a) {
    int n = a.size();
    vector<vector<int>> dp(n, vector<int>(n));
    for (int i = 0; i < n; ++i) dp[i][i] = a[i];
    for (int len = 2; len <= n; ++len)
        for (int l = 0; l + len - 1 < n; ++l) {
            int r = l + len - 1;
            dp[l][r] = max(a[l] - dp[l + 1][r], a[r] - dp[l][r - 1]);
        }
    return dp[0][n - 1] >= 0;
}
```

### 螺旋矩阵 II

```cpp
vector<vector<int>> generateMatrix(int n) {
    vector<vector<int>> a(n, vector<int>(n));
    int top = 0, bottom = n - 1, left = 0, right = n - 1;
    int x = 1;
    while (x <= n * n) {
        for (int j = left; j <= right; ++j) a[top][j] = x++;
        ++top;
        for (int i = top; i <= bottom; ++i) a[i][right] = x++;
        --right;
        for (int j = right; j >= left; --j) a[bottom][j] = x++;
        --bottom;
        for (int i = bottom; i >= top; --i) a[i][left] = x++;
        ++left;
    }
    return a;
}
```

## 例题拆解

### 986. 区间列表的交集（Medium）

- 双指针，每次计算当前两个区间的交集，然后移动右端点较小的指针。
- 复杂度：时间 `O(n+m)`，空间 `O(1)`（不计结果）。

### 391. 完美矩形（Hard）

- 所有小矩形面积和等于大矩形面积，且所有顶点中只有四个角出现奇数次。
- 用哈希表统计顶点出现次数，面积和必须精确覆盖。
- 复杂度：时间 `O(n)`，空间 `O(n)`。

### 850. 矩形面积 II（Hard）

- 扫描线：按 x 分段，每段内收集覆盖的 y 区间，合并后乘以宽度。
- 复杂度：时间 `O(n² log n)`，空间 `O(n)`。

### 292. Nim 游戏（Easy）

- `n % 4 == 0` 必败，否则必胜。
- 复杂度：时间 `O(1)`，空间 `O(1)`。

### 59. 螺旋矩阵 II（Medium）

- 四个边界收缩，按右、下、左、上顺序填数。
- 注意 `n` 为奇数时最后一圈的中心格。
- 复杂度：时间 `O(n²)`，空间 `O(1)`（不计结果）。

### 794. 有效的井字游戏（Medium）

- 统计 X 和 O 的数量：`X == O` 或 `X == O + 1`。
- 如果 X 赢，必须 `X == O + 1`；如果 O 赢，必须 `X == O`；不能两人同时赢。
- 复杂度：时间 `O(1)`，空间 `O(1)`。

## 常见坑点

- 扫描线事件排序时，同一 x 的「结束」和「开始」顺序错误，导致高度抖动。
- 区间交集忘记判断 `l <= r`，把空区间加入结果。
- 天际线用 `multiset` 删除时只删一个元素，用 `erase(find(h))` 而不是 `erase(h)`。
- 博弈题没有区分「先手/后手」和「当前玩家」。
- minimax 的 DP 状态定义成「当前玩家得分」还是「分差」，转移方向不同。
- 模拟题方向数组和边界处理写错，导致越界或死循环。
- 井字棋只检查数量不检查胜负关系。
- 「完美矩形」只比较面积和，没有检查顶点覆盖。

## 题目清单

### 第 26 周 · 特殊算法：扫描线、博弈、模拟、脑筋急转弯（18 题）

- [1025](https://leetcode.cn/problems/divisor-game/) 除数博弈 (E) · [1227](https://leetcode.cn/problems/airplane-seat-assignment-probability/) 飞机座位分配概率 (M) · [319](https://leetcode.cn/problems/bulb-switcher/) 灯泡开关 (M)
- [810](https://leetcode.cn/problems/chalkboard-xor-game/) 黑板异或游戏 (H) · [1033](https://leetcode.cn/problems/moving-stones-until-consecutive/) 移动石子直到连续 (M) · [1503](https://leetcode.cn/problems/last-moment-before-all-ants-fall-out-of-a-plank/) 所有蚂蚁掉下来前的最后一刻 (M)
- [2731](https://leetcode.cn/problems/movement-of-robots/) 移动机器人 (M) · [2419](https://leetcode.cn/problems/longest-subarray-with-maximum-bitwise-and/) 按位与最大的最长子数组 (M) · [794](https://leetcode.cn/problems/valid-tic-tac-toe-state/) 有效的井字游戏 (M)
- [913](https://leetcode.cn/problems/cat-and-mouse/) 猫和老鼠 (H) · [1728](https://leetcode.cn/problems/cat-and-mouse-ii/) 猫和老鼠 II (H) · [986](https://leetcode.cn/problems/interval-list-intersections/) 区间列表的交集 (M)
- [850](https://leetcode.cn/problems/rectangle-area-ii/) 矩形面积 II (H) · [391](https://leetcode.cn/problems/perfect-rectangle/) 完美矩形 (H) · [1851](https://leetcode.cn/problems/minimum-interval-to-include-each-query/) 包含每个查询的最小区间 (H)
- [59](https://leetcode.cn/problems/spiral-matrix-ii/) 螺旋矩阵 II (M) · [498](https://leetcode.cn/problems/diagonal-traverse/) 对角线遍历 (M) · [2425](https://leetcode.cn/problems/bitwise-xor-of-all-pairings/) 所有数对的异或和 (M)

## 已完成题目

暂无。按计划完成后，把 `<题号>.<题目标题>.cpp` 放在本文件夹即可。
