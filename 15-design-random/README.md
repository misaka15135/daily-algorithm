# 15 · 设计题与随机

> 对应计划：第 25 周（2027-04-05 ～ 2027-04-11）  
> 核心题量：18 题

## 本节目标

- 掌握 O(1) 设计题的常用组合：哈希表 + 双向链表、哈希表 + 数组。
- 能手写 LRU 与 LFU 缓存。
- 理解洗牌算法、水塘抽样、拒绝采样。
- 能用「前缀和 + 二分」实现按权重随机。

## 前置知识

### 1. 设计题的一般思路

1. 明确每个操作需要的时间复杂度。
2. 选择数据结构：哈希表负责 `O(1)` 查找，链表/数组负责顺序，堆负责最值。
3. 维护好「索引」与「实际存储」的映射。
4. 注意容量、空结构、重复元素等边界。

### 2. LRU 缓存

- 需要 `O(1)` 的 `get` 和 `put`。
- `unordered_map<int, list<pair<int,int>>::iterator>` + `list`。
- `get`：命中后把节点移到链表头。
- `put`：已存在则更新并移到头部；不存在则插入头部，超容量删除尾部。

### 3. LFU 缓存

- 每个 key 维护频率；需要按频率淘汰，频率相同淘汰最久未使用。
- 常用结构：`key -> {value, freq, iterator}` + `freq -> list<key>` + `minFreq`。
- 操作 `O(1)`。

### 4. 洗牌算法（Fisher-Yates）

```text
for i from n-1 down to 1:
    j = random(0..i)
    swap(a[i], a[j])
```

每个排列等概率。

### 5. 水塘抽样（Reservoir Sampling）

从未知长度的流中等概率抽取 k 个元素：

```text
前 k 个直接放入水库
第 i 个元素（i > k）以 k/i 的概率替换水库中随机一个
```

### 6. 拒绝采样

用 `Rand7()` 生成 `Rand10()`：用两个 `Rand7` 构造 `1..49`，拒绝 `41..49`，然后 `% 10 + 1`。

### 7. 按权重随机

前缀和 + 二分：`pre[i]` 表示前 i 个权重之和，随机 `[0, total)`，二分找到第一个 `pre[i] > target` 的下标。

## 核心模板

### LRU 缓存

```cpp
class LRUCache {
    int cap;
    list<pair<int,int>> lru; // front 最近使用
    unordered_map<int, list<pair<int,int>>::iterator> mp;
public:
    LRUCache(int capacity) : cap(capacity) {}
    int get(int key) {
        auto it = mp.find(key);
        if (it == mp.end()) return -1;
        lru.splice(lru.begin(), lru, it->second);
        return it->second->second;
    }
    void put(int key, int value) {
        auto it = mp.find(key);
        if (it != mp.end()) {
            it->second->second = value;
            lru.splice(lru.begin(), lru, it->second);
            return;
        }
        if ((int)lru.size() == cap) {
            mp.erase(lru.back().first);
            lru.pop_back();
        }
        lru.push_front({key, value});
        mp[key] = lru.begin();
    }
};
```

### 水塘抽样：链表随机节点

```cpp
class Solution {
    ListNode* head;
public:
    Solution(ListNode* h) : head(h) {}
    int getRandom() {
        int ans = head->val;
        ListNode* p = head->next;
        for (int i = 2; p; ++i, p = p->next)
            if (rand() % i == 0) ans = p->val; // 以 1/i 的概率替换
        return ans;
    }
};
```

### 拒绝采样：Rand7 -> Rand10

```cpp
int rand10() {
    while (true) {
        int x = (rand7() - 1) * 7 + rand7(); // 1..49
        if (x <= 40) return (x - 1) % 10 + 1;
    }
}
```

### 按权重随机选择

```cpp
class Solution {
    vector<int> pre;
public:
    Solution(vector<int>& w) {
        pre.resize(w.size());
        partial_sum(w.begin(), w.end(), pre.begin());
    }
    int pickIndex() {
        int x = rand() % pre.back() + 1; // 1..total
        return lower_bound(pre.begin(), pre.end(), x) - pre.begin();
    }
};
```

### 打乱数组

```cpp
vector<int> shuffle(vector<int>& a) {
    vector<int> b = a;
    for (int i = b.size() - 1; i > 0; --i)
        swap(b[i], b[rand() % (i + 1)]);
    return b;
}
```

## 例题拆解

### 146. LRU 缓存（Medium）

- 哈希表 + 双向链表，`get/put` 均 `O(1)`。
- `list::splice` 把节点移到头部，不用手动删除/插入。
- 容量为 0 时 `put` 直接返回。

### 460. LFU 缓存（Hard）

- 维护 `key -> (value, freq)` 和 `freq -> list<key>`。
- 每次访问频率 +1，从旧频率链表移到新频率链表头部。
- `minFreq` 在插入新 key 时置 1，在淘汰后更新。
- 操作 `O(1)`。

### 380. O(1) 时间插入、删除和获取随机元素（Medium）

- `vector` 存值，`unordered_map<value, index>` 存下标。
- 删除时把最后一个元素移到待删除位置，再 `pop_back`。
- 操作均摊 `O(1)`。

### 382. 链表随机节点（Medium）

- 水塘抽样：遍历到第 i 个节点时，以 `1/i` 的概率替换答案。
- 只需一次遍历，空间 `O(1)`。
- 期望时间 `O(n)`。

### 470. 用 Rand7() 实现 Rand10()（Medium）

- 两个 `Rand7` 构造 `1..49`，拒绝 `41..49` 后取模。
- 期望调用次数 `49/40`。

### 1515. 服务中心的最佳位置（Hard）

- 距离是凸函数，可以用梯度下降/三分搜索，或数学推导。
- 面试中了解「凸优化 + 迭代」即可。

## 常见坑点

- LRU 中 `get` 命中后忘记把节点移到头部。
- LRU 淘汰时忘记同时删除哈希表中的键。
- LFU 的 `minFreq` 没有正确更新，导致淘汰错误。
- O(1) 随机删除时，忘记更新被移动元素的下标。
- 洗牌算法从前往后遍历并用 `random(0..n-1)`，导致分布不均匀。
- 水塘抽样中概率写成 `1/n` 而不是 `1/i`。
- 按权重随机的前缀和二分边界：`rand() % total` 还是 `+1`。
- `rand()` 的最大值 `RAND_MAX` 可能不够，权重和很大时用 `mt19937`。
- 设计题没有处理容量为 0、重复 key、空结构等边界。

## 题目清单

### 第 25 周 · 设计题与随机：LRU/LFU、O(1) 设计、采样（18 题）

- [146](https://leetcode.cn/problems/lru-cache/) LRU 缓存 (M) · [460](https://leetcode.cn/problems/lfu-cache/) LFU 缓存 (H) · [380](https://leetcode.cn/problems/insert-delete-getrandom-o1/) O(1) 时间插入、删除和获取随机元素 (M)
- [381](https://leetcode.cn/problems/insert-delete-getrandom-o1-duplicates-allowed/) O(1) 时间插入、删除和获取随机元素 - 允许重复 (H) · [384](https://leetcode.cn/problems/shuffle-an-array/) 打乱数组 (M) · [470](https://leetcode.cn/problems/implement-rand10-using-rand7/) 用 Rand7() 实现 Rand10() (M)
- [382](https://leetcode.cn/problems/linked-list-random-node/) 链表随机节点 (M) · [398](https://leetcode.cn/problems/random-pick-index/) 随机数索引 (M) · [519](https://leetcode.cn/problems/random-flip-matrix/) 随机翻转矩阵 (M)
- [528](https://leetcode.cn/problems/random-pick-with-weight/) 按权重随机选择 (M) · [710](https://leetcode.cn/problems/random-pick-with-blacklist/) 黑名单中的随机数 (H) · [478](https://leetcode.cn/problems/generate-random-point-in-a-circle/) 在圆内随机生成点 (M)
- [497](https://leetcode.cn/problems/random-point-in-non-overlapping-rectangles/) 非重叠矩形中的随机点 (M) · [1515](https://leetcode.cn/problems/best-position-for-a-service-centre/) 服务中心的最佳位置 (H) · [706](https://leetcode.cn/problems/design-hashmap/) 设计哈希映射 (E)
- [535](https://leetcode.cn/problems/encode-and-decode-tinyurl/) TinyURL 的加密与解密 (M) · [341](https://leetcode.cn/problems/flatten-nested-list-iterator/) 扁平化嵌套列表迭代器 (M) · [981](https://leetcode.cn/problems/time-based-key-value-store/) 基于时间的键值存储 (M)

## 已完成题目

暂无。按计划完成后，把 `<题号>.<题目标题>.cpp` 放在本文件夹即可。
