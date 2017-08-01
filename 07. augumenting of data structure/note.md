# 数据结构的扩张

在实际应用环境中，需要一些标准的数据结构。最基本，最单纯的数据结构可能满足不了需求，但我们很少创建全新的数据结构，而是扩张已有的数据结构，使其包含新的内容，为其添加新的操作，来符合我们对数据结构更高的要求。本章讨论数据结构扩张的理论，以及两种以红黑树扩充而来的数据结构。

# 对一种数据结构扩张的步骤

1. 选择基础的数据结构
2. 确定要添加哪些信息
3. 验证可用基本数据结构的基础操作来维护这些新添加的信息
4. 设计新的操作

# 动态顺序统计

顺序统计（order statistics）的概念已经介绍过了，即在包含 n 个元素的集合中，第 i 个顺序统计量就是该集合中第 i 小关键字的集合。在一个给定的静态集合中，任意的顺序统计量都可以在 O(n) 时间内找到。动态顺序统计（dynamic order statistics）与前者的区别就是序列不再是一次性给出，而是在一个动态集合中，不仅需要求顺序统计量，还有增删查这样的动态集合基本操作。为了实现这个功能，一般不设计一个全新的数据结构，而是扩张数据结构。

我们修改一个支持动态集合操作的基础数据结构，使其能支持快速顺序统计量操作。根据上面数据扩张的理论，四步操作为：

1. 我们选择红黑树作为基础数据结构。
2. 每个结点除了 color、key、left、right、parent 之外，新增**size**域，这个域的内容 size[x] 是**以结点 x 为根的子树的结点（包括 x 本身）数**，即子树的大小。且定义 nil 的 size 为 0 。用递推公式算出各个结点的 size：`size[x] = size[left[x]] + size[right[x]] + 1`。可以看到，第二步是扩充数据结构时最需要发挥创造力和头脑的地方。
3. 对信息的维护。验证 Insert 和 Delete 操作能够更新 size 域。设计扩充的 DS 时，不仅设计新增的功能，**更重要的是维护先前已有的功能**。在给定每个结点的 size 域之后，能够很快的算出顺序统计信息，但我们要验证红黑树上的基本操作能对 size 域进行**有效的维护**，否则，就不能达到期望的目标。
4. 新的操作就是找出顺序统计树 T 中的第 i 小关键字，`OS_Select(root T, int i);`

## 数据结构修改

~~~
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
	int size;
};



typedef struct RBNode * RBTree;

struct RBNode Nil = { BLACK, -9999, NULL, NULL, NULL, 0 };
struct RBNode *nil = &Nil;//哨兵值 
~~~

## 对子树规模的维护

- Insert

插入有两个阶段，第一个阶段从树根开始，沿着树下降，将新节点插入到某个位置。路上经过的所有节点为其 size 加 1，时间复杂度为 O(log n)。第二个阶段沿树上升，做一些颜色修改和旋转以保持红黑树性质。会影响 size 域的操作仅有旋转操作，因为它会改变树的结构。所以要在 `Rotate_left` 函数末尾增加：

~~~
y->size = x->size;
x->size  = x->left->size + x->right->size + 1;
~~~

`Rotate_right` 的末尾改动与上面的是对称的。因为红黑树插入后的`RBTree_Insert_Fixup`至多执行两次旋转，因此第二阶段更新 size 域只需 O(1) 时间。总共需要 O(log n) 时间。

- Delete

删除同样有两个阶段，第一个阶段从树根开始寻找一条到被删除节点 y 的路径，则路径上所有节点的 size 减 1，时间复杂度为 O(log n)。第二个阶段采取与 Insert 同样的方法处理，因为删除的旋转次数也是 O(1) 次，因此包括了维护 size 域的插入删除操作依然是 O(log n) 的时间效率。

## 新增操作

~~~

/*~~~~~~~~~~~~~~~~~~~~~~dynamic order statistics~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
struct RBNode * OS_select(RBTree root, int i) // 寻找一个以 root 为根的子树中的包含第 i 小的结点的指针
{
	int r = root->left->size + 1;
	if (i == r)
		return root;
	else if (i < r)
		return OS_select(root->left, i);
	else
		return OS_select(root->right, i - r);
}

int OS_rank(RBTree root, struct RBNode * x) // 确定一个元素 x 的秩（对 root 中序遍历后得到的序列中 x 的位置）
{
	int r = x->left->size + 1;
	struct RBNode * y = x;

	while (y != root) {
		if (y == y->parent->right) // 如果这个元素不是根节点，并处于右子树上
			r = r + y->parent->left->size + 1;
		y = y->parent;
	}
	return r;
}

~~~

# 区间树

扩张红黑树以支持由**区间**构成的动态集合上的操作。这里操作的区间我们认为是**闭区间**，因为结论扩张到开区间很容易。

把一个闭区间 [t1,t2] 表示成一个对象 i， t1 是 i 的低端点，t2 是 i 的高端点。根据上面数据扩张的理论，四步操作为：

1. 我们选择红黑树作为基础数据结构。
2. 每个结点除了 color、key、left、right、parent 之外，新增**low、high、max**域，分别代表结点 i 的低端点、高端点、以 i 为根的子树中所有区间的高端点的最大值。
3. 对信息的维护。`max[x] = max(high[x], max[left[x]], max[right[x]])`
4. 设计新的操作，是 `Interval_Search(root T, struct Node * i);`，用来找到树 T 覆盖区间 i 的一个结点，如果找不到，则返回一个 nil。删除操作任然是 O(log n) 的时间效率。

## 数据结构修改

~~~
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
	int low;
	int high;
	int max;
};

typedef struct RBNode * RBTree;

struct RBNode Nil = { BLACK, -9999, NULL, NULL, NULL, 0, 0, 0 };
struct RBNode *nil = &Nil;//哨兵值 
~~~

## 对 max 的维护

在插入和删除后添加`max[x] = max(high[x], max[left[x]], max[right[x]])` 即可，因此插入删除操作依然是 O(log n) 的时间效率。

## 新增操作

~~~
struct Node * Interval_Search(RBTree root, struct RBNode * i) // 返回树 root 中与区间 i 覆盖的结点，如果不存在会返回 nil
{
    struct Node * x = root;
    while( x != nil && (i->low > x->high || i->high < x->low)) { // x 不为 nil 且 x 与 i 不重叠
        if(x->left != nil && (x->left->max > i->low || x->left->max == i->low))
            x = x->left;
        else
            x = x->right;
    }
    return x;
}
~~~