# 插入的写法写成返回结点指针是有原因的。

[在子函数中动态分配内存](http://blog.csdn.net/kelvin_yan/article/details/41596937)
~~~
void GetMemory(char *p, int num)     
{         
        p = (char *)malloc(sizeof(char) * num);  
}   
~~~

这里犯了值传递的错误,虽然p是指针,但对于p本身来说,这里还是值传递.即函数生成了个值和p相同的char*临时变量,为这个临时指针分配了空间,而p并没有改变.  

Tree_Insert 的空树分支错误写法（函数返回值类型 void）：

~~~
if( root == NULL)
{
	root = NewNode(element);
	return;
}
~~~

原因在于root 是传进来的参数，如果不把新分配的地址返回的话，那么这个地址会随着临时变量的消失而不见。root 将一直是 NULL

# 中序遍历BST来排序的时间效率

Ω(nlogn)。最好情况下就是平衡树，树高 nlogn。对最底层的 n/2 个节点的 insert 操作就是 Ω(nlogn) 量级。最差情况：数组几乎已经排好序，那样建树时 BST 会很不平衡，极端为 O(n^2)。

**BST sort 和 quicksort 所作的比较次数一样，只是次序不同。**

# 动态集合 —— BST 的操作效率

search、minumum、maximum、successor、preducessor、insert、delete 的运行时间都为 O(h)， h 为树高。