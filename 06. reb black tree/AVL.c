//自己模仿算法导论里面打的
#include<stdio.h>
#include<stdlib.h>

struct AVLNode {
	int key;
	int height;
	struct AVLNode * left;
	struct AVLNode * right;
	//struct AVLNode * parent;
};

typedef struct AVLNode * AVLTree;

struct AVLNode * NewNode(int key)
{
	struct AVLNode * p = (struct AVLNode *)malloc(sizeof(struct AVLNode));
	p->height = 0;
	p->key = key;
	p->left = p->right = NULL;
	
	if (p == NULL) printf("memory exhausted!\n");

	return p;
}

int max(int a, int b)
{
	return a > b ? a : b;
}

int Get_Height(struct AVLNode *x)
{
	return (x == NULL) ? 0 : x->height;
}

// 基本遍历操作：
void inorder_traversal(AVLTree t)
{
	if (t != NULL)
	{
		inorder_traversal(t->left);
		printf("%d ", t->key);
		inorder_traversal(t->right);
	}
}

void preorder_traversal(AVLTree t)
{
	if (t != NULL)
	{
		printf("%d ", t->key);
		preorder_traversal(t->left);
		preorder_traversal(t->right);
	}
}

void postorder_traversal(AVLTree t)
{
	if (t != NULL)
	{
		postorder_traversal(t->left);
		postorder_traversal(t->right);
		printf("%d ", t->key);
	}
}

struct AVLNode * Tree_Search(AVLTree root, int key)//寻找根为 root 的树中键值为 key 的结点。
{
	if (root == NULL || key == root->key)
		return root;

	struct AVLNode * x = root;//搜索结点
	while (x != NULL && x->key != key) // 非递归写法
	{
		if (key < x->key)
			x = x->left;
		else
			x = x->right;
	}
	return x;
}


/*---------------------------------------------------------------
|     x             y        左旋 Rotate_left(x,T); a、b、c 是子树
|    / \    ==>    / \
|   a   y         x   c      ① y 的左孩子 b 成为 x 的右孩子，
|      / \       / \         ② y 成为新子树的根，
|     b   c     a   b        ③ x 成为 y 的左孩子。
----------------------------------------------------------------*/

struct AVLNode * Left_Rotation(struct AVLNode * x) //对 AVL 里的结点 x 进行左单旋
{
	struct AVLNode * y = x->right;

	x->right = y->left;// ① y 的左孩子 c 成为 x 的右孩子

	//if (y->left != NULL)
	//	y->left->parent = x; // 如果 y 的左子树 b 不为 NULL 的话，改变 b 的父结点为 x

	//y->parent = x->parent; // ② y 成为新子树的根

//if (x == x->parent->left) // 更新 y 的父结点子指针关系
	//	x->parent->left = y;
	//else
	//	x->parent->right = y;

	y->left = x; // ③ x 成为 y 的左孩子
	//x->parent = y;

	x->height = max(Get_Height(x->left), Get_Height(x->right)) + 1; // 更新节点高度
	y->height = max(Get_Height(y->right), Get_Height(x)) + 1;

	return y; // 返回这片子树的新根节点：y
}


/*-----------------------------------------------------------
|     x           y          右旋 Rotate_right(x,T)
|    / \   ==>   / \
|   y   c       a   x        ① y 的右孩子 b 成为 x 的左孩子，
|  / \             / \       ② y 成为新子树的根，
| a   b           b   c      ③ x 成为 y 的右孩子。
-----------------------------------------------------------*/

struct AVLNode * Right_Rotation(struct AVLNode *x)//对 AVL 里的结点 x 进行右单旋
{
	struct AVLNode * y = x->left;

	x->left = y->right; // ① y 的右孩子 b 成为 x 的左孩子，

	//if (y->right != NULL)
	//	y->right->parent = x;

	//y->parent = x->parent;// ② y 成为新子树的根，
	// 
	//if (x->parent->left == x)
	//	x->parent->left = y;
	//else
	//	x->parent->right = y;

	y->right = x; //③ x 成为 y 的右孩子。
	//x->parent = y;

	x->height = max(Get_Height(x->left), Get_Height(x->right)) + 1; // 更新节点高度
	y->height = max(Get_Height(y->left), Get_Height(x)) + 1;

	return y;
}


/*-----------------------------------------------------------------------------
|     x               x                  z           小写字母 x、y、z 代表节点，
|    / \             / \               /   \         大写字母 ABCD 代表子树
|   y   D           z   D             y     x
|  / \       ==>   / \       ==>     / \   / \
| A   z           y   C             A  B   C  D
|    / \         / \
|   B   C       A   B
------------------------------------------------------------------------------*/


struct AVLNode * Left_Right_Rotation(struct AVLNode *x) //对不平衡的节点 x 进行 LR 旋转
{
	Left_Rotation(x->left); // 先对 x 的左儿子 y 进行左旋
	return Right_Rotation(x->left); // 再对 x 的左儿子 z 进行右旋，返回的是子树的根 z
}

/*-----------------------------------------------------------------------------
|     x               x                   z          小写字母 x、y、z 代表节点，
|    / \             / \                /   \        大写字母 ABCD 代表子树
|   A   y           A   z              y     x
|      / \   ==>       / \     ==>    / \   / \
|     z   D           B   y          A  B   C  D
|    / \                 / \
|   B   C               C   D
------------------------------------------------------------------------------*/
struct AVLNode * Right_Left_Rotation(struct AVLNode *x) //对不平衡的节点 x 进行 RL 旋转，也就是 LR 旋转的对称情况
{
	Right_Rotation(x->right);
	return Left_Rotation(x->right); 
}


AVLTree AVLTree_Insert(AVLTree root, int key) //向根为 root 的树中插入一个结点，其键值为 key
{ 
	if (root == NULL)
	{
		root = NewNode(key); 
	}

	else if (key < root->key)
	{
		root->left = AVLTree_Insert(root->left, key); // 递归写法，因为要回溯不断更新节点的高度、做旋转

		// 插入节点后，若AVL树失去平衡，则进行相应的调节。
		if (Get_Height(root->left) - Get_Height(root->right) == 2) // 高度差达到了 2，需要调整
		{
			// 看书本 P218

			if (/*root->left==NULL ||*/ key < root->left->key)       // case 1：插在了左边的左子树
				root = Right_Rotation(root);
			else                             // case 2：插在了左边的右子树
				root = Left_Right_Rotation(root);
		}
	}

	else if (key > root->key) 
	{
		root->right = AVLTree_Insert(root->right, key); 

		if (Get_Height(root->right) - Get_Height(root->left) == 2)
		{
			// 同上
			if (/*root->right == NULL ||*/ key > root->right->key)
				root = Left_Rotation(root);
			else
				root = Right_Left_Rotation(root);
		}
	}

	else  // 插入了相同的元素
	{
		printf("error: already exists!\n");
	}

	root->height = max(Get_Height(root->left), Get_Height(root->right)) + 1;

	return root;
}

struct AVLNode * Minimum(AVLTree root)//寻找根为 root 的树中的键值最小的结点
{
	struct AVLNode * x = root;
	while (x->left != NULL)
		x = x->left;

	return x;
}


struct AVLNode * Maximum(AVLTree root)//寻找根为 root 的 BST 中的键值最大的结点
{
	struct AVLNode * x = root;
	while (x->right != NULL)
		x = x->right;

	return x;
}

/*struct AVLNode * Tree_Succeccor(AVLTree root, struct AVLNode * x)//寻找以 root 为根的树中的结点 x 在中序遍历下它的后继
{
	if (x->right != NULL)//如果结点 x 的右子树非空，则 x 的后继即右子树的最小结点
		return Minimum(x->right);

	struct AVLNode * y = x->parent;
	while (y != NULL && x == y->right)//如果没有右子树，则一直向上寻找，直到遇到某个是其父的左儿子结点（或者root）为止
	{
		x = y;
		y = y->parent;
	}
	return y;
}*/

/*struct AVLNode * Tree_Predecessor(AVLTree root, struct AVLNode *x)//寻找以 root 为根的树中的结点 x 在中序遍历下它的前驱
{
	if (x->left != NULL)//如果结点 x 的左子树非空，则 x 的前驱即左子树的最大结点
		return Maximum(x->left);

	else return x->parent;//否则父结点就是其前驱
}*/

int Tree_Search_Get_Depth(AVLTree root, int key)//寻找根为 root 的树中键值为 key 的结点，返回值是该节点的深度
{
	int depth = 1;
	if (root == NULL || key == root->key)
		return depth;

	struct AVLNode * x = root;//搜索结点
	while (x != NULL && x->key != key) // 非递归写法
	{
		if (key < x->key)
			x = x->left;
		else
			x = x->right;

		depth++;
	}
	return depth;
}

void Answer_List(AVLTree root, int a[], int b[], int n) // 依次输出 a 数组中的元素所在以 root 为根的 AVL 树中的深度到 b 数组中
{
	int i;
	for (i = 0; i < n; i++)
	{
		b[i] = Tree_Search_Get_Depth(root, a[i]);
	}
	for (i = 0; i < n; i++)
	{
		if (i == 0) {
			printf("%d", b[i]);
		}
		else {
			printf(" %d", b[i]);
		}
	}
}

void Build_a_AVLTree(AVLTree * root, int a[], int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		*root = AVLTree_Insert(*root, a[i]);
	}
}

int main()
{
	AVLTree root = NULL;
	int a[6] = { 1,2,3,4,5,6 };
	Build_a_AVLTree(&root, a, 6);
	
	int b[6];
	Answer_List(root, a, b, 6);

	getchar();
	return 0;
}