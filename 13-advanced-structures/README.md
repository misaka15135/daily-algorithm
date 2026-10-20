# 13 · 高级数据结构

> 对应计划：第 23 周（2027-03-22 ～ 2027-03-28）  
> 核心题量：18 题

## 本节目标

- 能手写并查集（路径压缩 + 按秩合并）。
- 掌握 Trie 的插入、查询、前缀匹配。
- 理解树状数组的 `lowbit` 和前缀和查询。
- 了解线段树的建树、区间查询、单点/区间更新。
- 知道 `ordered_set`（平衡树）在动态第 K 小/前驱后继中的应用。

## 前置知识

### 1. 并查集（DSU）

- 支持合并两个集合、查询两个元素是否同集合。
- `parent[x]` 指向父节点，根节点 `parent[x] == x`。
- 路径压缩：查询时把路径上的节点直接挂到根。
- 按秩/按大小合并：把较小的树挂到较大的树下，保证树高 `O(log n)`。
- 扩展域并查集：用于「敌人的敌人是朋友」、二分图判定。

### 2. Trie（前缀树）

- 每个节点有若干子节点和一个 `isEnd` 标记。
- 插入/查询都是 `O(L)`，`L` 是字符串长度。
- 子节点可用 `array<Trie*, 26>`（小写字母）或 `unordered_map<char, Trie*>`。
- 删除单词可以只把 `isEnd` 置 false，或维护计数。

### 3. 树状数组（BIT）

- 支持单点更新、前缀和查询，均为 `O(log n)`。
- `lowbit(x) = x & -x`。
- 更新：`for (i = x; i <= n; i += lowbit(i)) tree[i] += delta;`
- 查询：`for (i = x; i > 0; i -= lowbit(i)) sum += tree[i];`
- 下标从 1 开始。
- 区间和 = `query(r) - query(l-1)`。
- 配合离散化可以处理值域很大的问题。

### 4. 线段树

- 每个节点维护一个区间的信息（和、最大值、最小值等）。
- 单点更新/区间查询 `O(log n)`。
- 区间更新 + 区间查询需要懒标记（lazy propagation）。
- 递归实现更直观，注意数组开 `4n`。

### 5. 有序集合

- C++ 的 `std::set` 基于红黑树，支持 `lower_bound`、`upper_bound`、`erase`，`O(log n)`。
- 需要「第 K 小」时，`std::set` 不支持 `O(log n)` 排名；可用 PBDS 或树状数组/线段树。
- 滑动窗口中位数可以用两个 `multiset` 或对顶堆。

## 核心模板

### 并查集

```cpp
struct DSU {
    vector<int> p, sz;
    DSU(int n) : p(n), sz(n, 1) { iota(p.begin(), p.end(), 0); }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    bool join(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        p[b] = a;
        sz[a] += sz[b];
        return true;
    }
    bool same(int a, int b) { return find(a) == find(b); }
};
```

### Trie

```cpp
struct TrieNode {
    TrieNode* child[26] = {};
    bool isEnd = false;
};

class Trie {
    TrieNode* root = new TrieNode();
public:
    void insert(const string& s) {
        TrieNode* p = root;
        for (char c : s) {
            int i = c - 'a';
            if (!p->child[i]) p->child[i] = new TrieNode();
            p = p->child[i];
        }
        p->isEnd = true;
    }
    bool search(const string& s) {
        TrieNode* p = root;
        for (char c : s) {
            int i = c - 'a';
            if (!p->child[i]) return false;
            p = p->child[i];
        }
        return p->isEnd;
    }
    bool startsWith(const string& s) {
        TrieNode* p = root;
        for (char c : s) {
            int i = c - 'a';
            if (!p->child[i]) return false;
            p = p->child[i];
        }
        return true;
    }
};
```

### 树状数组

```cpp
struct BIT {
    int n;
    vector<long long> t;
    BIT(int n) : n(n), t(n + 1, 0) {}
    void add(int i, long long v) {
        for (; i <= n; i += i & -i) t[i] += v;
    }
    long long sum(int i) {
        long long s = 0;
        for (; i > 0; i -= i & -i) s += t[i];
        return s;
    }
    long long rangeSum(int l, int r) { return sum(r) - sum(l - 1); }
};
```

### 线段树（区间和 + 单点更新）

```cpp
struct SegTree {
    int n;
    vector<long long> t;
    SegTree(vector<int>& a) : n(a.size()), t(4 * n) { build(a, 1, 0, n - 1); }
    void build(vector<int>& a, int p, int l, int r) {
        if (l == r) { t[p] = a[l]; return; }
        int m = (l + r) / 2;
        build(a, p * 2, l, m);
        build(a, p * 2 + 1, m + 1, r);
        t[p] = t[p * 2] + t[p * 2 + 1];
    }
    void update(int p, int l, int r, int i, int v) {
        if (l == r) { t[p] = v; return; }
        int m = (l + r) / 2;
        if (i <= m) update(p * 2, l, m, i, v);
        else update(p * 2 + 1, m + 1, r, i, v);
        t[p] = t[p * 2] + t[p * 2 + 1];
    }
    long long query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return t[p];
        int m = (l + r) / 2;
        long long ans = 0;
        if (ql <= m) ans += query(p * 2, l, m, ql, qr);
        if (qr > m) ans += query(p * 2 + 1, m + 1, r, ql, qr);
        return ans;
    }
};
```

## 例题拆解

### 208. 实现 Trie（前缀树）（Medium）

- 插入：沿字符走，不存在就新建节点，最后标记 `isEnd`。
- 查询：走完返回 `isEnd`；前缀查询走完即可返回 true。
- 复杂度：插入/查询 `O(L)`，空间 `O(总字符数)`。

### 547. 省份数量（Medium）

- 并查集：遍历邻接矩阵，`isConnected[i][j] == 1` 就合并。
- 最后统计根节点数量。
- 复杂度：时间 `O(n² α(n))`，空间 `O(n)`。

### 684. 冗余连接（Medium）

- 并查集：按顺序加边，如果一条边的两个端点已经连通，这条边就是冗余边。
- 复杂度：时间 `O(n α(n))`，空间 `O(n)`。

### 307. 区域和检索 - 数组可修改（Medium）

- 树状数组或线段树：单点更新 + 区间和。
- 树状数组代码更短，注意下标从 1 开始。
- 复杂度：更新/查询 `O(log n)`，空间 `O(n)`。

### 315. 计算右侧小于当前元素的个数（Hard）

- 从右往左遍历，树状数组统计已出现的、比当前值小的元素个数。
- 值域需要离散化；或直接用归并排序（见 06 文件夹）。
- 复杂度：时间 `O(n log n)`，空间 `O(n)`。

## 常见坑点

- 并查集初始化忘记 `iota`，或 `find` 没有路径压缩。
- 按秩合并时把方向写反，导致树高退化。
- Trie 的 `child` 数组没有初始化为 `nullptr`。
- Trie 查询前缀和查询完整单词混淆（`isEnd`）。
- 树状数组下标从 0 开始，导致死循环；必须从 1 开始。
- 线段树数组只开 `2n`，递归越界；应开 `4n`。
- 线段树区间查询没有判断 `ql > qr` 或边界不重叠。
- 懒标记下传时忘记更新子节点和清空父节点标记。
- 离散化后忘记把查询值也映射到相同排名。

## 题目清单

### 第 23 周 · 高级结构：并查集、Trie、树状数组、线段树（18 题）

- [208](https://leetcode.cn/problems/implement-trie-prefix-tree/) 实现 Trie (前缀树) (M) · [211](https://leetcode.cn/problems/design-add-and-search-words-data-structure/) 添加与搜索单词 - 数据结构设计 (M) · [336](https://leetcode.cn/problems/palindrome-pairs/) 回文对 (H)
- [421](https://leetcode.cn/problems/maximum-xor-of-two-numbers-in-an-array/) 数组中两个数的最大异或值 (M) · [648](https://leetcode.cn/problems/replace-words/) 单词替换 (M) · [720](https://leetcode.cn/problems/longest-word-in-dictionary/) 词典中最长的单词 (M)
- [1268](https://leetcode.cn/problems/search-suggestions-system/) 搜索推荐系统 (M) · [745](https://leetcode.cn/problems/prefix-and-suffix-search/) 前缀和后缀搜索 (H) · [684](https://leetcode.cn/problems/redundant-connection/) 冗余连接 (M)
- [685](https://leetcode.cn/problems/redundant-connection-ii/) 冗余连接 II (H) · [721](https://leetcode.cn/problems/accounts-merge/) 账户合并 (M) · [765](https://leetcode.cn/problems/couples-holding-hands/) 情侣牵手 (H)
- [990](https://leetcode.cn/problems/satisfiability-of-equality-equations/) 等式方程的可满足性 (M) · [959](https://leetcode.cn/problems/regions-cut-by-slashes/) 由斜杠划分区域 (M) · [307](https://leetcode.cn/problems/range-sum-query-mutable/) 区域和检索 - 数组可修改 (M)
- [327](https://leetcode.cn/problems/count-of-range-sum/) 区间和的个数 (H) · [406](https://leetcode.cn/problems/queue-reconstruction-by-height/) 根据身高重建队列 (M) · [1395](https://leetcode.cn/problems/count-number-of-teams/) 统计作战单位数 (M)

## 已完成题目

暂无。按计划完成后，把 `<题号>.<题目标题>.cpp` 放在本文件夹即可。
