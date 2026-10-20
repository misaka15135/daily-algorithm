# 06 · 排序与二分

> 对应计划：第 8–9 周（2026-12-07 ～ 2026-12-20）  
> 核心题量：36 题

## 本节目标

- 能手写快速排序、归并排序、堆排序的核心部分。
- 掌握快速选择（Quickselect）求第 K 大/小。
- 掌握二分的三种写法：查找目标、查找边界、二分答案。
- 理解「二分答案」的单调性前提和 `check` 函数设计。

## 前置知识

### 1. 排序算法对比

| 算法 | 平均时间 | 最坏时间 | 空间 | 稳定性 |
| --- | --- | --- | --- | --- |
| 快速排序 | `O(n log n)` | `O(n²)` | `O(log n)` | 不稳定 |
| 归并排序 | `O(n log n)` | `O(n log n)` | `O(n)` | 稳定 |
| 堆排序 | `O(n log n)` | `O(n log n)` | `O(1)` | 不稳定 |
| 计数排序 | `O(n+k)` | `O(n+k)` | `O(k)` | 稳定 |

- 基于比较的排序下界是 `O(n log n)`。
- 计数/桶/基数排序适用于值域有限的整数。

### 2. 快速选择

Quickselect 用快排的 partition，但只递归包含第 K 个元素的一侧，平均 `O(n)`，最坏 `O(n²)`。面试中常用 `nth_element`。

### 3. 二分查找的两种区间

- 闭区间 `[l, r]`：循环条件 `l <= r`，更新 `l = mid + 1` / `r = mid - 1`。
- 左闭右开 `[l, r)`：循环条件 `l < r`，更新 `l = mid + 1` / `r = mid`。

写之前先确定区间，不要混用。

### 4. 二分答案

当答案具有单调性（`check(x)` 为真则 `x` 更大/更小也为真）时，二分答案：

```text
lo = 最小可能答案, hi = 最大可能答案
while lo < hi:
    mid = lo + (hi - lo) / 2
    if check(mid): hi = mid
    else: lo = mid + 1
return lo
```

## 核心模板

### 快速排序

```cpp
void quickSort(vector<int>& a, int l, int r) {
    if (l >= r) return;
    int pivot = a[l + (r - l) / 2];
    int i = l, j = r;
    while (i <= j) {
        while (a[i] < pivot) ++i;
        while (a[j] > pivot) --j;
        if (i <= j) swap(a[i++], a[j--]);
    }
    quickSort(a, l, j);
    quickSort(a, i, r);
}
```

### 归并排序（含逆序对计数）

```cpp
long long mergeCount(vector<int>& a, int l, int r) {
    if (l >= r) return 0;
    int m = l + (r - l) / 2;
    long long ans = mergeCount(a, l, m) + mergeCount(a, m + 1, r);
    vector<int> tmp;
    int i = l, j = m + 1;
    while (i <= m && j <= r) {
        if (a[i] <= a[j]) tmp.push_back(a[i++]);
        else { ans += m - i + 1; tmp.push_back(a[j++]); }
    }
    while (i <= m) tmp.push_back(a[i++]);
    while (j <= r) tmp.push_back(a[j++]);
    copy(tmp.begin(), tmp.end(), a.begin() + l);
    return ans;
}
```

### 二分查找：第一个 >= target

```cpp
int lowerBound(const vector<int>& a, int target) {
    int l = 0, r = a.size(); // [l, r)
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (a[mid] < target) l = mid + 1;
        else r = mid;
    }
    return l; // 可能等于 a.size()
}
```

### 二分答案：爱吃香蕉的珂珂

```cpp
int minEatingSpeed(vector<int>& piles, int h) {
    int lo = 1, hi = *max_element(piles.begin(), piles.end());
    auto check = [&](int k) {
        long long hours = 0;
        for (int p : piles) hours += (p + k - 1) / k;
        return hours <= h;
    };
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (check(mid)) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}
```

## 例题拆解

### 912. 排序数组（Medium）

- 面试手写快排/归并/堆排。
- 快排注意随机化 pivot，避免有序数组退化；归并注意临时数组和稳定合并。
- 复杂度：`O(n log n)`。

### 34. 在排序数组中查找元素的第一个和最后一个位置（Medium）

- 两次二分：第一个 `>= target`，第一个 `> target` 再减一。
- 检查 `lowerBound == n` 或 `a[lowerBound] != target`，返回 `{-1,-1}`。
- 复杂度：时间 `O(log n)`，空间 `O(1)`。

### 875. 爱吃香蕉的珂珂（Medium）

- 答案范围 `[1, max(piles)]`，`check(k)` 判断以速度 k 是否能在 h 小时内吃完。
- `check` 单调：速度越大，耗时越少。
- 复杂度：时间 `O(n log max)`，空间 `O(1)`。

### 315. 计算右侧小于当前元素的个数（Hard）

- 归并排序过程中统计逆序对：当右半元素先出队时，左半剩余元素都比它大。
- 需要把原下标一起归并，才能把答案写回原位置。
- 复杂度：时间 `O(n log n)`，空间 `O(n)`。

## 常见坑点

- `mid = (l + r) / 2` 在 `l + r` 溢出时出错，写成 `l + (r - l) / 2`。
- 闭区间写成左闭右开，或反过来，导致死循环/漏答案。
- 二分边界时没有检查越界和不等。
- 二分答案的 `check` 函数不是单调的，或 `lo/hi` 初始范围不对。
- 快排 partition 写法不统一，`i/j` 越界。
- 归并排序合并后忘记把临时数组写回原数组。
- `nth_element` 只保证第 K 个位置正确，左右不保证有序。

## 题目清单

### 第 8 周 · 排序：快排、归并、堆排序与快速选择（18 题）

- [912](https://leetcode.cn/problems/sort-an-array/) 排序数组 (M) · [148](https://leetcode.cn/problems/sort-list/) 排序链表 (M) · [215](https://leetcode.cn/problems/kth-largest-element-in-an-array/) 数组中的第K个最大元素 (M)
- [347](https://leetcode.cn/problems/top-k-frequent-elements/) 前 K 个高频元素 (M) · [973](https://leetcode.cn/problems/k-closest-points-to-origin/) 最接近原点的 K 个点 (M) · [2343](https://leetcode.cn/problems/query-kth-smallest-trimmed-number/) 裁剪数字后查询第 K 小的数字 (M)
- [2406](https://leetcode.cn/problems/divide-intervals-into-minimum-number-of-groups/) 将区间分为最少组数 (M) · [2491](https://leetcode.cn/problems/divide-players-into-teams-of-equal-skill/) 划分技能点相等的团队 (M) · [2602](https://leetcode.cn/problems/minimum-operations-to-make-all-array-elements-equal/) 使数组元素全部相等的最少操作次数 (M)
- [164](https://leetcode.cn/problems/maximum-gap/) 最大间距 (M) · [315](https://leetcode.cn/problems/count-of-smaller-numbers-after-self/) 计算右侧小于当前元素的个数 (H) · [493](https://leetcode.cn/problems/reverse-pairs/) 翻转对 (H)
- [1122](https://leetcode.cn/problems/relative-sort-array/) 数组的相对排序 (E) · [1365](https://leetcode.cn/problems/how-many-numbers-are-smaller-than-the-current-number/) 有多少小于当前数字的数字 (E) · [977](https://leetcode.cn/problems/squares-of-a-sorted-array/) 有序数组的平方 (E)
- [905](https://leetcode.cn/problems/sort-array-by-parity/) 按奇偶排序数组 (E) · [1636](https://leetcode.cn/problems/sort-array-by-increasing-frequency/) 按照频率将数组升序排序 (E) · [1913](https://leetcode.cn/problems/maximum-product-difference-between-two-pairs/) 两个数对之间的最大乘积差 (E)

### 第 9 周 · 二分查找：边界、旋转数组、二分答案（18 题）

- [4](https://leetcode.cn/problems/median-of-two-sorted-arrays/) 寻找两个正序数组的中位数 (H) · [33](https://leetcode.cn/problems/search-in-rotated-sorted-array/) 搜索旋转排序数组 (M) · [34](https://leetcode.cn/problems/find-first-and-last-position-of-element-in-sorted-array/) 在排序数组中查找元素的第一个和最后一个位置 (M)
- [35](https://leetcode.cn/problems/search-insert-position/) 搜索插入位置 (E) · [69](https://leetcode.cn/problems/sqrtx/) x 的平方根  (E) · [74](https://leetcode.cn/problems/search-a-2d-matrix/) 搜索二维矩阵 (M)
- [153](https://leetcode.cn/problems/find-minimum-in-rotated-sorted-array/) 寻找旋转排序数组中的最小值 (M) · [154](https://leetcode.cn/problems/find-minimum-in-rotated-sorted-array-ii/) 寻找旋转排序数组中的最小值 II (H) · [162](https://leetcode.cn/problems/find-peak-element/) 寻找峰值 (M)
- [240](https://leetcode.cn/problems/search-a-2d-matrix-ii/) 搜索二维矩阵 II (M) · [278](https://leetcode.cn/problems/first-bad-version/) 第一个错误的版本 (E) · [540](https://leetcode.cn/problems/single-element-in-a-sorted-array/) 有序数组中的单一元素 (M)
- [658](https://leetcode.cn/problems/find-k-closest-elements/) 找到 K 个最接近的元素 (M) · [704](https://leetcode.cn/problems/binary-search/) 二分查找 (E) · [744](https://leetcode.cn/problems/find-smallest-letter-greater-than-target/) 寻找比目标字母大的最小字母 (E)
- [875](https://leetcode.cn/problems/koko-eating-bananas/) 爱吃香蕉的珂珂 (M) · [1011](https://leetcode.cn/problems/capacity-to-ship-packages-within-d-days/) 在 D 天内送达包裹的能力 (M) · [1482](https://leetcode.cn/problems/minimum-number-of-days-to-make-m-bouquets/) 制作 m 束花所需的最少天数 (M)

## 已完成题目

暂无。按计划完成后，把 `<题号>.<题目标题>.cpp` 放在本文件夹即可。
