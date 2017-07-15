//用于测试 插入和删除 操作的main函数

int main()
{
	RBTree root = NULL;

	int a[100];
	for (int i = 0; i < 100; i++)
		a[i] = i + 1;
	
	Build_a_tree(&root, a, 100); // 插入 1 到 100 的有序序列，树会极其不平衡，来看看红黑树是怎么优化的

	printf("insert 1-100 to RBTree : \n");
	printf("preorder_traversal: "); preorder_traversal(root); printf("\n");
	printf("inorder_traversal: "); inorder_traversal(root); printf("\n");
	printf("postorder_traversal: "); postorder_traversal(root); printf("\n\n");
	printf("tree depth: %d , is O(log n), quite balanced!!\n\n", Tree_Depth(root)); // 深度会是 O(lgn)

	printf("delete node 24 and 105\n\n");
	Delete_node_with_key(24, &root);
	Delete_node_with_key(105, &root);

	printf("preorder_traversal: "); preorder_traversal(root); printf("\n");
	printf("inorder_traversal: "); inorder_traversal(root); printf("\n");  //中序遍历中少了 24 
	printf("postorder_traversal: "); postorder_traversal(root); printf("\n\n");
	printf("tree depth: %d\n", Tree_Depth(root));

	return 0;
}