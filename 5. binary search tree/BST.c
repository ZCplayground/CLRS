#include<stdio.h>
#include<stdlib.h>
#include<math.h>

struct Node {
	int data;
	struct Node * left;
	struct Node * right;
	struct Node * parent;
};

typedef struct Node * Tree;

struct Node * NewNode(int key)
{
	struct Node * p = (struct Node *)malloc(sizeof(Node));
	p->data = key;
	p->left = p->right = p->parent = NULL;
	return p;
}

void inorder_traversal(Tree t)
{
	if (t != NULL)
	{
		inorder_traversal(t->left);
		printf("%d ", t->data);
		inorder_traversal(t->right);
	}
}

void preorder_traversal(Tree t)
{
	if (t != NULL)
	{
		printf("%d ", t->data);
		preorder_traversal(t->left);
		preorder_traversal(t->right);
	}
}

void postorder_traversal(Tree t)
{
	if (t != NULL)
	{
		postorder_traversal(t->left);
		postorder_traversal(t->right);
		printf("%d ", t->data);
	}
}

Tree Tree_Insert(Tree root, int key)//向根为 root 的 BST 中插入一个结点，其键值为 key
{
	struct Node * x = root;//搜索节点
	struct Node * y = NULL;//父节点

	if (root == NULL)
	{
		root = NewNode(key);
		return root;
	}

	while (x != NULL)
	{
		y = x;
		if (key < x->data)
			x = x->left;
		else if (key > x->data)
			x = x->right;
		else
			return NULL;
	}

	struct Node *z = NewNode(key);
	z->parent = y;

	if (key < y->data)
		y->left = z;
	else y->right = z;

	return root;
}

struct Node * Tree_Search(Tree root, int key)//寻找根为 root 的 BST 中键值为 key 的结点。
{
	if (root == NULL || key == root->data)
		return root;

	struct Node * x = root;//搜索结点
	while (x != NULL&&x->data != key)
	{
		if (key < x->data)
			x = x->left;
		else
			x = x->right;
	}
	return x;
}

struct Node * Minimum(Tree root)//寻找根为 root 的 BST 中的键值最小的结点
{
	struct Node * x = root;
	while (x->left != NULL)
		x = x->left;

	return x;
}

struct Node * Maximum(Tree root)//寻找根为 root 的 BST 中的键值最大的结点
{
	struct Node * x = root;
	while (x->right != NULL)
		x = x->right;

	return x;
}

struct Node * Succeccor(Tree root, struct Node * x)//寻找以 root 为根的 BST 中的结点 x 在中序遍历下它的后继
{
	if (x->right != NULL)//如果结点 x 的右子树非空，则 x 的后继即右子树的最小节点
		return Minimum(root->right);

	struct Node * y = x->parent;
	while (y != NULL && x == y->right)//如果没有右子树，则一直向上寻找，直到遇到某个是其父的左儿子结点（或者root）为止
	{
		x = y;
		y = y->parent;
	}
	return y;
}

struct Node * Predecessor(Tree root, struct Node *x)//寻找以 root 为根的 BST 中的结点 x 在中序遍历下它的前驱
{
	if (x->left != NULL)//如果结点 x 的左子树非空，则 x 的前驱即左子树的最大结点
		return Maximum(root->left);

	else return x->parent;//否则父结点就是其前驱
}


void Tree_delete(Tree root, struct Node *z)//从以 root 为根的 BST 中删除结点 z
{
	/* 删除结点 z 时，考虑三种情况。具体是删哪一个结点被删除取决于 z 有多少子女

	case 1: z 没有儿子节点，删除 z 本身
	case 2: z 只有一个儿子，删除 z 本身
	case 3: z 有两个儿子，删除 z 的后继，然后用后继的键值替代 z 的键值*/

	struct Node * y; // y 是要被删除的结点
	if (z->left == NULL || z->right == NULL)// 如果 z 有 0 或 1 个儿子则删除 z，z 有 2 个儿子则删除 z 的后继
		y = z;
	else
		y = Tree_Succeccor(root, z);

	struct Node * x;
	if (y->left != NULL) // x 被置为 y 的非 NULL 子女，或者当 y 无子女时被置为 NULL
		x = y->left;
	else
		x = y->right;

	if (x != NULL) // z 有子节点，那么要重置 parent 指针
		x->parent = y->parent;

	if (y->parent == NULL) {//删除的结点是树根
		root = x;
	}
	else if (y->parent->left == y) //更新被删除的结点的父结点的儿子指针
		y->parent->left = x;
	else
		y->parent->right = x;

	if (y != z)//如果删除的结点是 z 的后继，就将后继的内容复制到 z 中
		z->data = y->data;

	free(y);
}


int max(int a, int b)
{
	return a > b ? a : b;
}

int Tree_Depth(Tree root)//返回以 root 为节点的树的深度
{
	if (root == NULL)
		return 0;
	else
		return max(Tree_Depth(root->left), Tree_Depth(root->right)) + 1;
}


int main()
{
	Tree root = NULL;
	int a[11] = { 15,6,3,7,2,4,13,9,18,17,20 };
	int i;
	for (i = 0; i < 11; i++)
	{
		root = Tree_Insert(root, a[i]);
	}

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
	printf("the depth of BST is %d\n\n", Tree_Depth(root));

	printf("preorder_traversal: "); preorder_traversal(root);printf("\n");
	printf("inorder_traversal: "); inorder_traversal(root); printf("\n");
	printf("postorder_traversal: "); postorder_traversal(root); printf("\n");

	printf("\nSearch element :\n");
	if (Tree_Search(root, 9))printf("9 is in BST\n");
	if (Tree_Search(root, 25) == NULL)printf("25 is not in BST\n\n");
	
	printf("maximun: %d\n", Maximum(root)->data);
	printf("minimue: %d\n\n", Minimum(root)->data);

	printf("root's successor is %d\n", Tree_Succeccor(root, root)->data);
	printf("root's predecessor is %d\n\n", Tree_Predecessor(root, root)->data);

	printf("Search and Delete:\n");
	printf("case 1: delete leaf node  eg : 9. inorder traversal after deleting: \n");
	Tree_delete(root, Tree_Search(root, 9));
	inorder_traversal(root); printf("\n");

	printf("case 2: delete node with 1 child  eg : 7. inorder traversal after deleting: \n");
	Tree_delete(root, Tree_Search(root, 7));
	inorder_traversal(root); printf("\n");

	printf("case 3: delete node with 2 children eg : 20. inorder traversal after deleting: \n");
	Tree_delete(root, Tree_Search(root, 20));
	inorder_traversal(root); printf("\n");

	printf("\nDone!\n\n");

	return 0;
}
