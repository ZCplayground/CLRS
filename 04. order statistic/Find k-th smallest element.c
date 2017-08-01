#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void swap(int a[], int i, int j)
{
	int temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}

int partition(int a[], int p, int r)
{
	int x = a[r];

	int i = p - 1;
	int j = p;

	for (j = p; j <= r - 1; j++)
	{
		if (a[j] < x || a[j] == x)
		{
			i++;
			swap(a, i, j);
		}
	}
	swap(a, i + 1, r);

	return i + 1;
}

int select(int a[], int p, int r, int i)//�������� a[p..r] ֮�� �� i С��Ԫ��
{
	if (p == r)return a[p];

	int q = partition(a, p, r);
	int k = q - p +1;
	if (k == i)
		return a[q];
	else if (i < k)
		return select(a, p, q - 1, i);
	else
		return select(a, q + 1, r, i - k);
}

int median(int a[], int p, int r)//Ѱ������ a[p...r] ֮�����λ��
{
	int i = ((r - p + 1) + 1) / 2;//n��������λ�����ǵ� (n+1)/2 ����n = p - r + 1��
	return select(a, p, r, i);
}

int main()
{
	int a[5] = { 2,3,5,1,4 };
	
	for (int i = 1; i <= 5; i++)
		printf("%d ", select(a,0,4,i));
	printf("\n");

	printf("%d\n", median(a, 0, 4));

	return 0;
}
