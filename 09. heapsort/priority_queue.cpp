#include<iostream>
using namespace std;

class p_queue {

private:
	int a[1000];
	int heapsize;

	int parent(int i) { return (i - 1) / 2; }
	int left(int i) { return  2 * i + 1; }
	int right(int i) { return 2 * i + 2; }

	void Max_heapify(int A[], int n, int i);
	void build_Maxheap(int A[], int n);
	void heapsort(int A[], int n);

public:
	p_queue(int *A, int n);
	int maximum();
	int extract_max();
	void heap_increase_key(int i, int key);
	void insert(int x);
	
	
};

p_queue::p_queue(int *A, int n)
{
	for (int i = 0; i < n; i++)
		a[i] = A[i];
	heapsize = n;
	build_Maxheap(a, heapsize);
}

int p_queue::maximum()
{
	if (heapsize < 1) {
		printf("error: heap underflow.\n");
		return -1;
	}
	int max = a[0];
	return max;
}

int p_queue::extract_max()
{
	if (heapsize < 1) {
		printf("error: heap underflow");
		return -1;
	}
	int max = a[0];
	a[0] = a[heapsize-1];
	heapsize--;
	Max_heapify(a, heapsize, 0); // 思路与 heapsort 很像
	return max;
}

void p_queue::heap_increase_key(int i, int key) // 将下标为 i 的元素的键值更新为更大的 key 
{
	if (key < a[i]) {
		printf("error: new key is smaller than current key\n");
		return;
	}
	a[i] = key;

	while (i > 0 && a[parent(i)] < a[i]) { // 从本节点往根节点的移动路径上，不断与其父母比较
		swap(a[i], a[parent(i)]); // 如果此元素的 key 更大，则交换此元素与其父节点并继续移动
		i = parent(i);
	}
	// 当元素的 key 小于其父母，最大堆性质成立，函数结束
}

void p_queue::insert(int key) // 向堆中插入新的元素，其键值为 key
{
	heapsize++;
	a[heapsize - 1] = -9999; // 先加入一个 key很小的（负无穷）的叶节点来扩展最大堆
	heap_increase_key(heapsize - 1, key); // 调用 increase_key 函数来设置正确的 key 值，并维护最大堆性质
}

void p_queue::Max_heapify(int A[], int n, int i)
{
	int l = left(i);
	int r = right(i);
	int largest;
	if (l <= (n - 1) && A[l] > A[i])
		largest = l;
	else
		largest = i;
	if (r <= (n - 1) && A[r] > A[largest])
		largest = r;
	if (largest != i)
	{
		std::swap(A[i], A[largest]);
		Max_heapify(A, n, largest);
	}
}

void p_queue::build_Maxheap(int A[], int n)
{
	int i;

	for (i = n / 2 - 1; i >= 0; i--) // 子数组 A[(n/2)-1 ... n-1] 的元素都是树的叶子。
									 // 可以把叶子看成符合最大堆性质的堆 

		Max_heapify(A, n, i); // 对其他每一个节点调用一次 Max_heapify （一定要自底向上）
}

void p_queue::heapsort(int A[], int n)
{
	build_Maxheap(A, n);
	for (int i = n - 1; i > 0; i--)
	{
		swap(A[0], A[i]); // 交换 A[0] 与 A[i]，
						  // A[0] 一直是当前这 A[0 ~ i] 数组中最大的数，也就是说，会不断把最大的数放到数列尾部
		Max_heapify(A, --n, 0); // 然后调整剩余堆的最大堆性质
	}
}