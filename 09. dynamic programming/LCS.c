#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/*

动态规划思想：

最优子结构(optimal substructure)：一个问题的最优解也包括子问题的最优解
重叠子问题(overlapping subproblem)：递归解某个问题时会重复多次解其子问题

序列 s1 和序列 s2 长度分别为 m 和 n。
二维数组 c[m+1][n+1] 用来记录 LCS 的长度。

m和n分别从1开始，m++外循环，n++内循环。
- if str1[m] == str2[n], then L[m, n] = L[m - 1, n - 1] + 1；
- if str1[m] != str2[n], then L[m, n] = max{ L[m,n - 1]，L[m - 1, n]

c[m, n]中的最后的数字一定是最大的，且这个数字就是最长公共子序列的长度

*/

int c[101][101];

int max(int a, int b)
{
	return a > b ? a : b;
}

int LCS_length(char *s1, char *s2)
{
	int m = strlen(s1);
	int n = strlen(s2);
	
	memset(c, 0, sizeof(c));
	int i, j;

	for(i=1;i<=m;i++){
		for (j = 1; j <= n; j++) {
			if (s1[i-1] == s2[j-1])
				c[i][j] = c[i - 1][j - 1] + 1;
			else
				c[i][j] = max(c[i - 1][j], c[i][j - 1]);

			//printf("%d ", c[i][j]);
		}

		//printf("\n");
	}
	//printf("longest common subsquence length: %d\n\n", c[i - 1][j - 1]);
	return c[i-1][j-1];
}

/*
2、用数组 c 中构造 **一个** LCS

i 和 j 分别从 m，n 开始，递减循环直到i = 0，j = 0。 
- 如果str1[i] == str2[j]，则将str[i]字符插入到子序列内，i--，j--；
- 如果str1[i] != str[j]，则比较L[i,j-1]与L[i-1,j]，L[i,j-1]大，则j--，否则i--；
（如果相等，则任选一个，可由此构造出全部的 LCS）
*/

char * LCS(char *s1, char *s2)
{
	int lcs_len = LCS_length(s1, s2);
	char * lcs = (char *)malloc(sizeof(lcs_len));

	int m = strlen(s1);
	int n = strlen(s2);

	int i = m, j = n; //  搜索的位置
	int k = 0; // lcs 指针
	while (lcs_len > 0) {
		if (s1[i - 1] == s2[j - 1] && (c[i - 1][j - 1] + 1 == c[i][j])){
			lcs[k++] = s1[i - 1];
			i--;
			j--;
			lcs_len--;
		}
		else {
			// if(c[i - 1][j] == c[i][j] && c[i][j - 1] == c[i][j]) go up or left randomly;
			if (c[i - 1][j] == c[i][j])
				i--;
			else if (c[i][j - 1] == c[i][j])
				j--;
		}
	}
	lcs[k] = '\0';

	//REVERSE
	lcs_len = strlen(lcs);
	for (i = 0; i < lcs_len / 2; i++)
	{
		char temp;
		temp = lcs[i];
		lcs[i] = lcs[lcs_len - 1 - i];
		lcs[lcs_len - 1 - i] = temp;
	}

	return lcs;
}

int main()
{
	char *s1 = "BDCABA";
	char *s2 = "ABCBDAB";
	
	char *lcs = LCS(s1, s2);
	puts(lcs);

	return 0;
}