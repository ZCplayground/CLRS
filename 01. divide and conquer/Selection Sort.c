#include<stdio.h>
void swap(int v[], int i, int j)
{
	int temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

int mini(int a[], int left, int right)
{
	/*确定最小元素下标*/
	int i, min=left;

	for (i = left+1; i <= right; i++)
	{
		if (a[i] < a[min])
			min = i;
	}
	return min;
}

void selectionsort(int a[], int left, int right)
{
	int i;
	for (i = left; i < right - 1; i++)
	{
		int j = mini(a, i, right);
		swap(a, i, j);
	}
}

int main()
{
	int a[10] = { 9,6,4,3,10,7,2,8,1,5 };
	selectionsort(a, 0, 9);
	for (int i = 0; i < 10; i++)
		printf("%d ", a[i]);
	printf("\n");
	return 0;
}
