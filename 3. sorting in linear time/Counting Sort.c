#include<stdio.h>
#include<stdlib.h>

void countingsort(int a[], int k, int len)
{
	int *b = (int *)malloc(sizeof(int)*len);
	int *c = (int *)malloc(sizeof(int)*(k + 1));
	int i, j;
	for (i = 0; i <= k; i++)
		c[i] = 0;
	
	for (j = 0; j < len; j++)
		c[a[j]]++;

	for (i = 1; i <= k; i++)
		c[i] += c[i - 1];

	for (j = len - 1; j >= 0; j--)
	{
		b[c[a[j]] - 1] = a[j];
		c[a[j]]--;
	}
	for (j = 0; j < len; j++)
		a[j] = b[j];

	free(c);
	free(b);
}

int main()
{
	int a[5] = { 4,1,3,4,3 };
	countingsort(a, 4, 5);

	for (int i = 0; i < 5; i++)
		printf("%d ", a[i]);
	printf("\n");

	return 0;
}
