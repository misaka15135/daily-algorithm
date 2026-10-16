/*
 * @lc app=leetcode.cn id=24 lang=cpp
 *
 * [24] 两两交换链表中的节点
 */

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if (!head) return head;
        if (!head->next) return head;

        ListNode dummy(0);
        ListNode* back = &dummy;
        ListNode* result = &dummy;

        ListNode* temp = head->next;
        head->next = temp->next;
        temp->next = head;
        result->next = temp;

        while (head->next) {
            if ((auto temp1 = head->next->next) != nullptr) {
                head->next->next = temp1->next;
                temp1->next = head->next;
                head->next=temp1;
                head=head->next->next;
            }else break;

        }

        return back->next;
    }
};

// note
/*
## 二、`if` 条件里「赋值」和「声明」的区别

```cpp
ListNode* temp;                                  // 声明
if ((temp = head->next->next) != nullptr) { }    // ✅ 赋值表达式
if ((auto temp = head->next->next) != nullptr)   // ❌ 语法错误
```

**根本原因：C++ 里声明不是表达式。** `auto` 是占位类型说明符，本身没有值，不能成为表达式的一部分。编译器在期望表达式的位置看到 `auto`，直接报错（gcc: `expected primary-expression before 'auto'`）。

`if` 的条件（`condition`）文法上只有两种合法形式：

1. **一个表达式** —— `if (expr)`
2. **一整个声明** —— `if (T x = expr)`，必须占满整个条件

第 2 种是专为「声明 + 判断」开的特例产生式，**不能加括号，也不能拼接 `!= nullptr`**。所以 `(auto temp = ...) != nullptr` 两边都不占：既不是表达式（含声明），也不是那个特例声明（被包住了）。

### 相关现象

- 声明形式里写不了显式比较：`if (auto x = expr != nullptr)` 会被解析成 `auto x = (expr != nullptr)`，`x` 被推导成 `bool`。声明形式只能靠指针到 `bool` 的隐式转换判断空。
- `auto temp;` 单独写也是错的：`auto` 是占位符，必须有初始化器才能推导。
- **优先级**：`=` 低于 `!=`，所以 `(temp = x) != nullptr` 的括号是必须的。漏了会变成 `temp = (x != nullptr)` —— 把 `bool` 赋给指针（`true` → 非法地址 1），是 UB。这也是很多代码规范要求「条件中赋值」套括号、编译器有 `-Wparentheses` 警告的原因。

### 推荐写法

```cpp
if (auto temp1 = head->next->next) { ... }        // 声明式条件，最简洁，temp1 作用域限于 if
if (auto temp1 = expr; temp1 != nullptr) { ... }  // C++17 if-init：分号前是初始化语句，后面才是条件
```

变量需要在 `if` 外跨轮次复用时，才用「外层声明 + 条件里赋值」的老写法。

*/
// @lc code=end

