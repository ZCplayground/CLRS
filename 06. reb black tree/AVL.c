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

// ��������������
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

struct AVLNode * Tree_Search(AVLTree root, int key)//Ѱ�Ҹ�Ϊ root �����м�ֵΪ key �Ľ�㡣
{
	if (root == NULL || key == root->key)
		return root;

	struct AVLNode * x = root;//�������
	while (x != NULL && x->key != key) // �ǵݹ�д��
	{
		if (key < x->key)
			x = x->left;
		else
			x = x->right;
	}


	return x;
}

/*---------------------------------------------------------------
|     x             y        ���� Rotate_left(x); a��b��c ������
|    / \    ==>    / \
|   a   y         x   c      �� y ������ b ��Ϊ x ���Һ��ӣ�
|      / \       / \         �� y ��Ϊ�������ĸ���
|     b   c     a   b        �� x ��Ϊ y �����ӡ�
----------------------------------------------------------------*/

struct AVLNode * Left_Rotation(struct AVLNode * x) //�� AVL ��Ľ�� x ��������
{
	struct AVLNode * y = x->right;

	x->right = y->left;// �� y ������ c ��Ϊ x ���Һ���

	y->left = x; // �� x ��Ϊ y ������


	x->height = max(Get_Height(x->left), Get_Height(x->right)) + 1; // ���½ڵ�߶�
	y->height = max(Get_Height(y->right), Get_Height(x)) + 1;

	return y; // ������Ƭ�������¸��ڵ㣺y
}

/*-----------------------------------------------------------
|     x           y          ���� Rotate_right(x)
|    / \   ==>   / \
|   y   c       a   x        �� y ���Һ��� b ��Ϊ x �����ӣ�
|  / \             / \       �� y ��Ϊ�������ĸ���
| a   b           b   c      �� x ��Ϊ y ���Һ��ӡ�
-----------------------------------------------------------*/

struct AVLNode * Right_Rotation(struct AVLNode *x)//�� AVL ��Ľ�� x �����ҵ���
{
	struct AVLNode * y = x->left;

	x->left = y->right; // �� y ���Һ��� b ��Ϊ x �����ӣ�

	y->right = x; //�� x ��Ϊ y ���Һ��ӡ�

	x->height = max(Get_Height(x->left), Get_Height(x->right)) + 1; // ���½ڵ�߶�
	y->height = max(Get_Height(y->left), Get_Height(x)) + 1;

	return y;
}

/*-----------------------------------------------------------------------------
|     x               x                  z           Сд��ĸ x��y��z ����ڵ㣬
|    / \             / \               /   \         ��д��ĸ ABCD ��������
|   y   D           z   D             y     x
|  / \       ==>   / \       ==>     / \   / \
| A   z           y   C             A  B   C  D
|    / \         / \
|   B   C       A   B
------------------------------------------------------------------------------*/

struct AVLNode * Left_Right_Rotation(struct AVLNode *x) //�Բ�ƽ��Ľڵ� x ���� LR ��ת
{
	/*Left_Rotation(x->left); // �ȶ� x ������� y ��������
	return Right_Rotation(x->left);*/ // �ٶ� x ������� z �������������ص��������ĸ� z
	Left_Rotation(x->left);
	return Right_Rotation(x);
}

/*-----------------------------------------------------------------------------
|     x               x                   z          Сд��ĸ x��y��z ����ڵ㣬
|    / \             / \                /   \        ��д��ĸ ABCD ��������
|   A   y           A   z              y     x
|      / \   ==>       / \     ==>    / \   / \
|     z   D           B   y          A  B   C  D
|    / \                 / \
|   B   C               C   D
------------------------------------------------------------------------------*/
struct AVLNode * Right_Left_Rotation(struct AVLNode *x) //�Բ�ƽ��Ľڵ� x ���� RL ��ת��Ҳ���� LR ��ת�ĶԳ����
{
	Right_Rotation(x->right);
	return Left_Rotation(x);
}

AVLTree AVLTree_Insert(AVLTree root, int key) //���Ϊ root �����в���һ����㣬���ֵΪ key
{
	if (root == NULL)
	{
		root = NewNode(key);
	}

	else if (key < root->key)
	{
		root->left = AVLTree_Insert(root->left, key); // �ݹ�д������ΪҪ���ݲ��ϸ��½ڵ�ĸ߶ȡ�����ת

													  // ����ڵ����AVL��ʧȥƽ�⣬�������Ӧ�ĵ��ڡ�
		if (Get_Height(root->left) - Get_Height(root->right) == 2) // �߶Ȳ�ﵽ�� 2����Ҫ����
		{
			// ���鱾 P218

			if (/*root->left==NULL ||*/ key < root->left->key)       // case 1����������ߵ�������
				root = Right_Rotation(root);
			else                             // case 2����������ߵ�������
				root = Left_Right_Rotation(root);
		}
	}

	else if (key > root->key)
	{
		root->right = AVLTree_Insert(root->right, key);

		if (Get_Height(root->right) - Get_Height(root->left) == 2)
		{
			// ͬ��
			if (/*root->right == NULL ||*/ key > root->right->key)
				root = Left_Rotation(root);
			else
				root = Right_Left_Rotation(root);
		}
	}

	else  // ��������ͬ��Ԫ��
	{
		printf("error: already exists!\n");
	}

	root->height = max(Get_Height(root->left), Get_Height(root->right)) + 1;

	return root;
}

struct AVLNode * Minimum(AVLTree root)//Ѱ�Ҹ�Ϊ root �����еļ�ֵ��С�Ľ��
{
	struct AVLNode * x = root;
	while (x->left != NULL)
		x = x->left;

	return x;
}

struct AVLNode * Maximum(AVLTree root)//Ѱ�Ҹ�Ϊ root �� BST �еļ�ֵ���Ľ��
{
	struct AVLNode * x = root;
	while (x->right != NULL)
		x = x->right;

	return x;
}

struct AVLNode * AVTree_Delete(AVLTree root, struct AVLNode * x) //���� root Ϊ���� AVL ��ɾ����� x
{
	if (root == NULL || x == NULL)
		return NULL;

	if (x->key < root->key)        // ��ɾ���Ľڵ��� root ����������
	{
		root->left = AVTree_Delete(root->left, x);
		// ɾ���ڵ����AVL��ʧȥƽ�⣬�������Ӧ�ĵ��ڡ�
		if (Get_Height(root->right) - Get_Height(root->left) == 2)
		{
			struct AVLNode *r = root->right;
			if (Get_Height(r->left) > Get_Height(r->right))
				root = Right_Left_Rotation(root); // ɾ���Ľڵ������������ұߣ�˫��
			else
				root = Left_Rotation(root); // ɾ���Ľڵ�������������ߣ�����
		}
	}

	else if (x->key > root->key)// ��ɾ���Ľڵ��� root ����������
	{
		root->right = AVTree_Delete(root->right, x);
		// ɾ���ڵ����AVL��ʧȥƽ�⣬�������Ӧ�ĵ��ڡ�
		if (Get_Height(root->left) - Get_Height(root->right) == 2)
		{
			struct AVLNode *l = root->left;

			if (Get_Height(l->right) > Get_Height(l->left))
				root = Left_Right_Rotation(root);// ɾ���Ľڵ�������������ߣ�˫��
			else
				root = Right_Rotation(root);// ɾ���Ľڵ�������������ߣ�����
		}
	}

	else    // root�Ƕ�ӦҪɾ���Ľڵ㡣
	{
		// root ���������ӣ�ɾ���
		if ((root->left) && (root->right))
		{
			if (Get_Height(root->left) > Get_Height(root->right))
			{
				// ���root�����������������ߣ�  
				struct AVLNode * max = Maximum(root->left); // ���ҳ� root ���������е����ڵ�
				root->key = max->key; // �������ڵ��ֵ��ֵ��root
				root->left = AVTree_Delete(root->left, max); // ɾ�������ڵ㡣
			}
			else
			{
				// ���root�������������������ߣ�
				struct AVLNode * min = Minimum(root->right); // �ҳ�root���������е���С�ڵ�
				root->key = min->key; // ������С�ڵ��ֵ��ֵ��root��
				root->right = AVTree_Delete(root->right, min); // ɾ������С�ڵ㡣
			}
		}
		// ���һ����Ů�����Ǹ���Ů������ɣ����û����Ů��ֱ��ɾ������
		else
		{
			struct AVLNode * tmp = root;
			root = root->left ? root->left : root->right;
			free(tmp);
		}
	
	}
	if (root != NULL)
		root->height = max(Get_Height(root->left), Get_Height(root->right)) + 1; // �����߶�

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

int Tree_Search_Get_Depth(AVLTree root, int key)//Ѱ�Ҹ�Ϊ root �����м�ֵΪ key �Ľ�㣬����ֵ�Ǹýڵ�����
{
	int depth = 1;
	if (root == NULL || key == root->key)
		return depth;

	struct AVLNode * x = root;//�������
	while (x != NULL && x->key != key) // �ǵݹ�д��
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
