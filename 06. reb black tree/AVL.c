#include<stdio.h>
#include<stdlib.h>

struct AVLNode {
	int key;
	int height;
	struct AVLNode * left;
	struct AVLNode * right;
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

int Get_Height(struct AVLNode * x)
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
|     x             y        左旋 Rotate_left(x); a、b、c 是子树
|    / \    ==>    / \
|   a   y         x   c      ① y 的左孩子 b 成为 x 的右孩子，
|      / \       / \         ② y 成为新子树的根，
|     b   c     a   b        ③ x 成为 y 的左孩子。
----------------------------------------------------------------*/

struct AVLNode * Left_Rotation(struct AVLNode * x) //对 AVL 里的结点 x 进行左单旋
{
	struct AVLNode * y = x->right;

	x->right = y->left;// ① y 的左孩子 c 成为 x 的右孩子

	y->left = x; // ③ x 成为 y 的左孩子


	x->height = max(Get_Height(x->left), Get_Height(x->right)) + 1; // 更新节点高度
	y->height = max(Get_Height(y->right), Get_Height(x)) + 1;

	return y; // 返回这片子树的新根节点：y
}

/*-----------------------------------------------------------
|     x           y          右旋 Rotate_right(x)
|    / \   ==>   / \
|   y   c       a   x        ① y 的右孩子 b 成为 x 的左孩子，
|  / \             / \       ② y 成为新子树的根，
| a   b           b   c      ③ x 成为 y 的右孩子。
-----------------------------------------------------------*/

struct AVLNode * Right_Rotation(struct AVLNode *x)//对 AVL 里的结点 x 进行右单旋
{
	struct AVLNode * y = x->left;

	x->left = y->right; // ① y 的右孩子 b 成为 x 的左孩子，

	y->right = x; //③ x 成为 y 的右孩子。

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
	/*Left_Rotation(x->left); // 先对 x 的左儿子 y 进行左旋
	return Right_Rotation(x->left);*/ // 再对 x 的左儿子 z 进行右旋，返回的是子树的根 z
	Left_Rotation(x->left);
	return Right_Rotation(x);
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
	return Left_Rotation(x);
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

struct AVLNode * AVTree_Delete(AVLTree root, struct AVLNode * x) //从以 root 为根的 AVL 中删除结点 x
{
	if (root == NULL || x == NULL)
		return NULL;

	if (x->key < root->key)        // 待删除的节点在 root 的左子树中
	{
		root->left = AVTree_Delete(root->left, x);
		// 删除节点后，若AVL树失去平衡，则进行相应的调节。
		if (Get_Height(root->right) - Get_Height(root->left) == 2)
		{
			struct AVLNode *r = root->right;
			if (Get_Height(r->left) > Get_Height(r->right))
				root = Right_Left_Rotation(root); // 删除的节点在左子树的右边，双旋
			else
				root = Left_Rotation(root); // 删除的节点在左子树的左边，单旋
		}
	}

	else if (x->key > root->key)// 待删除的节点在 root 的右子树中
	{
		root->right = AVTree_Delete(root->right, x);
		// 删除节点后，若AVL树失去平衡，则进行相应的调节。
		if (Get_Height(root->left) - Get_Height(root->right) == 2)
		{
			struct AVLNode *l = root->left;

			if (Get_Height(l->right) > Get_Height(l->left))
				root = Left_Right_Rotation(root);// 删除的节点在右子树的左边，双旋
			else
				root = Right_Rotation(root);// 删除的节点在左子树的左边，单旋
		}
	}

	else    // root是对应要删除的节点。
	{
		// root 有两个孩子，删后继
		if ((root->left) && (root->right))
		{
			if (Get_Height(root->left) > Get_Height(root->right))
			{
				// 如果root的左子树比右子树高；  
				struct AVLNode * max = Maximum(root->left); // 则找出 root 的左子树中的最大节点
				root->key = max->key; // 将该最大节点的值赋值给root
				root->left = AVTree_Delete(root->left, max); // 删除该最大节点。
			}
			else
			{
				// 如果root的左子树不比右子树高，
				struct AVLNode * min = Minimum(root->right); // 找出root的右子树中的最小节点
				root->key = min->key; // 将该最小节点的值赋值给root。
				root->right = AVTree_Delete(root->right, min); // 删除该最小节点。
			}
		}
		// 如果一个子女，用那个子女替代即可；如果没有子女，直接删除即可
		else
		{
			struct AVLNode * tmp = root;
			root = root->left ? root->left : root->right;
			free(tmp);
		}
	
	}
	if (root != NULL)
		root->height = max(Get_Height(root->left), Get_Height(root->right)) + 1; // 调整高度

	return root;
}

void Delete_node_with_key(AVLTree * root, int key)
{
	struct AVLNode * node = Tree_Search(*root, key);
	if (node == NULL) {
		printf("key %d is not exist!\n", key);
		return;
	}
	*root = AVTree_Delete(*root, node);
}

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

void Build_a_AVLTree(AVLTree * root, int a[], int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		*root = AVLTree_Insert(*root, a[i]);
	}
}

int data[100005];

int main()
{
	int i;
	int n;
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%d", &data[i]);
	}

	AVLTree root = NULL;
	Build_a_AVLTree(&root, data, n);

	int m, op;
	struct AVLNode * x = NULL;
	scanf("%d", &m);
	for (i = 0; i < m; i++)
	{
		scanf("%d", &op);
		if (op == 1)
		{
			x = Maximum(root);
			if (x == NULL) printf("-1\n");
			else 
				printf("%d %d\n", x->key, 
					Tree_Search_Get_Depth(root, x->key));

			root = AVTree_Delete(root, x);
		}
		else if (op == 2)
		{
			x = Minimum(root);
			if (x == NULL) printf("-1\n");
			else
				printf("%d %d\n", x->key,
					Tree_Search_Get_Depth(root, x->key));

			root = AVTree_Delete(root, x);
		}
		else if (op == 3)
		{
			int key;
			scanf("%d", &key);
			root = AVLTree_Insert(root, key);
		}
	}
	return 0;
}
