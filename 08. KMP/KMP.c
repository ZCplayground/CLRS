#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int * compute_prefix_function(char *p)
{
	// next[i] : 模式 p 的前 i 个字符组成的串，其前缀和后缀的最长公共部分的长度
	// 因此对于 next 来说有意义的数字是从下标 1 开始的。但遍历源字符串时还是从 0 开始。

	int i, n, k;

	n = strlen(p);
	int *next = (int *)malloc(sizeof(int)*n);
	next[1] = next[0] = 0;  // next[1] 一定为 0，因为定义子串的长度不能等于母串

	k = 0;      // 第 i 次外层循环中，求的是 next[i+1]，k 表示的是 next[i] 的值 

	for (i = 1; i < n; i++) { // 求 next[i+1]

		// 根据之前算好的 next[i] 的数据来求 next[i+1]
		// next[i] 的数字如果是 a，那公共的前缀部分的长度是 a，下标是 0 ~ a-1
		// 现在要求 next[i+1] ，也就是把下标为 i 的字符与下标为 next[i] 的字符相比较（然后看最下面一条）
																 
		for (; k != 0 && p[k] != p[i]; k = next[k]);  // 如果两者不同，我们可以将长度为 next[i] 的前缀继续分割，获得 next[next[i]] （前缀的前缀）
													  // 然后跟前缀的前缀的后一个符相比较，依次类推。直到出现某次两个字符相等或字符串长度为0为止。

		if (p[k] == p[i]) 
			k++;

		next[i+1] = k; // 如果两者相同，则 next[i+1] 等于 next[i] + 1 （再看中间的for循环）
	}
	return next;
}

void kmp_match(char *text, char *p)
{
	int *next = compute_prefix_function(p);
	int m = strlen(p);
	int n = strlen(text);
	int q = 0; // 已经匹配的字符数
	int i;
	for (i = 0; i < n; i++) {
		while (q > 0 && p[q] != text[i])
			q = next[q]; // 字符串f的前移只是概念上的前移
						 // 只要我们在比较出现不等的时候，从最大公共长度之后比较f和O即可达到字符串f前移的目的。
		if (p[q] == text[i])
			q++;
		if (q == m)
			printf("pattern occurs with shift %d\n", i + 1 - m);// 可以更改成返回 int 或者 char *
	}
}

int main()
{
	char *p = "abcdabd";
	int m = strlen(p);
	int * next = compute_prefix_function(p);

	for (int i = 1; i <= m; i++)
	{
		printf("%d ", next[i]);
	}printf("\n");

	char *t = "bbcfabcdabfabcdabcdabde";
	kmp_match(t, p);

	return 0;
}