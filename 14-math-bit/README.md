# 14 · 数学与位运算

> 对应计划：第 24 周（2027-03-29 ～ 2027-04-04）  
> 核心题量：18 题

## 本节目标

- 掌握常见位运算技巧：判断 2 的幂、统计 1 的个数、异或消对。
- 能手写快速幂、最大公约数、埃氏筛。
- 理解二进制补码、移位、溢出。
- 能处理整数反转、回文数、进制转换等数学模拟题。

## 前置知识

### 1. 位运算

```text
a & b   按位与
a | b   按位或
a ^ b   按位异或
~a      按位取反
a << k  左移 k 位（等价于乘 2^k）
a >> k  右移 k 位（算术右移，保留符号）
```

- `x & (x - 1)` 去掉最低位的 1。
- `x & -x` 取出最低位的 1（lowbit）。
- `x ^ x = 0`，`x ^ 0 = x`。
- 异或满足交换律、结合律；一排数中只有一个出现奇数次时，全部异或即可。

### 2. 补码

- `int` 通常是 32 位有符号，范围 `[-2^31, 2^31-1]`。
- 负数右移是算术右移，高位补 1；无符号右移用 `unsigned`。
- `INT_MIN` 取相反数会溢出，需要特殊处理。

### 3. 快速幂

```text
x^n:
    if n == 0: return 1
    half = x^(n/2)
    return half * half * (n%2 ? x : 1)
```

迭代写法：

```text
ans = 1
while n:
    if n & 1: ans *= x
    x *= x
    n >>= 1
```

### 4. 最大公约数/最小公倍数

```cpp
int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }
int lcm(int a, int b) { return a / gcd(a, b) * b; } // 先除后乘防溢出
```

### 5. 质数筛

埃氏筛：从 2 开始，把每个质数的倍数标记为合数，`O(n log log n)`。线性筛可以做到 `O(n)`。

### 6. 常见数学结论

- 阶乘末尾 0 的个数：`n/5 + n/25 + n/125 + ...`。
- 回文数：反转一半数字比较，避免溢出。
- 整数反转：用 `long long` 暂存，最后判断是否超出 `int` 范围。
- 计数质数：只需筛到 `sqrt(n)`。

## 核心模板

### 统计二进制中 1 的个数

```cpp
int hammingWeight(uint32_t n) {
    int cnt = 0;
    while (n) { n &= n - 1; ++cnt; } // 每次去掉最低位的 1
    return cnt;
}
```

### 只出现一次的数字

```cpp
int singleNumber(vector<int>& a) {
    int x = 0;
    for (int v : a) x ^= v;
    return x;
}
```

### 快速幂

```cpp
long long fastPow(long long x, long long n, long long mod) {
    long long ans = 1 % mod;
    x %= mod;
    while (n > 0) {
        if (n & 1) ans = ans * x % mod;
        x = x * x % mod;
        n >>= 1;
    }
    return ans;
}
```

### 埃氏筛

```cpp
int countPrimes(int n) {
    if (n < 3) return 0;
    vector<bool> isPrime(n, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; (long long)i * i < n; ++i)
        if (isPrime[i])
            for (long long j = (long long)i * i; j < n; j += i)
                isPrime[j] = false;
    return count(isPrime.begin(), isPrime.end(), true);
}
```

### 整数反转（防溢出）

```cpp
int reverse(int x) {
    long long ans = 0;
    while (x) {
        ans = ans * 10 + x % 10;
        x /= 10;
    }
    if (ans < INT_MIN || ans > INT_MAX) return 0;
    return (int)ans;
}
```

## 例题拆解

### 136. 只出现一次的数字（Easy）

- 所有数异或，成对的数抵消，剩下唯一出现一次的数。
- 复杂度：时间 `O(n)`，空间 `O(1)`。

### 137. 只出现一次的数字 II（Medium）

- 每个数出现 3 次，用两个位掩码统计每一位出现 1 的次数模 3。
- 或按位统计 32 位，对 3 取模。
- 复杂度：时间 `O(32n)`，空间 `O(1)`。

### 50. Pow(x, n)（Medium）

- 快速幂，注意 `n` 为负数时先取相反数并取倒数。
- `n = INT_MIN` 时 `-n` 溢出，用 `long long`。
- 复杂度：时间 `O(log |n|)`，空间 `O(log |n|)`（递归）或 `O(1)`（迭代）。

### 204. 计数质数（Medium）

- 埃氏筛，`i` 只需枚举到 `sqrt(n)`，内层从 `i*i` 开始。
- 复杂度：时间 `O(n log log n)`，空间 `O(n)`。

### 29. 两数相除（Medium，已完成）

- 不能用乘法/除法，用快速幂思想：每次减去除数的最大倍数。
- 处理 `INT_MIN / -1` 溢出。
- 复杂度：时间 `O(log² n)`，空间 `O(1)`。

### 172. 阶乘后的零（Medium）

- 统计因子 5 的个数：`n/5 + n/25 + ...`。
- 复杂度：时间 `O(log n)`，空间 `O(1)`。

## 常见坑点

- `INT_MIN` 取相反数溢出；负数右移与无符号右移混淆。
- 快速幂的 `n` 用 `int` 时，`n = INT_MIN` 取反溢出。
- 筛法中 `i*i` 溢出 `int`，用 `long long`。
- 整数反转没有判断溢出，或反转后前导零处理错误。
- 异或题中「出现两次」和「出现三次」的解法不同，不能直接套。
- 位运算优先级低于比较运算符，记得加括号。
- `x & -x` 在 `x = 0` 时结果为 0，循环可能死掉。
- 负数取模与数学取模不同，注意题目要求。

## 题目清单

### 第 24 周 · 数学与位运算：位技巧、快速幂、质数、计数（18 题）

- [136](https://leetcode.cn/problems/single-number/) 只出现一次的数字 (E) · [137](https://leetcode.cn/problems/single-number-ii/) 只出现一次的数字 II (M) · [260](https://leetcode.cn/problems/single-number-iii/) 只出现一次的数字 III (M)
- [190](https://leetcode.cn/problems/reverse-bits/) 颠倒二进制位 (E) · [231](https://leetcode.cn/problems/power-of-two/) 2 的幂 (E) · [342](https://leetcode.cn/problems/power-of-four/) 4的幂 (E)
- [338](https://leetcode.cn/problems/counting-bits/) 比特位计数 (E) · [371](https://leetcode.cn/problems/sum-of-two-integers/) 两整数之和 (M) · [201](https://leetcode.cn/problems/bitwise-and-of-numbers-range/) 数字范围按位与 (M)
- [318](https://leetcode.cn/problems/maximum-product-of-word-lengths/) 最大单词长度乘积 (M) · [461](https://leetcode.cn/problems/hamming-distance/) 汉明距离 (E) · [477](https://leetcode.cn/problems/total-hamming-distance/) 汉明距离总和 (M)
- [1461](https://leetcode.cn/problems/check-if-a-string-contains-all-binary-codes-of-size-k/) 检查一个字符串是否包含所有长度为 K 的二进制子串 (M) · [7](https://leetcode.cn/problems/reverse-integer/) 整数反转 (M) · [172](https://leetcode.cn/problems/factorial-trailing-zeroes/) 阶乘后的零 (M)
- [204](https://leetcode.cn/problems/count-primes/) 计数质数 (M) · [292](https://leetcode.cn/problems/nim-game/) Nim 游戏 (E) · [458](https://leetcode.cn/problems/poor-pigs/) 可怜的小猪 (H)

## 已完成题目

- [12.整数转罗马数字.cpp](12.整数转罗马数字.cpp)
- [29.两数相除.cpp](29.两数相除.cpp)
