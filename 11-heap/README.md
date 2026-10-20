# 11 · 堆与优先队列

> 对应计划：第 20 周（2027-03-01 ～ 2027-03-07）  
> 核心题量：18 题

## 本节目标

- 理解堆的完全二叉树结构和上浮/下沉操作。
- 熟练使用 `priority_queue` 解决 Top K、数据流中位数、多路归并。
- 掌握「两个堆」维护动态中位数。
- 知道 Quickselect 与堆在 Top K 问题上的取舍。

## 前置知识

### 1. 堆的性质

- 大根堆：父节点 >= 子节点；小根堆：父节点 <= 子节点。
- 完全二叉树，用数组存储：`children(i) = 2i+1, 2i+2`，`parent(i) = (i-1)/2`。
- 插入：放到末尾后上浮，`O(log n)`。
- 删除堆顶：末尾元素换到堆顶后下沉，`O(log n)`。
- 建堆：从最后一个非叶子节点向前下沉，`O(n)`。

### 2. C++ `priority_queue`

```cpp
priority_queue<int> maxHeap;                              // 默认大根堆
priority_queue<int, vector<int>, greater<int>> minHeap;  // 小根堆
priority_queue<pair<int,int>> pq;                        // 按 first 再按 second
```

自定义比较器：

```cpp
auto cmp = [](const ListNode* a, const ListNode* b) {
    return a->val > b->val; // 返回 true 表示 a 的优先级更低
};
priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> pq(cmp);
```

### 3. Top K 的两种做法

| 做法 | 时间 | 适用 |
| --- | --- | --- |
| 小根堆放 K 个元素 | `O(n log k)` | 数据流、内存受限 |
| Quickselect | 平均 `O(n)` | 静态数组、允许修改 |

### 4. 两个堆维护中位数

- 大根堆放较小的一半，小根堆放较大的一半。
- 保证 `maxHeap.size() == minHeap.size()` 或 `maxHeap.size() == minHeap.size() + 1`。
- 中位数：奇数个取大根堆顶；偶数个取两个堆顶平均。

## 核心模板

### Top K 大元素（小根堆）

```cpp
int findKthLargest(vector<int>& a, int k) {
    priority_queue<int, vector<int>, greater<int>> pq; // 小根堆
    for (int x : a) {
        pq.push(x);
        if ((int)pq.size() > k) pq.pop();
    }
    return pq.top();
}
```

### 前 K 个高频元素

```cpp
vector<int> topKFrequent(vector<int>& a, int k) {
    unordered_map<int,int> cnt;
    for (int x : a) ++cnt[x];
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
    for (auto& [x, c] : cnt) {
        pq.push({c, x});
        if ((int)pq.size() > k) pq.pop();
    }
    vector<int> ans;
    while (!pq.empty()) { ans.push_back(pq.top().second); pq.pop(); }
    return ans;
}
```

### 数据流的中位数

```cpp
class MedianFinder {
    priority_queue<int> lo;                              // 大根堆
    priority_queue<int, vector<int>, greater<int>> hi;   // 小根堆
public:
    void addNum(int x) {
        lo.push(x);
        hi.push(lo.top()); lo.pop();
        if (hi.size() > lo.size()) { lo.push(hi.top()); hi.pop(); }
    }
    double findMedian() {
        if (lo.size() > hi.size()) return lo.top();
        return (lo.top() + hi.top()) / 2.0;
    }
};
```

### 多路归并：合并 K 个升序链表

```cpp
ListNode* mergeKLists(vector<ListNode*>& lists) {
    auto cmp = [](ListNode* a, ListNode* b) { return a->val > b->val; };
    priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> pq(cmp);
    for (ListNode* p : lists) if (p) pq.push(p);
    ListNode dummy(0);
    ListNode* tail = &dummy;
    while (!pq.empty()) {
        ListNode* p = pq.top(); pq.pop();
        tail->next = p;
        tail = tail->next;
        if (p->next) pq.push(p->next);
    }
    return dummy.next;
}
```

## 例题拆解

### 215. 数组中的第 K 个最大元素（Medium）

- 小根堆维护 K 个最大的数，堆顶就是第 K 大。
- 复杂度：时间 `O(n log k)`，空间 `O(k)`。
- 进阶：Quickselect 平均 `O(n)`，但最坏 `O(n²)`。

### 347. 前 K 个高频元素（Medium）

- 先用哈希表计数，再用小根堆维护频率最高的 K 个。
- 复杂度：时间 `O(n log k)`，空间 `O(n)`。

### 295. 数据流的中位数（Hard）

- 两个堆，大根堆放较小一半，小根堆放较大一半。
- 每次插入后调整两个堆的大小关系。
- 复杂度：插入 `O(log n)`，查询 `O(1)`。

### 23. 合并 K 个升序链表（Hard，已完成）

- 最小堆存每个链表当前头结点，每次弹出全局最小值。
- 复杂度：时间 `O(N log K)`，空间 `O(K)`。
- 也可以用分治合并，复杂度相同。

### 407. 接雨水 II（Hard）

- 从边界开始 BFS，用最小堆放当前最矮的边界。
- 每次弹出最矮的格子，向四周扩展，水位取 `max(当前高度, 当前水位)`。
- 复杂度：时间 `O(mn log(mn))`，空间 `O(mn)`。

## 常见坑点

- `priority_queue` 默认是大根堆，求第 K 大要用小根堆。
- 自定义比较器返回 `true` 表示「优先级更低」，方向容易写反。
- 堆中存了已失效的元素（如 Dijkstra 的旧距离），需要懒删除。
- 多路归并时忘了先把每个链表的头结点入堆。
- 两个堆调整后大小关系不满足，导致中位数计算错误。
- Top K 问题中 `k > n` 或 `k <= 0` 的边界没有处理。
- 堆的 `pop()` 不会返回元素，要先 `top()` 再 `pop()`。

## 题目清单

### 第 20 周 · 堆与优先队列：Top K、数据流、多路归并（18 题）

- [295](https://leetcode.cn/problems/find-median-from-data-stream/) 数据流的中位数 (H) · [692](https://leetcode.cn/problems/top-k-frequent-words/) 前K个高频单词 (M) · [218](https://leetcode.cn/problems/the-skyline-problem/) 天际线问题 (H)
- [378](https://leetcode.cn/problems/kth-smallest-element-in-a-sorted-matrix/) 有序矩阵中第 K 小的元素 (M) · [407](https://leetcode.cn/problems/trapping-rain-water-ii/) 接雨水 II (H) · [703](https://leetcode.cn/problems/kth-largest-element-in-a-stream/) 数据流中的第 K 大元素 (E)
- [767](https://leetcode.cn/problems/reorganize-string/) 重构字符串 (M) · [264](https://leetcode.cn/problems/ugly-number-ii/) 丑数 II (M) · [1046](https://leetcode.cn/problems/last-stone-weight/) 最后一块石头的重量 (E)
- [1353](https://leetcode.cn/problems/maximum-number-of-events-that-can-be-attended/) 最多可以参加的会议数目 (M) · [1383](https://leetcode.cn/problems/maximum-performance-of-a-team/) 最大的团队表现值 (H) · [1705](https://leetcode.cn/problems/maximum-number-of-eaten-apples/) 吃苹果的最大数目 (M)
- [1792](https://leetcode.cn/problems/maximum-average-pass-ratio/) 最大平均通过率 (M) · [1834](https://leetcode.cn/problems/single-threaded-cpu/) 单线程 CPU (M) · [1882](https://leetcode.cn/problems/process-tasks-using-servers/) 使用服务器处理任务 (M)
- [2141](https://leetcode.cn/problems/maximum-running-time-of-n-computers/) 同时运行 N 台电脑的最长时间 (H) · [2208](https://leetcode.cn/problems/minimum-operations-to-halve-array-sum/) 将数组和减半的最少操作次数 (M) · [2462](https://leetcode.cn/problems/total-cost-to-hire-k-workers/) 雇佣 K 位工人的总代价 (M)

## 已完成题目

- [23.合并-k-个升序链表.cpp](23.合并-k-个升序链表.cpp)
