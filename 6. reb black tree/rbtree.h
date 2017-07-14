#include<stdio.h>
#include<stdlib.h>
#include<math.h>

enum Color {
	RED = 0,
	BLACK = 1 
};

struct RBNode {
	Color color;
	int data;
	struct RBNode * left;
	struct RBNode * right;
	struct RBNode * parent;
};

typedef struct RBNode * RBTree;

struct RBNode Nil = { BLACK, -9999, NULL,NULL,NULL };
struct RBNode *nil = &Nil;//哨兵值 

struct RBNode * NewNode(int key)
{
	struct RBNode * p = (struct RBNode *)malloc(sizeof(RBNode));
	p->color = BLACK;
	p->data = key;
	p->left = p->right = p->parent = NULL;
	return p;
}

/*---------------------------------------------------------------
|     x             y        左旋 Rotate_left(x,T); a、b、c 是子树
|    / \    ==>    / \
|   a   y         x   c      ① y 的左孩子 b 成为 x 的右孩子，
|      / \       / \         ② y 成为新子树的根，
|     b   c     a   b        ③ x 成为 y 的左孩子。
----------------------------------------------------------------*/

struct RBNode * Rotate_left(struct RBNode * x, RBTree root) //对根为 root 的 RBT 里的结点 x 进行左旋
{
	struct RBNode * y = x->right;

	x->right = y->left;// ① y 的左孩子 c 成为 x 的右孩子

	if (y->left != nil)
		y->left->parent = x; // 如果 y 的左子树 b 不为空的话，改变 b 的父结点为 x

	y->parent = x->parent; // ② y 成为新子树的根

	if (x->parent == nil) // x 为根节点，则 y 为新的根节点
		root = y;
	else if (x == x->parent->left) // 否则，更新 y 的父结点子指针关系
		x->parent->left = y;
	else
		x->parent->right = y;

	y->left = x; // ③ x 成为 y 的左孩子
x->parent = y;

return root;
}

/*-----------------------------------------------------------
|     x           y          右旋 Rotate_right(x,T)
|    / \   ==>   / \
|   y   c       a   x        ① y 的右孩子 b 成为 x 的左孩子，
|  / \             / \       ② y 成为新子树的根，
| a   b           b   c      ③ x 成为 y 的右孩子。
-----------------------------------------------------------*/

struct RBNode * Rotate_right(struct RBNode *x, RBTree root)//对根为 root 的 RBT 里的结点 x 进行右旋
{
	struct RBNode * y = x->left;

	x->left = y->right; // ① y 的右孩子 b 成为 x 的左孩子，

	if (y->right != nil)
		y->right->parent = x;

	y->parent = x->parent;// ② y 成为新子树的根，

	if (x->parent == nil)
		root = y;
	else if (x->parent->left == x)
		x->parent->left = y;
	else
		x->parent->right = y;

	y->right = x;
	x->parent = y;

	return root;
}

void inorder_traversal(RBTree t)
{
	if (t != NULL&&t != nil)
	{
		inorder_traversal(t->left);
		printf("%d ", t->data);
		inorder_traversal(t->right);
	}
}

void preorder_traversal(RBTree t)
{
	if (t != NULL&&t != nil)
	{
		printf("%d ", t->data);
		preorder_traversal(t->left);
		preorder_traversal(t->right);
	}
}

void postorder_traversal(RBTree t)
{
	if (t != NULL&&t != nil)
	{
		postorder_traversal(t->left);
		postorder_traversal(t->right);
		printf("%d ", t->data);
	}
}

RBTree Tree_Insert(RBTree root, int key)//向根为 root 的 BST 中插入一个结点，其键值为 key
{
	struct RBNode * x = root;//搜索节点
	struct RBNode * y = NULL;//父节点

	if (root == NULL)
	{
		root = NewNode(key);
		root->left = nil;
		root->right = nil;
		root->color = BLACK;
		return root;
	}

	while (x != nil)
	{
		y = x;
		if (key < x->data)
			x = x->left;
		else if (key > x->data)
			x = x->right;
		else
			return NULL;
	}

	struct RBNode *z = NewNode(key);
	z->parent = y;

	if (key < y->data)
		y->left = z;
	else y->right = z;   

	// RBTree_Insert 的前面的步骤与一般的 Tree_Insert 无异

	z->left = nil;
	z->right = nil;
	z->color = RED; // 新插入的节点的两个儿子都指向 nil ，置为红色

	return root;
}

struct RBNode * Tree_Search(RBTree root, int key)//寻找根为 root 的 BST 中键值为 key 的结点。
{
	if (root == NULL || key == root->data)
		return root;

	struct RBNode * x = root;//搜索结点
	while (x != NULL&&x->data != key)
	{
		if (key < x->data)
			x = x->left;
		else
			x = x->right;
	}
	return x;
}

struct RBNode * Minimum(RBTree root)//寻找根为 root 的 BST 中的键值最小的结点
{
	struct RBNode * x = root;
	while (x->left != NULL)
		x = x->left;

	return x;
}

struct RBNode * Maximum(RBTree root)//寻找根为 root 的 BST 中的键值最大的结点
{
	struct RBNode * x = root;
	while (x->right != NULL)
		x = x->right;

	return x;
}

struct RBNode * Tree_Succeccor(RBTree root, struct RBNode * x)//寻找以 root 为根的 BST 中的结点 x 在中序遍历下它的后继
{
	if (x->right != NULL)//如果结点 x 的右子树非空，则 x 的后继即右子树的最小节点
		return Minimum(root->right);

	struct RBNode * y = x->parent;
	while (y != NULL && x == y->right)//如果没有右子树，则一直向上寻找，直到遇到某个是其父的左儿子结点（或者root）为止
	{
		x = y;
		y = y->parent;
	}
	return y;
}

struct RBNode * Tree_Predecessor(RBTree root, struct RBNode *x)//寻找以 root 为根的 BST 中的结点 x 在中序遍历下它的前驱
{
	if (x->left != NULL)//如果结点 x 的左子树非空，则 x 的前驱即左子树的最大结点
		return Maximum(root->left);

	else return x->parent;//否则父结点就是其前驱
}

void Tree_delete(RBTree root, struct RBNode *z)//从以 root 为根的 BST 中删除结点 z
{
	/* 删除结点 z 时，考虑三种情况。具体是删哪一个结点被删除取决于 z 有多少子女

	case 1: z 没有儿子节点，删除 z 本身
	case 2: z 只有一个儿子，删除 z 本身
	case 3: z 有两个儿子，删除 z 的后继，然后用后继的键值替代 z 的键值*/

	struct RBNode * y; // y 是要被删除的结点
	if (z->left == NULL || z->right == NULL)// 如果 z 有 0 或 1 个儿子则删除 z，z 有 2 个儿子则删除 z 的后继
		y = z;
	else
		y = Tree_Succeccor(root, z);

	struct RBNode * x;
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

int Tree_Depth(RBTree root)//返回以 root 为节点的树的深度
{
	if (root == NULL)
		return 0;
	else
		return max(Tree_Depth(root->left), Tree_Depth(root->right)) + 1;
}

void Build_a_tree(RBTree * root, int a[], int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		*root = Tree_Insert(*root, a[i]);
	}
}
