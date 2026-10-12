# daily-algorithm

每日算法练习记录，刷题过程中的解法与思路留档。

题目主要来自 [LeetCode](https://leetcode.cn/)，按题号命名文件，例如 `11.盛最多水的容器.cpp`。

## 目录约定

- 文件名格式：`<题号>.<题目标题>.cpp`
- 文件顶部保留 LeetCode 插件生成的 `@lc app=... id=... lang=cpp` 注释，便于与题号对应
- 代码位于 `// @lc code=start` 与 `// @lc code=end` 之间，可直接粘贴回提交

## 编译运行

```bash
c++ -std=c++17 -O0 -o /tmp/sol "11.盛最多水的容器.cpp" && /tmp/sol
```

单文件包含 `main` 时可直接编译；只有 `Solution` 类时需自行补测试代码。
