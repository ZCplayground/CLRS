//用于测试 插入 操作的main函数
int main()
{
	RBTree root = NULL;

	int a[100];
	for (int i = 0; i < 100; i++)
		a[i] = i + 1;
	
	Build_a_tree(&root, a, 100); // 插入 1 到 100 的有序序列，树会极其不平衡，来看看红黑树是怎么优化的

	printf("RBTree insert : \n");
	printf("preorder_traversal: "); preorder_traversal(root); printf("\n");
	printf("inorder_traversal: "); inorder_traversal(root); printf("\n");
	printf("postorder_traversal: "); postorder_traversal(root); printf("\n\n");
	printf("tree depth: %d\n", Tree_Depth(root)); // 深度会是 O(lgn)
	

	return 0;
}