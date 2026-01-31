# 最长回文子串 - 中心扩散法

#字符串 #枚举

## 题目描述

输出给定字符串的最长回文子串。

---
## 思路

1. **中心扩散法**：依次遍历字符串的每一个单元，从单元左右两侧同步向外搜寻**相等的字符**。
2. **奇长回文和偶长回文**：奇长回文的中心是**一个字符**，所以直接从某一个字符开始中心扩散即可；偶长回文的中心则是**两个相同的字符**，所以需要先找到**连续两个相同字符**，并作为一个整体向两侧扩散。

---
## 步骤

*为了减小耦合度，将中心扩散的搜索过程单独作为一个函数；为了弥补低耦合带来的时间效率损失，使用类成员变量来跨函数传递结果。*

1. **总体框架**：使用局部变量 `max_size` 来存储最长回文子串的长度，`max_left` 存储最长回文子串的左侧下标。有了这两个信息就可以定位答案子串。循环体遍历每个字符，并按照上文方法分别搜索奇长和偶长的回文子串。

```C++
std::string LongestPalindromeBasic(std::string s) {
	int size = s.length();
	int max_size = 1, max_left = 0;

	for (int i = 0; i < size; i++) {
		// Odd length palindrome
		// ...

		// Even length palindrome
		if (i < size - 1 && s[i] == s[i + 1]) {
			// ...
		}
	}

	return s.substr(max_left, max_size);
}
```

2. **中心扩散函数**：在类内部引入 `cached_size`、`cached_now_size` 和 `cached_now_left`三个整型成员，分别表示源字符串的长度、中心扩散搜索所得子串的长度和左侧下标。

```C++
void centricExtendSearch(const std::string& s, int left, int right) {
	while (left >= 0 && right <= cached_size - 1 && s[left] == s[right]) {
		--left; ++right;
	}
	cached_now_left = left + 1;
	cached_now_size = right - left - 1;
}
```

3. **调用中心扩散函数**

``` C++
for (int i = 0; i < cached_size; i++) {
	// Odd length palindrome
	centricExtendSearch(s, i - 1, i + 1);
	if (cached_now_size > max_size) {
		max_size = cached_now_size;
		max_left = cached_now_left;
	}

	// Even length palindrome
	if (i < cached_size - 1 && s[i] == s[i + 1]) {
		centricExtendSearch(s, i - 1, i + 2);
		if (cached_now_size > max_size) {
			max_size = cached_now_size;
			max_left = cached_now_left;
		}
	}
}
```

## 改进方向

1. **规范化**：可以在每两个字符之间插入一个间隔符 `#`，字符串首尾分别添加首尾标识符 `?` 和 `:`，这样就把所有的回文串全部变成奇长回文串，方便处理（但是会增加时间代价）。
2.  **Manacher 算法**：引入 Manacher 算法，可以复用前面搜索得到的回文串，利用对称思想加速处理 *（参见 [最长回文子串 - Manacher 算法](</String/Manacher's Algorithm.md>)）*。同时，上面提到的规范化处理简化 Manacher 算法的逻辑，通常作为 Manacher 算法前的预处理步骤。

---
*具体代码见 Algorithms/LongestPalindrome.cpp.*