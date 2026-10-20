# daily-algorithm

每日算法练习记录，刷题过程中的解法与思路留档。

题目主要来自 [LeetCode](https://leetcode.cn/)，按题号命名文件，并按分类归档到对应文件夹。

## 刷题计划

完整的 26 周、每天 3 题日程见 [plan.md](plan.md)。

**进度**：已完成 22 道；计划内新题 468 道。

## 目录结构

```text
.
├── plan.md                       # 26 周每日刷题计划（含题号）
├── 01-array-hash/                # 数组与哈希
├── 02-string-two-pointers/       # 字符串与双指针
├── 03-sliding-window/            # 滑动窗口
├── 04-linked-list/               # 链表
├── 05-stack-queue/               # 栈与队列
├── 06-sorting-binary-search/     # 排序与二分
├── 07-recursion-backtracking/    # 递归与回溯
├── 08-greedy/                    # 贪心
├── 09-dynamic-programming/       # 动态规划
├── 10-tree/                      # 树
├── 11-heap/                      # 堆与优先队列
├── 12-graph/                     # 图论
├── 13-advanced-structures/       # 高级数据结构
├── 14-math-bit/                  # 数学与位运算
├── 15-design-random/             # 设计题与随机
└── 16-special-algorithms/        # 特殊算法
```

每个分类文件夹内有一份 `README.md`，包含该类别的**前置知识、核心模板、例题拆解、常见坑点**和题目清单。

## 文件约定

- 文件名格式：`<题号>.<题目标题>.cpp`
- 文件放在题目主分类对应的文件夹中；跨类别题目在分类 README 中做交叉引用。
- 文件顶部保留 LeetCode 插件生成的 `@lc app=... id=... lang=cpp` 注释，便于与题号对应。
- 代码位于 `// @lc code=start` 与 `// @lc code=end` 之间，可直接粘贴回提交。

## 编译运行

```bash
c++ -std=c++17 -O0 -o /tmp/sol "01-array-hash/31.下一个排列.cpp" && /tmp/sol
```

单文件包含 `main` 时可直接编译；只有 `Solution` 类时需自行补测试代码。

## 提交约定

```text
10.19: [数组] 3m
```

每天提交一次，每周日更新本文件的进度。
