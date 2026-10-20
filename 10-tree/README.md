# 10 · 树

> 对应计划：第 17–19 周（2027-02-08 ～ 2027-02-28）  
> 核心题量：54 题

## 本节目标

- 熟练掌握二叉树的前/中/后序递归与迭代遍历、层序遍历。
- 能根据两种遍历序列构造二叉树。
- 掌握二叉搜索树的性质：中序遍历有序。
- 掌握最近公共祖先、路径问题、树形 DP。
- 能手写序列化/反序列化。

## 前置知识

### 1. 二叉树节点

```cpp
struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
```

### 2. 四种遍历

| 遍历 | 顺序 | 用途 |
| --- | --- | --- |
| 前序 | 根 → 左 → 右 | 复制树、序列化 |
| 中序 | 左 → 根 → 右 | BST 得到有序序列 |
| 后序 | 左 → 右 → 根 | 自底向上计算（高度、直径、树形 DP） |
| 层序 | 逐层从左到右 | 最短路径、右视图、层内统计 |

### 3. 递归遍历的「思考位置」

- 前序位置：刚进入节点，适合自顶向下传参。
- 后序位置：左右子树处理完，适合自底向上返回值。
- 中序位置：左子树处理完，适合 BST。

### 4. 二叉搜索树（BST）

- 左子树所有节点 < 根 < 右子树所有节点。
- 中序遍历严格递增。
- 验证 BST 不能只比较父子，要传 `(min, max)` 区间。
- 删除节点分三种情况：叶子、只有一个孩子、有两个孩子（用后继/前驱替换）。

### 5. 最近公共祖先（LCA）

- 普通二叉树：后序遍历，左右子树分别找到目标则当前节点是 LCA；否则返回非空的一侧。
- BST：利用值的大小关系，从根向下走。

### 6. 构造二叉树

- 前序 + 中序：前序第一个是根，在中序中找到根的位置划分左右。
- 中序 + 后序：后序最后一个是根。
- 前序 + 后序：不唯一，除非是满二叉树。

## 核心模板

### 中序遍历（递归）

```cpp
void inorder(TreeNode* u, vector<int>& ans) {
    if (!u) return;
    inorder(u->left, ans);
    ans.push_back(u->val);
    inorder(u->right, ans);
}
```

### 中序遍历（迭代）

```cpp
vector<int> inorderTraversal(TreeNode* root) {
    vector<int> ans;
    stack<TreeNode*> st;
    TreeNode* cur = root;
    while (cur || !st.empty()) {
        while (cur) { st.push(cur); cur = cur->left; }
        cur = st.top(); st.pop();
        ans.push_back(cur->val);
        cur = cur->right;
    }
    return ans;
}
```

### 层序遍历

```cpp
vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> ans;
    if (!root) return ans;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        int sz = q.size(); // 先固定当前层大小
        vector<int> level;
        for (int i = 0; i < sz; ++i) {
            TreeNode* u = q.front(); q.pop();
            level.push_back(u->val);
            if (u->left) q.push(u->left);
            if (u->right) q.push(u->right);
        }
        ans.push_back(level);
    }
    return ans;
}
```

### 验证二叉搜索树

```cpp
bool valid(TreeNode* u, long long lo, long long hi) {
    if (!u) return true;
    if (u->val <= lo || u->val >= hi) return false;
    return valid(u->left, lo, u->val) && valid(u->right, u->val, hi);
}
bool isValidBST(TreeNode* root) {
    return valid(root, LLONG_MIN, LLONG_MAX);
}
```

### 最近公共祖先

```cpp
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root || root == p || root == q) return root;
    TreeNode* l = lowestCommonAncestor(root->left, p, q);
    TreeNode* r = lowestCommonAncestor(root->right, p, q);
    if (l && r) return root;
    return l ? l : r;
}
```

### 从前序与中序遍历构造二叉树

```cpp
TreeNode* build(vector<int>& pre, int pl, int pr,
                vector<int>& in, int il, int ir,
                unordered_map<int,int>& pos) {
    if (pl > pr) return nullptr;
    int rootVal = pre[pl];
    int k = pos[rootVal];
    int leftSize = k - il;
    TreeNode* root = new TreeNode(rootVal);
    root->left = build(pre, pl + 1, pl + leftSize, in, il, k - 1, pos);
    root->right = build(pre, pl + leftSize + 1, pr, in, k + 1, ir, pos);
    return root;
}
```

## 例题拆解

### 94. 二叉树的中序遍历（Easy）

- 递归最简单；迭代用显式栈，先一路向左入栈，再弹出访问，再转向右子树。
- 复杂度：时间 `O(n)`，空间 `O(h)`。

### 102. 二叉树的层序遍历（Medium）

- 队列实现 BFS，每轮先记录 `sz = q.size()`，保证按层分组。
- 复杂度：时间 `O(n)`，空间 `O(w)`（w 为最大层宽）。

### 236. 二叉树的最近公共祖先（Medium）

- 后序遍历：左右子树都找到目标，当前节点就是 LCA。
- 如果只有一个子树找到，返回那个子树的结果。
- 复杂度：时间 `O(n)`，空间 `O(h)`。

### 98. 验证二叉搜索树（Medium）

- 不能只比较 `left->val < root->val < right->val`，因为 BST 要求整棵子树满足区间约束。
- 递归传 `(lo, hi)`，或用中序遍历检查严格递增。
- 复杂度：时间 `O(n)`，空间 `O(h)`。

### 105. 从前序与中序遍历序列构造二叉树（Medium）

- 前序第一个是根，用哈希表记录中序中每个值的位置，`O(1)` 定位。
- 递归划分左右子树区间。
- 复杂度：时间 `O(n)`，空间 `O(n)`。

### 297. 二叉树的序列化与反序列化（Hard）

- 前序遍历 + `nullptr` 标记，序列化成字符串。
- 反序列化按同样顺序递归消费。
- 层序遍历也可以，注意空节点标记。

## 常见坑点

- 层序遍历没有先固定 `sz`，导致同一层和下一层混在一起。
- 验证 BST 只比较父子节点。
- LCA 中 `p`/`q` 可能不在树中；题目通常保证存在。
- 构造二叉树时中序位置映射没有预处理，导致 `O(n²)`。
- 递归函数返回值与全局答案混用：直径、最大路径和需要在后序位置更新全局变量。
- 序列化时没有处理空节点，反序列化无法还原结构。
- BST 删除节点时，用右子树最小节点替换后忘记删除后继。
- 递归深度过大导致栈溢出（链状树），迭代遍历更安全。

## 题目清单

### 第 17 周 · 二叉树 I：四种遍历、层序、路径与深度（18 题）

- [94](https://leetcode.cn/problems/binary-tree-inorder-traversal/) 二叉树的中序遍历 (E) · [144](https://leetcode.cn/problems/binary-tree-preorder-traversal/) 二叉树的前序遍历 (E) · [145](https://leetcode.cn/problems/binary-tree-postorder-traversal/) 二叉树的后序遍历 (E)
- [102](https://leetcode.cn/problems/binary-tree-level-order-traversal/) 二叉树的层序遍历 (M) · [103](https://leetcode.cn/problems/binary-tree-zigzag-level-order-traversal/) 二叉树的锯齿形层序遍历 (M) · [107](https://leetcode.cn/problems/binary-tree-level-order-traversal-ii/) 二叉树的层序遍历 II (M)
- [104](https://leetcode.cn/problems/maximum-depth-of-binary-tree/) 二叉树的最大深度 (E) · [111](https://leetcode.cn/problems/minimum-depth-of-binary-tree/) 二叉树的最小深度 (E) · [226](https://leetcode.cn/problems/invert-binary-tree/) 翻转二叉树 (E)
- [101](https://leetcode.cn/problems/symmetric-tree/) 对称二叉树 (E) · [110](https://leetcode.cn/problems/balanced-binary-tree/) 平衡二叉树 (E) · [112](https://leetcode.cn/problems/path-sum/) 路径总和 (E)
- [113](https://leetcode.cn/problems/path-sum-ii/) 路径总和 II (M) · [257](https://leetcode.cn/problems/binary-tree-paths/) 二叉树的所有路径 (E) · [199](https://leetcode.cn/problems/binary-tree-right-side-view/) 二叉树的右视图 (M)
- [637](https://leetcode.cn/problems/average-of-levels-in-binary-tree/) 二叉树的层平均值 (E) · [429](https://leetcode.cn/problems/n-ary-tree-level-order-traversal/) N 叉树的层序遍历 (M) · [559](https://leetcode.cn/problems/maximum-depth-of-n-ary-tree/) N 叉树的最大深度 (E)

### 第 18 周 · 二叉树 II：构造、序列化、公共祖先、直径（18 题）

- [105](https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-inorder-traversal/) 从前序与中序遍历序列构造二叉树 (M) · [106](https://leetcode.cn/problems/construct-binary-tree-from-inorder-and-postorder-traversal/) 从中序与后序遍历序列构造二叉树 (M) · [108](https://leetcode.cn/problems/convert-sorted-array-to-binary-search-tree/) 将有序数组转换为二叉搜索树 (E)
- [109](https://leetcode.cn/problems/convert-sorted-list-to-binary-search-tree/) 有序链表转换二叉搜索树 (M) · [114](https://leetcode.cn/problems/flatten-binary-tree-to-linked-list/) 二叉树展开为链表 (M) · [116](https://leetcode.cn/problems/populating-next-right-pointers-in-each-node/) 填充每个节点的下一个右侧节点指针 (M)
- [117](https://leetcode.cn/problems/populating-next-right-pointers-in-each-node-ii/) 填充每个节点的下一个右侧节点指针 II (M) · [124](https://leetcode.cn/problems/binary-tree-maximum-path-sum/) 二叉树中的最大路径和 (H) · [236](https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-tree/) 二叉树的最近公共祖先 (M)
- [235](https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-search-tree/) 二叉搜索树的最近公共祖先 (M) · [297](https://leetcode.cn/problems/serialize-and-deserialize-binary-tree/) 二叉树的序列化与反序列化 (H) · [449](https://leetcode.cn/problems/serialize-and-deserialize-bst/) 序列化和反序列化二叉搜索树 (M)
- [543](https://leetcode.cn/problems/diameter-of-binary-tree/) 二叉树的直径 (E) · [687](https://leetcode.cn/problems/longest-univalue-path/) 最长同值路径 (M) · [513](https://leetcode.cn/problems/find-bottom-left-tree-value/) 找树左下角的值 (M)
- [515](https://leetcode.cn/problems/find-largest-value-in-each-tree-row/) 在每个树行中找最大值 (M) · [623](https://leetcode.cn/problems/add-one-row-to-tree/) 在二叉树中增加一行 (M) · [652](https://leetcode.cn/problems/find-duplicate-subtrees/) 寻找重复的子树 (M)

### 第 19 周 · 二叉搜索树与树形 DP（18 题）

- [98](https://leetcode.cn/problems/validate-binary-search-tree/) 验证二叉搜索树 (M) · [230](https://leetcode.cn/problems/kth-smallest-element-in-a-bst/) 二叉搜索树中第 K 小的元素 (M) · [450](https://leetcode.cn/problems/delete-node-in-a-bst/) 删除二叉搜索树中的节点 (M)
- [701](https://leetcode.cn/problems/insert-into-a-binary-search-tree/) 二叉搜索树中的插入操作 (M) · [700](https://leetcode.cn/problems/search-in-a-binary-search-tree/) 二叉搜索树中的搜索 (E) · [938](https://leetcode.cn/problems/range-sum-of-bst/) 二叉搜索树的范围和 (E)
- [530](https://leetcode.cn/problems/minimum-absolute-difference-in-bst/) 二叉搜索树的最小绝对差 (E) · [501](https://leetcode.cn/problems/find-mode-in-binary-search-tree/) 二叉搜索树中的众数 (E) · [99](https://leetcode.cn/problems/recover-binary-search-tree/) 恢复二叉搜索树 (M)
- [96](https://leetcode.cn/problems/unique-binary-search-trees/) 不同的二叉搜索树 (M) · [173](https://leetcode.cn/problems/binary-search-tree-iterator/) 二叉搜索树迭代器 (M) · [1008](https://leetcode.cn/problems/construct-binary-search-tree-from-preorder-traversal/) 前序遍历构造二叉搜索树 (M)
- [1305](https://leetcode.cn/problems/all-elements-in-two-binary-search-trees/) 两棵二叉搜索树中的所有元素 (M) · [783](https://leetcode.cn/problems/minimum-distance-between-bst-nodes/) 二叉搜索树节点最小距离 (E) · [1373](https://leetcode.cn/problems/maximum-sum-bst-in-binary-tree/) 二叉搜索子树的最大键值和 (H)
- [653](https://leetcode.cn/problems/two-sum-iv-input-is-a-bst/) 两数之和 IV - 输入二叉搜索树 (E) · [863](https://leetcode.cn/problems/all-nodes-distance-k-in-binary-tree/) 二叉树中所有距离为 K 的结点 (M) · [987](https://leetcode.cn/problems/vertical-order-traversal-of-a-binary-tree/) 二叉树的垂序遍历 (H)

## 已完成题目

暂无。按计划完成后，把 `<题号>.<题目标题>.cpp` 放在本文件夹即可。
