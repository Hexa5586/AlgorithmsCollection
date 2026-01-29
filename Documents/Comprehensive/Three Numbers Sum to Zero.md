# 三数之和为 0

#双指针 

## 题目描述

给定一个长度为 length 的数组，找出满足条件的三元组，三个数相加为零。*顺序不同、构成数相同的三元组算作同一个三元组。*

## 思路

1. **排序**：为了方便数的搜索，对原数组排序是个必须的任务。可以考虑直接使用 STL 中的搜索函数。
2. **消元**：三个指针一起寻找的话，数字间的大小关系并不明确，选择需要移动的指针也很复杂。因此可以考虑将一个指针从首个元素开始遍历，这样就**将三指针变成了双指针**，目的就从“寻找三个数相加得 0 ”变成了“**寻找两个数相加等于某个固定的数**”。
3. **双指针**：定下一个数后，另外两个指针就可以根据指向的值之和来简单地判断移动哪个指针，就可以依次遍历出所有的解。

## 步骤

1. **排序**：使用 std::sort() 对输入的 vector 进行排序。
2. **双指针定义**：定义第一个指针指向的值为 pivot ，它的值由负责遍历的 for 循环控制。**pivot 右侧的第一个位置**为**左指针**初始位置，**数组最后一个元素**为**右指针**初始位置。

```C++
for (int i = 0; i < length - 2; ++i) {
	// ...
	int pivot = data[i];
	int left = i + 1, right = length - 1;
	// ...
}
```

3. **双指针移动**：先计算两个指针指向的值和  pivot 的和。如果**和大于 0**，则将右指针左移以降低和；如果**和小于 0**，则将左指针右移以增大和；否则，说明找到了一个答案，记录答案并将左右指针同时向中间移动一格。

```C++
for (int i = 0; i < length - 2; ++i) {
	// ...

	int pivot = data[i];
	int left = i + 1, right = length - 1;

	while (left < right) {
		int s = pivot + data[left] + data[right];
		if (s < 0)  ++left;               
		else if (s > 0) --right;
		else {
			result.push_back({pivot, data[left], data[right]});
			++left; --right;
			
			// ...
		}
	}
}
```

4. **去重**：为了去掉重复的解，要做到以下两点：
* 找到答案后移动指针时，要**跳过与前面一项值相同的位置**。如 \[ -4 -1 -1 ... ]，则左指针移动时，第一个 -1 后面的所有 -1 都要直接跳过。
* 移动 pivot 时，也要跳过与前一个 pivot 值相同的位置。

```C++
for (int i = 0; i < length - 2; ++i) {
	// Jump over repeated pivots
	if (i > 0 && data[i] == data[i - 1])    continue;

	int pivot = data[i];
	int left = i + 1, right = length - 1;

	while (left < right) {
		int s = pivot + data[left] + data[right];
		if (s < 0)  ++left;               
		else if (s > 0) --right;
		else {
			result.push_back({pivot, data[left], data[right]});
			++left; --right;
			
			// Jump over repeated values when searching
			while (left < right && data[left] == data[left - 1])    ++left;
			while (left < right && data[right] == data[right + 1])  --right;
		}
	}
}
```

*具体代码见 Algorithms/ThreeNumbersSumToZero.cpp.*