void countingsort(int a[], int k, int len, int looptime)
{
	int *b = (int *)malloc(sizeof(int)*len);
	int *c = (int *)malloc(sizeof(int)*(k + 1));

	int temp = (int)pow(10, looptime - 1);

	int i, j;
	for (i = 0; i <= k; i++)
		c[i] = 0;
	
	for (j = 0; j < len; j++)
		//c[a[j]]++;  只需要对c数组进行小改动即可
		c[(a[j] / temp) % 10]++;

	for (i = 1; i <= k; i++)
		c[i] += c[i - 1];

	for (j = len - 1; j >= 0; j--)
	{
		b[c[(a[j] / temp) % 10] - 1] = a[j];
		c[(a[j] / temp) % 10]--;
	}
	for (j = 0; j < len; j++)
		a[j] = b[j];

	free(c);
	free(b);
}


int findmax(int *a, int n)
{
	int i, max = INT_MIN;
	for (i = 0; i < n; i++)
	{
		if (*(a + i) > max)
			max = *(a + i);
	}
	return max;
}

int getlooptimes(int max)
{
	int count = 1;
	int temp = max / 10;
	while (temp != 0)
	{
		temp /= 10;
		count++;
	}
	return count;
}


void radixsort(int a[], int d, int len)//a是待排数组，d是最高位数
{
	int max = findmax(a, len);
	int i;
	for (i = 1; i <= d; i++)
	{
		countingsort(a, max, len, i);
	}
}


int main()
{
	int a[7] = { 329,457,657,839,436,720,355 };
	radixsort(a, 3, 7);

	for (int i = 0; i < 5; i++)
		printf("%d ", a[i]);
	printf("\n");

	return 0;
}
