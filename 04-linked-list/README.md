# 04 · 链表

> 对应计划：第 6 周（2026-11-23 ～ 2026-11-29）  
> 核心题量：18 题

## 本节目标

- 熟练掌握链表的遍历、插入、删除，尤其是哑结点技巧。
- 能手写链表反转、找中点、合并、删除倒数第 N 个。
- 理解快慢指针在环检测、找中点、找入环点中的应用。
- 掌握 K 个一组翻转的指针操作顺序。

## 前置知识

### 1. 链表节点

```cpp
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};
```

### 2. 哑结点（dummy）

在头结点可能被删除/修改时，创建一个 `dummy` 指向 `head`，最后返回 `dummy->next`。它能把「删除头结点」和「删除中间结点」统一处理。

### 3. 指针操作三要素

1. 先保存 `next`，再改指针；
2. 画图确认每一步的顺序；
3. 循环结束后检查 `nullptr`。

### 4. 快慢指针

- 找中点：`slow` 每次 1 步，`fast` 每次 2 步。
- 判环：相遇则有环。
- 找入环点：相遇后一个指针回到 `head`，两人同速前进，再次相遇即入环点。

## 核心模板

### 反转整条链表（迭代）

```cpp
ListNode* reverseList(ListNode* head) {
    ListNode* prev = nullptr;
    while (head) {
        ListNode* nxt = head->next;
        head->next = prev;
        prev = head;
        head = nxt;
    }
    return prev;
}
```

### 反转区间 [left, right]（一次遍历）

```cpp
ListNode* reverseBetween(ListNode* head, int left, int right) {
    ListNode dummy(0);
    dummy.next = head;
    ListNode* pre = &dummy;
    for (int i = 1; i < left; ++i) pre = pre->next;
    ListNode* cur = pre->next;
    for (int i = 0; i < right - left; ++i) {
        ListNode* nxt = cur->next;
        cur->next = nxt->next;
        nxt->next = pre->next;
        pre->next = nxt;
    }
    return dummy.next;
}
```

### 删除倒数第 N 个结点

```cpp
ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode dummy(0, head);
    ListNode *fast = &dummy, *slow = &dummy;
    for (int i = 0; i < n; ++i) fast = fast->next;
    while (fast->next) { fast = fast->next; slow = slow->next; }
    slow->next = slow->next->next;
    return dummy.next;
}
```

### 合并两个有序链表

```cpp
ListNode* mergeTwoLists(ListNode* a, ListNode* b) {
    ListNode dummy(0);
    ListNode* tail = &dummy;
    while (a && b) {
        if (a->val <= b->val) { tail->next = a; a = a->next; }
        else                  { tail->next = b; b = b->next; }
        tail = tail->next;
    }
    tail->next = a ? a : b;
    return dummy.next;
}
```

## 例题拆解

### 206. 反转链表（Easy）

- 三指针：`prev / cur / nxt`，每次先保存 `nxt` 再改 `cur->next`。
- 循环结束时 `prev` 是新头。
- 复杂度：时间 `O(n)`，空间 `O(1)`。

### 19. 删除链表的倒数第 N 个结点（Medium，已完成）

- 哑结点 + 快慢指针，快指针先走 N 步，然后两者同步前进。
- 快指针到最后一个结点时，慢指针正好在待删除结点的前一个。
- 复杂度：时间 `O(n)`，空间 `O(1)`。

### 25. K 个一组翻转链表（Hard，已完成）

- 先数出剩余长度，不足 K 个就保持原样。
- 对每一组做「头插法」反转，注意保存组前驱和组后继。
- 复杂度：时间 `O(n)`，空间 `O(1)`。

### 23. 合并 K 个升序链表（Hard，已完成，归档到 11-heap）

- 最小堆存每个链表当前头结点，每次弹出最小值接到结果尾部。
- 堆大小 K，时间复杂度 `O(N log K)`。
- 分治合并也能做到 `O(N log K)`，见 `06-sorting-binary-search`。

## 常见坑点

- 改指针前没有保存 `next`，导致链表断裂。
- 删除结点后没有 `delete`（LeetCode 不要求，但工程中要）。
- 快指针的循环条件写成 `fast->next`，在偶数长度时越界；应为 `fast && fast->next`。
- 哑结点是栈上对象时，返回 `dummy.next` 而不是 `&dummy`。
- K 个一组翻转时，组内反转后没有把 `pre->next` 接到新的组头。
- 环检测中 `fast` 初始化为 `head` 还是 `head->next`，会影响相遇判断，写之前先统一。

## 题目清单

### 第 6 周 · 链表：哑结点、快慢指针、反转与合并（18 题）

- [2](https://leetcode.cn/problems/add-two-numbers/) 两数相加 (M) · [206](https://leetcode.cn/problems/reverse-linked-list/) 反转链表 (E) · [92](https://leetcode.cn/problems/reverse-linked-list-ii/) 反转链表 II (M)
- [141](https://leetcode.cn/problems/linked-list-cycle/) 环形链表 (E) · [142](https://leetcode.cn/problems/linked-list-cycle-ii/) 环形链表 II (M) · [234](https://leetcode.cn/problems/palindrome-linked-list/) 回文链表 (E)
- [160](https://leetcode.cn/problems/intersection-of-two-linked-lists/) 相交链表 (E) · [138](https://leetcode.cn/problems/copy-list-with-random-pointer/) 随机链表的复制 (M) · [143](https://leetcode.cn/problems/reorder-list/) 重排链表 (M)
- [82](https://leetcode.cn/problems/remove-duplicates-from-sorted-list-ii/) 删除排序链表中的重复元素 II (M) · [83](https://leetcode.cn/problems/remove-duplicates-from-sorted-list/) 删除排序链表中的重复元素 (E) · [203](https://leetcode.cn/problems/remove-linked-list-elements/) 移除链表元素 (E)
- [445](https://leetcode.cn/problems/add-two-numbers-ii/) 两数相加 II (M) · [876](https://leetcode.cn/problems/middle-of-the-linked-list/) 链表的中间结点 (E) · [86](https://leetcode.cn/problems/partition-list/) 分隔链表 (M)
- [61](https://leetcode.cn/problems/rotate-list/) 旋转链表 (M) · [328](https://leetcode.cn/problems/odd-even-linked-list/) 奇偶链表 (M) · [237](https://leetcode.cn/problems/delete-node-in-a-linked-list/) 删除链表中的节点 (M)

## 已完成题目

- [19.删除链表的倒数第-n-个结点.cpp](19.删除链表的倒数第-n-个结点.cpp)
- [21.合并两个有序链表.cpp](21.合并两个有序链表.cpp)
- [24.两两交换链表中的节点.cpp](24.两两交换链表中的节点.cpp)
- [25.k-个一组翻转链表.cpp](25.k-个一组翻转链表.cpp)
