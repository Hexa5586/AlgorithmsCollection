# 滑动窗口最大值

#滑动窗口 #单调队列 #双端队列

## 题目描述

给定一个整数数组和一个定长为 `windowLength` 的滑动窗口，求滑动窗口滑动到每个位置时窗口内的最大值。

---
## 思路

1. 单调队列：使用一个单调递减（**本题中，单调队列储存的是索引，因此“单调性”指的是索引对应的元素单调**）的队列；随着滑动窗口的移动，从单调队列的首部“淘汰”不在滑动窗口范围内的元素。这样可以保证从队头取出的一定是**对当前窗口有效**的最大值。
2. 双端队列：由于单调队列的头部和尾部都需要进行弹出（POP）操作，所以需要使用双端队列。

---
## 步骤

1. **形成滑动窗口**：滑动窗口是有长度的。最开始的 `windowLength - 1` 个元素不需要更新最大值数组，但是需要维护单调队列：**持续弹出队尾元素直至队列为空，或插入元素小于等于队尾索引对应的元素**，然后插入待插入元素。第 `windowLength` 个元素插入后，将单调队列队头索引对应的元素插入单调队列。

```C++
// Forming sliding window
for (int i = 0; i < windowLength; ++i) {
	while (!monoQueue.empty() && data[monoQueue.back()] < data[i]) {
		monoQueue.pop_back();
	}
	monoQueue.push_back(i);
}
result.push_back(data[monoQueue.front()]);
```

2. **开始滑动**：单调队列的维护和第 1 步没有区别。关键在于，每次滑动后，**检查单调队列的队头索引是否在滑动窗口范围内**，否则需要弹出队头。

```C++
// Start sliding
for (int i = windowLength; i < data_length; ++i) {
	while (!monoQueue.empty() && data[monoQueue.back()] < data[i]) {
		monoQueue.pop_back();
	}
	monoQueue.push_back(i);

	// Check if the front element is still in the window
	if (monoQueue.front() < i - windowLength + 1) {
		monoQueue.pop_front();
	}
	result.push_back(data[monoQueue.front()]);
}
```

---
*具体代码见 Algorithms/SlidingWindowMaximum.cpp.*