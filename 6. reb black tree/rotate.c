//用于测试 旋转 的 main 函数
int main()
{
	RBTree root = NULL;
	int a[11] = { 15,6,3,7,2,4,13,9,18,17,20 };
	Build_a_tree(&root, a, 11);
	/*
	BST is like：	 	15
	                  /    \
	                 6     18
	                / \    / \
	               3   7  17 20
	              / \   \
	             2   4   13
	                     /
	                    9
	*/
	printf("beforn rotate : \n");
	printf("preorder_traversal: "); preorder_traversal(root); printf("\n");
	printf("inorder_traversal: "); inorder_traversal(root); printf("\n");
	printf("postorder_traversal: "); postorder_traversal(root); printf("\n\n");

	struct RBNode * n = Tree_Search(root, 18);
	Rotate_left(n, root);
	/*
	BST is like：	 	 15
	                  /      \
	                 6        20
	                / \        / 
	               3   7      18  
	              / \   \     /  
	             2   4   13  17    
	                     /
	                    9
	*/
	printf("after rotate node(18) left: \n");
	printf("preorder_traversal: "); preorder_traversal(root); printf("\n");
	printf("inorder_traversal: "); inorder_traversal(root); printf("\n");
	printf("postorder_traversal: "); postorder_traversal(root); printf("\n\n");


	struct RBNode * m = Tree_Search(root, 3);
	Rotate_right(m, root);
	/*
	BST is like：	 	 15
	                  /      \
	                 6        20
	                / \        /
	               2   7      18
	                \   \     /
	                 3   13  17
	                  \   /
	                   4 9 
	*/

	printf("after rotate node(3) right: \n");
	printf("preorder_traversal: "); preorder_traversal(root); printf("\n");
	printf("inorder_traversal: "); inorder_traversal(root); printf("\n");
	printf("postorder_traversal: "); postorder_traversal(root); printf("\n");

	return 0;
}