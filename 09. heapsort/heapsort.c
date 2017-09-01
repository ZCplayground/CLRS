#include<iostream>
using namespace std;

int parent(int i) // 计算下标 i 的父亲的下标
{
	return (i - 1) / 2;
}

int left(int i) // 计算下标 i 的左儿子的下标
{
	return 2 * i + 1;
}

int right(int i) // 计算下标 i 的右儿子的下标
{
	return 2 * i + 2;
}

void Max_heapify(int A[], int n, int i) // 保持以 i 为根节点的子树的最大堆性质
{
	int heapsize = n - 1;
	int l = left(i);   
	int r = right(i); 
	int largest; // 从元素 A[i], A[left], A[right] 中找出最大的
	if (l <= heapsize && A[l] > A[i])
		largest = l; 
	else
		largest = i;
	if (r <= heapsize && A[r] > A[largest])
		largest = r;

	if (largest != i) // 如果 A[i] 是最大的，则以 i 为根节点的子树已经是最大堆，程序结束
	{
		swap(A[i], A[largest]); // 否则 i 的某个孩子有最大元素，交换 A[i] 与那个孩子
		Max_heapify(A, n, largest); // 此时的 A[largest] 为根的子树又有可能违反最大堆性质，递归调用过程。
	}
}
 
void build_MaxHeap(int A[], int n)
{
	int i;

	for (i = n / 2 - 1; i >= 0; i--) // 子数组 A[(n/2)-1 ... n-1] 的元素都是树的叶子。
                                     // 可以把叶子看成符合最大堆性质的堆 

		Max_heapify(A, n, i); // 对其他每一个节点调用一次 Max_heapify
}
 
void heapsort(int A[], int n)
{ 
	int i;
	build_MaxHeap(A, n); // 先将数组建成最大堆
	for (i = n - 1; i > 0; i--) 
	{
		swap(A[0], A[i]); // 交换 A[0] 与 A[i]，
                          // A[0] 一直是当前这 A[0 ~ i] 数组中最大的数，也就是说，会不断把最大的数放到数列尾部
		Max_heapify(A, --n, 0); // 然后调整剩余堆的最大堆性质
	}
}
 
int main()
{
	int A[10] = { 16,14,10,8,7,9,3,2,4,1 };
	heapsort(A, 10);
	for (int i = 0; i < 10; i++)
		printf("%d ", A[i]);
	printf("\n");
	return 0;
}