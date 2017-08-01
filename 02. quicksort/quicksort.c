#include<stdio.h>
#include<stdlib.h>
void swap(int a[], int i, int j)
{
	int temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}

int partition(int a[], int p, int r)//就地重排
{
	int x = a[r];//选择最右边的数作为主元（pivot）

	//在主元的左边维护一个子数组1，里面的元素全部小于 x 
	//在主元的右边维护一个子数组2，里面的元素大于等于 x

	int i = p - 1; //i 是子数组1 的最后一个元素的下标
	int j = p;	   //j 是子数组2 的最后一个元素的下标+1  j是未处理的数据的开始下标
	for (j = p; j <= r - 1; j++)
	{
		if (a[j] < x || a[j] == x)
		{
			i++;
			swap(a, i, j);
		}
	}
	swap(a, i + 1, r);//将主元放到中间

	return i + 1;
}

void quicksort(int a[], int p, int r)
{
	if (p >= r) return;

	int q = partition(a, p, r);
	quicksort(a, p, q - 1);
	quicksort(a, q + 1, r);
}

int main()
{
	int a[8] = { 2,8,7,1,3,5,6,4 };
	partition(a, 0, 7);

	for (int i = 0; i < 8; i++)
		printf("%d ", a[i]);
	printf("\n");


	int b[10] = { 9,6,4,3,10,7,2,8,1,5 };
	quicksort(b, 0, 9);

	for (int i = 0; i < 10; i++)
		printf("%d ", b[i]);
	printf("\n");


	return 0;
}
