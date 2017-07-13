#include<stdio.h>
#include<stdlib.h>
void merge(int a[], int p, int q, int r)//a[p,q] 与 a[q+1, r] 都是排好序的，合并成 a[p,r] 是排好序的
{
	int n1 = q - p + 1;
	int n2 = r - q;
	

	int *L = (int *)malloc(sizeof(int)*(n1+1));
	int *R = (int *)malloc(sizeof(int)*(n2+1));

	int i, j;
	for (i = 0; i < n1; i++)
		L[i] = a[p + i];

	for (j = 0; j < n2; j++)
		R[j] = a[q + j + 1];

	L[n1] = INT_MAX;
	R[n2] = INT_MAX;

	for (int k = p, i = 0, j = 0; k <= r; k++)
	{
		if (L[i] < R[j] || L[i] == R[j])
		{
			a[k] = L[i];
			i++;
		}
		else
		{
			a[k] = R[j];
			j++;
		}
	}
	free(L);
	free(R);
}

void mergesort(int a[], int p, int r)
{
	if (p >= r)return;//数组元素只有一个的时候被认为是排好序的，是递归开始返回的地方

	int q = (p + r) / 2;

	mergesort(a, p, q);
	mergesort(a, q + 1, r);
	merge(a, p, q, r);
}

int main()
{
	int a[8] = { 2,4,5,7,1,2,3,6 };
	merge(a, 0, 3, 7);

	for (int i = 0; i < 8; i++)
		printf("%d ", a[i]);
	printf("\n");

	int b[10]= { 9,6,4,3,10,7,2,8,1,5 };
	mergesort(b, 0, 9);

	for (int i = 0; i < 10; i++)
		printf("%d ", b[i]);
	printf("\n");

	return 0;
}
