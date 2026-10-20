# 05 · 栈与队列

> 对应计划：第 7 周（2026-11-30 ～ 2026-12-06）  
> 核心题量：18 题

## 本节目标

- 掌握栈的 LIFO 特性在括号匹配、表达式求值、路径简化中的应用。
- 掌握单调栈求「下一个更大/更小元素」及其变体。
- 掌握单调队列求窗口最值。
- 能用两个栈实现队列、用队列实现栈。

## 前置知识

### 1. STL 容器

```cpp
stack<int> st;      // push / pop / top / empty / size
queue<int> q;       // push / pop / front / back
deque<int> dq;      // push_back / pop_back / push_front / pop_front
```

- `stack` / `queue` 默认基于 `deque`。
- 需要随机访问或双端操作时直接用 `deque`。

### 2. 括号匹配

遇到左括号入栈，遇到右括号检查栈顶是否匹配。最后栈必须为空。

### 3. 单调栈

用于求每个元素左边/右边第一个更大/更小的元素。以「下一个更大元素」为例：

```text
从右往左遍历：
while 栈非空且栈顶 <= 当前元素: 弹出
栈顶就是下一个更大元素
当前元素入栈
```

栈内元素单调递减（从栈底到栈顶）。

### 4. 表达式求值

- 逆波兰表达式：遇到数字入栈，遇到运算符弹出两个数计算后入栈。
- 带括号/优先级的表达式：两个栈（数字栈 + 运算符栈），或递归下降。
- 只有加减和括号时，可以把括号展开成符号。

## 核心模板

### 有效的括号

```cpp
bool isValid(string s) {
    stack<char> st;
    for (char c : s) {
        if (c == '(' || c == '[' || c == '{') st.push(c);
        else {
            if (st.empty()) return false;
            char t = st.top(); st.pop();
            if ((c == ')' && t != '(') ||
                (c == ']' && t != '[') ||
                (c == '}' && t != '{')) return false;
        }
    }
    return st.empty();
}
```

### 下一个更大元素（单调栈）

```cpp
vector<int> nextGreater(vector<int>& a) {
    int n = a.size();
    vector<int> ans(n, -1);
    stack<int> st; // 存下标
    for (int i = n - 1; i >= 0; --i) {
        while (!st.empty() && a[st.top()] <= a[i]) st.pop();
        if (!st.empty()) ans[i] = a[st.top()];
        st.push(i);
    }
    return ans;
}
```

### 柱状图中最大的矩形

```cpp
int largestRectangleArea(vector<int>& h) {
    h.push_back(0); // 哨兵，保证最后全部弹出
    stack<int> st;  // 单调递增栈，存下标
    int ans = 0;
    for (int i = 0; i < (int)h.size(); ++i) {
        while (!st.empty() && h[st.top()] > h[i]) {
            int height = h[st.top()]; st.pop();
            int left = st.empty() ? -1 : st.top();
            ans = max(ans, height * (i - left - 1));
        }
        st.push(i);
    }
    return ans;
}
```

### 用栈实现队列

```cpp
class MyQueue {
    stack<int> in, out;
    void transfer() {
        if (out.empty())
            while (!in.empty()) { out.push(in.top()); in.pop(); }
    }
public:
    void push(int x) { in.push(x); }
    int pop() { transfer(); int x = out.top(); out.pop(); return x; }
    int peek() { transfer(); return out.top(); }
    bool empty() { return in.empty() && out.empty(); }
};
```

## 例题拆解

### 20. 有效的括号（Easy，已完成）

- 左括号入栈，右括号与栈顶匹配。
- 最后必须栈空；遇到右括号时栈空也是失败。
- 复杂度：时间 `O(n)`，空间 `O(n)`。

### 739. 每日温度（Medium）

- 单调栈存下标，栈内对应温度单调递减。
- 当前温度大于栈顶时，栈顶元素找到了答案，弹出并计算下标差。
- 复杂度：时间 `O(n)`，空间 `O(n)`。

### 84. 柱状图中最大的矩形（Hard）

- 对每根柱子，向左右扩展到第一个更矮的柱子，面积 = 高度 × 宽度。
- 单调递增栈；弹出时左边界是新栈顶，右边界是当前下标。
- 加哨兵 `0` 可以省略最后清空栈的循环。
- 复杂度：时间 `O(n)`，空间 `O(n)`。

### 224. 基本计算器（Hard）

- 两个栈：数字栈和运算符栈；遇到括号递归或压栈。
- 处理一元负号：在表达式开头或 `(` 后补 `0`，或维护 `sign`。
- 复杂度：时间 `O(n)`，空间 `O(n)`。

## 常见坑点

- 单调栈存值还是存下标：需要计算距离时必须存下标。
- 弹出条件用 `<` 还是 `<=`：取决于是否允许相等元素作为边界。
- 柱状图/最大矩形忘记加哨兵，最后栈中剩余元素没计算。
- 表达式求值中运算符优先级和结合性处理错误。
- 用两个栈实现队列时，`out` 非空不能把 `in` 倒进去，否则顺序错乱。
- 括号匹配只检查数量不检查类型，例如 `([)]` 会误判。

## 题目清单

### 第 7 周 · 栈与队列：括号、表达式、单调栈/队列（18 题）

- [155](https://leetcode.cn/problems/min-stack/) 最小栈 (M) · [32](https://leetcode.cn/problems/longest-valid-parentheses/) 最长有效括号 (H) · [224](https://leetcode.cn/problems/basic-calculator/) 基本计算器 (H)
- [394](https://leetcode.cn/problems/decode-string/) 字符串解码 (M) · [84](https://leetcode.cn/problems/largest-rectangle-in-histogram/) 柱状图中最大的矩形 (H) · [85](https://leetcode.cn/problems/maximal-rectangle/) 最大矩形 (H)
- [739](https://leetcode.cn/problems/daily-temperatures/) 每日温度 (M) · [232](https://leetcode.cn/problems/implement-queue-using-stacks/) 用栈实现队列 (E) · [225](https://leetcode.cn/problems/implement-stack-using-queues/) 用队列实现栈 (E)
- [150](https://leetcode.cn/problems/evaluate-reverse-polish-notation/) 逆波兰表达式求值 (M) · [402](https://leetcode.cn/problems/remove-k-digits/) 移掉 K 位数字 (M) · [316](https://leetcode.cn/problems/remove-duplicate-letters/) 去除重复字母 (M)
- [735](https://leetcode.cn/problems/asteroid-collision/) 小行星碰撞 (M) · [1047](https://leetcode.cn/problems/remove-all-adjacent-duplicates-in-string/) 删除字符串中的所有相邻重复项 (E) · [678](https://leetcode.cn/problems/valid-parenthesis-string/) 有效的括号字符串 (M)
- [581](https://leetcode.cn/problems/shortest-unsorted-continuous-subarray/) 最短无序连续子数组 (M) · [844](https://leetcode.cn/problems/backspace-string-compare/) 比较含退格的字符串 (E) · [496](https://leetcode.cn/problems/next-greater-element-i/) 下一个更大元素 I (E)

## 已完成题目

- [20.有效的括号.cpp](20.有效的括号.cpp)
