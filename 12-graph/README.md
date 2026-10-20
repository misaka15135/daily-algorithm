# 12 · 图论

> 对应计划：第 21–22 周（2027-03-08 ～ 2027-03-21）  
> 核心题量：36 题

## 本节目标

- 掌握邻接表的建图方式，区分有向图/无向图、带权图。
- 熟练掌握 DFS/BFS 求连通分量、网格图搜索。
- 掌握拓扑排序（Kahn 与 DFS）判断有向图是否有环。
- 掌握 Dijkstra、Bellman-Ford、Floyd 的适用场景。
- 了解 Kruskal/Prim 最小生成树、二分图判定。

## 前置知识

### 1. 建图

```cpp
// 无权图
vector<vector<int>> g(n);
for (auto& e : edges) {
    g[e[0]].push_back(e[1]);
    g[e[1]].push_back(e[0]); // 无向图
}

// 带权图
vector<vector<pair<int,int>>> g(n); // {to, weight}
```

- 节点编号是 0-based 还是 1-based，建图前统一。
- 网格图可以把 `(r,c)` 映射为 `r*m+c`，也可以直接在网格上 DFS/BFS。

### 2. DFS vs BFS

| 算法 | 数据结构 | 适用 |
| --- | --- | --- |
| DFS | 递归/栈 | 连通性、路径枚举、拓扑排序、回溯 |
| BFS | 队列 | 无权最短路、层序、多源扩散 |

### 3. 拓扑排序

- 只适用于有向无环图（DAG）。
- Kahn：统计入度，入度为 0 的节点入队，弹出后减少邻居入度。
- DFS：后序遍历逆序；用三色标记检测环。
- 如果拓扑序列长度小于节点数，说明有环。

### 4. 最短路算法

| 算法 | 适用 | 复杂度 |
| --- | --- | --- |
| BFS | 无权图 | `O(V+E)` |
| Dijkstra | 非负权 | `O((V+E) log V)` |
| Bellman-Ford | 可有负权，可判负环 | `O(VE)` |
| Floyd | 多源最短路 | `O(V³)` |

### 5. 最小生成树

- Kruskal：边按权排序 + 并查集，适合稀疏图。
- Prim：从点出发，用优先队列扩展，适合稠密图。

### 6. 二分图判定

对图黑白染色，相邻节点颜色不同。可用 BFS/DFS 或并查集（扩展域）。

## 核心模板

### DFS 求连通分量（网格）

```cpp
int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};

void dfs(vector<vector<char>>& g, int r, int c) {
    if (r < 0 || r >= (int)g.size() || c < 0 || c >= (int)g[0].size()) return;
    if (g[r][c] != '1') return;
    g[r][c] = '0'; // 标记已访问
    for (auto& d : dirs) dfs(g, r + d[0], c + d[1]);
}
```

### BFS 求无权最短路

```cpp
int bfs(vector<vector<int>>& g, int start, int target) {
    vector<int> dist(g.size(), -1);
    queue<int> q;
    dist[start] = 0;
    q.push(start);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (u == target) return dist[u];
        for (int v : g[u]) {
            if (dist[v] != -1) continue;
            dist[v] = dist[u] + 1;
            q.push(v);
        }
    }
    return -1;
}
```

### Kahn 拓扑排序

```cpp
vector<int> topoSort(int n, vector<vector<int>>& g) {
    vector<int> indeg(n, 0);
    for (int u = 0; u < n; ++u)
        for (int v : g[u]) ++indeg[v];
    queue<int> q;
    for (int i = 0; i < n; ++i) if (indeg[i] == 0) q.push(i);
    vector<int> order;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        order.push_back(u);
        for (int v : g[u])
            if (--indeg[v] == 0) q.push(v);
    }
    return order; // size < n 表示有环
}
```

### Dijkstra

```cpp
vector<long long> dijkstra(int n, vector<vector<pair<int,int>>>& g, int src) {
    vector<long long> dist(n, LLONG_MAX);
    priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<>> pq;
    dist[src] = 0;
    pq.push({0, src});
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue; // 懒删除
        for (auto [v, w] : g[u]) {
            if (dist[v] > d + w) {
                dist[v] = d + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}
```

### 并查集（Kruskal/连通性）

```cpp
struct DSU {
    vector<int> p, sz;
    DSU(int n) : p(n), sz(n, 1) { iota(p.begin(), p.end(), 0); }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    bool join(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        p[b] = a; sz[a] += sz[b];
        return true;
    }
};
```

## 例题拆解

### 200. 岛屿数量（Medium）

- 遍历网格，遇到 `'1'` 就计数并 DFS/BFS 把整个岛屿标记为 `'0'`。
- 复杂度：时间 `O(mn)`，空间 `O(mn)`（递归栈）。

### 207. 课程表（Medium）

- 有向图判环：Kahn 拓扑排序，若最终处理节点数小于 n 则有环。
- 复杂度：时间 `O(V+E)`，空间 `O(V+E)`。

### 743. 网络延迟时间（Medium）

- 单源最短路，非负权，用 Dijkstra。
- 答案是所有节点最短距离的最大值；有节点不可达返回 -1。
- 复杂度：时间 `O((V+E) log V)`，空间 `O(V+E)`。

### 547. 省份数量（Medium）

- 无向图连通分量数：DFS/BFS 或并查集。
- 邻接矩阵遍历是 `O(n²)`。
- 复杂度：时间 `O(n²)`，空间 `O(n)`。

### 329. 矩阵中的最长递增路径（Hard）

- 对每个格子 DFS，向四个方向找严格更大的值。
- 用记忆化 `memo[r][c]` 避免重复计算。
- 本质是 DAG 上的最长路径，也可以拓扑排序。
- 复杂度：时间 `O(mn)`，空间 `O(mn)`。

## 常见坑点

- 有向图和无向图的边只加了一个方向。
- 节点编号 0-based/1-based 混用，导致越界或漏点。
- 访问标记的时机：BFS 应在入队时标记，否则会重复入队。
- 拓扑排序忘记检查「处理节点数 < n」，漏判环。
- Dijkstra 不能处理负权边；负权用 Bellman-Ford/SPFA。
- Dijkstra 的优先队列没有懒删除，导致旧距离被重复处理。
- 网格 DFS 越界检查顺序错误，先访问 `g[r][c]` 再判越界。
- 递归 DFS 在超大网格上栈溢出，改用 BFS/迭代。
- 并查集忘记路径压缩或按秩合并，复杂度退化。

## 题目清单

### 第 21 周 · 图 I：DFS/BFS、连通分量、网格图（18 题）

- [200](https://leetcode.cn/problems/number-of-islands/) 岛屿数量 (M) · [695](https://leetcode.cn/problems/max-area-of-island/) 岛屿的最大面积 (M) · [130](https://leetcode.cn/problems/surrounded-regions/) 被围绕的区域 (M)
- [1254](https://leetcode.cn/problems/number-of-closed-islands/) 统计封闭岛屿的数目 (M) · [827](https://leetcode.cn/problems/making-a-large-island/) 最大人工岛 (H) · [133](https://leetcode.cn/problems/clone-graph/) 克隆图 (M)
- [797](https://leetcode.cn/problems/all-paths-from-source-to-target/) 所有可能的路径 (M) · [841](https://leetcode.cn/problems/keys-and-rooms/) 钥匙和房间 (M) · [547](https://leetcode.cn/problems/number-of-provinces/) 省份数量 (M)
- [785](https://leetcode.cn/problems/is-graph-bipartite/) 判断二分图 (M) · [994](https://leetcode.cn/problems/rotting-oranges/) 腐烂的橘子 (M) · [542](https://leetcode.cn/problems/01-matrix/) 01 矩阵 (M)
- [1091](https://leetcode.cn/problems/shortest-path-in-binary-matrix/) 二进制矩阵中的最短路径 (M) · [934](https://leetcode.cn/problems/shortest-bridge/) 最短的桥 (M) · [1020](https://leetcode.cn/problems/number-of-enclaves/) 飞地的数量 (M)
- [1905](https://leetcode.cn/problems/count-sub-islands/) 统计子岛屿 (M) · [733](https://leetcode.cn/problems/flood-fill/) 图像渲染 (E) · [997](https://leetcode.cn/problems/find-the-town-judge/) 找到小镇的法官 (E)

### 第 22 周 · 图 II：拓扑排序、最短路、最小生成树（18 题）

- [207](https://leetcode.cn/problems/course-schedule/) 课程表 (M) · [210](https://leetcode.cn/problems/course-schedule-ii/) 课程表 II (M) · [310](https://leetcode.cn/problems/minimum-height-trees/) 最小高度树 (M)
- [743](https://leetcode.cn/problems/network-delay-time/) 网络延迟时间 (M) · [787](https://leetcode.cn/problems/cheapest-flights-within-k-stops/) K 站中转内最便宜的航班 (M) · [399](https://leetcode.cn/problems/evaluate-division/) 除法求值 (M)
- [332](https://leetcode.cn/problems/reconstruct-itinerary/) 重新安排行程 (H) · [329](https://leetcode.cn/problems/longest-increasing-path-in-a-matrix/) 矩阵中的最长递增路径 (H) · [802](https://leetcode.cn/problems/find-eventual-safe-states/) 找到最终的安全状态 (M)
- [1462](https://leetcode.cn/problems/course-schedule-iv/) 课程表 IV (M) · [2115](https://leetcode.cn/problems/find-all-possible-recipes-from-given-supplies/) 从给定原材料中找到所有可以做出的菜 (M) · [1976](https://leetcode.cn/problems/number-of-ways-to-arrive-at-destination/) 到达目的地的方案数 (M)
- [1584](https://leetcode.cn/problems/min-cost-to-connect-all-points/) 连接所有点的最小费用 (M) · [1631](https://leetcode.cn/problems/path-with-minimum-effort/) 最小体力消耗路径 (M) · [778](https://leetcode.cn/problems/swim-in-rising-water/) 水位上升的泳池中游泳 (H)
- [1466](https://leetcode.cn/problems/reorder-routes-to-make-all-paths-lead-to-the-city-zero/) 重新规划路线 (M) · [1306](https://leetcode.cn/problems/jump-game-iii/) 跳跃游戏 III (M) · [1514](https://leetcode.cn/problems/path-with-maximum-probability/) 概率最大的路径 (M)

## 已完成题目

暂无。按计划完成后，把 `<题号>.<题目标题>.cpp` 放在本文件夹即可。
