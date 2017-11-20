//�Լ�ģ���㷨����������
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
|     x             y        ���� Rotate_left(x,T); a��b��c ������
|    / \    ==>    / \
|   a   y         x   c      �� y ������ b ��Ϊ x ���Һ��ӣ�
|      / \       / \         �� y ��Ϊ�������ĸ���
|     b   c     a   b        �� x ��Ϊ y �����ӡ�
----------------------------------------------------------------*/

struct AVLNode * Left_Rotation(struct AVLNode * x) //�� AVL ��Ľ�� x ��������
{
	struct AVLNode * y = x->right;

	x->right = y->left;// �� y ������ c ��Ϊ x ���Һ���

	//if (y->left != NULL)
	//	y->left->parent = x; // ��� y �������� b ��Ϊ NULL �Ļ����ı� b �ĸ����Ϊ x

	//y->parent = x->parent; // �� y ��Ϊ�������ĸ�

//if (x == x->parent->left) // ���� y �ĸ������ָ���ϵ
	//	x->parent->left = y;
	//else
	//	x->parent->right = y;

	y->left = x; // �� x ��Ϊ y ������
	//x->parent = y;

	x->height = max(Get_Height(x->left), Get_Height(x->right)) + 1; // ���½ڵ�߶�
	y->height = max(Get_Height(y->right), Get_Height(x)) + 1;

	return y; // ������Ƭ�������¸��ڵ㣺y
}


/*-----------------------------------------------------------
|     x           y          ���� Rotate_right(x,T)
|    / \   ==>   / \
|   y   c       a   x        �� y ���Һ��� b ��Ϊ x �����ӣ�
|  / \             / \       �� y ��Ϊ�������ĸ���
| a   b           b   c      �� x ��Ϊ y ���Һ��ӡ�
-----------------------------------------------------------*/

struct AVLNode * Right_Rotation(struct AVLNode *x)//�� AVL ��Ľ�� x �����ҵ���
{
	struct AVLNode * y = x->left;

	x->left = y->right; // �� y ���Һ��� b ��Ϊ x �����ӣ�

	//if (y->right != NULL)
	//	y->right->parent = x;

	//y->parent = x->parent;// �� y ��Ϊ�������ĸ���
	// 
	//if (x->parent->left == x)
	//	x->parent->left = y;
	//else
	//	x->parent->right = y;

	y->right = x; //�� x ��Ϊ y ���Һ��ӡ�
	//x->parent = y;

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
	Left_Rotation(x->left); // �ȶ� x ������� y ��������
	return Right_Rotation(x->left); // �ٶ� x ������� z �������������ص��������ĸ� z
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
	return Left_Rotation(x->right); 
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

/*struct AVLNode * Tree_Succeccor(AVLTree root, struct AVLNode * x)//Ѱ���� root Ϊ�������еĽ�� x ��������������ĺ��
{
	if (x->right != NULL)//������ x ���������ǿգ��� x �ĺ�̼�����������С���
		return Minimum(x->right);

	struct AVLNode * y = x->parent;
	while (y != NULL && x == y->right)//���û������������һֱ����Ѱ�ң�ֱ������ĳ�����丸������ӽ�㣨����root��Ϊֹ
	{
		x = y;
		y = y->parent;
	}
	return y;
}*/

/*struct AVLNode * Tree_Predecessor(AVLTree root, struct AVLNode *x)//Ѱ���� root Ϊ�������еĽ�� x ���������������ǰ��
{
	if (x->left != NULL)//������ x ���������ǿգ��� x ��ǰ�����������������
		return Maximum(x->left);

	else return x->parent;//���򸸽�������ǰ��
}*/

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

void Answer_List(AVLTree root, int a[], int b[], int n) // ������� a �����е�Ԫ�������� root Ϊ���� AVL ���е���ȵ� b ������
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