# Lower boundary on comparision sort

Ω(nlogn)

上述排序算法有一个共同的特点，就是用于排序结果的主要运算时对输入数据的比较运算。这类排序算法称为基于比较的排序算法。基于比较的排序算法计算时间下界是Ω(nlogn)。

证明：

排序算法的决策树。

决策树是一棵二叉树，表示某排序算法作用于给定输入的**所有比较**。作用于有 n 个元素的序列的排序算法，为了保证正确性（任何输入都是可能的，算法正确性的要求就是不管怎样的输入都可以输出排好序的序列），要有 n！ 个叶节点。n！就是 n 个元素的全排列个数

证明：基于比较排序算法的下界是Ω(nlogn)
也就是证明：决策树高度，或者说最长路径的长度 的下界也是Ω(nlogn)，这是因为，高度也就是从根节点到叶节点的**最长路径长度**，基于比较的排序如果是正确的，就一定要能走到这个点。

高度为 h 的话，叶子结点不多于 2^h

2^h ≥ n！

两边取对数、**斯特林公式**

h ≥ log(n!)  =  log(n/e)^n  = nlg(n/e)  = n(lgn - lge) = Ω(nlogn)

# countingsort

带排序数组 A
数组 A 里面的所有元素不大于 k
数组 A 的长度为 len

数组 C 用来存储“某种数值出现的频率”
当C数组输入完成后，C中的数字就告诉原数组的值应该放到哪里。

算法复杂度：第一个和第三个 for 是O(k)  ，第二个和第四个 for 是 O(n)
因此算法复杂度是 O(k+n)

这是一个依赖于 k 的算法。

如果 k 是O(n)，那么总的算法复杂度会是 O(n) 就优于比较排序的下界了。
但如果 k 达到了 O(nlogn)的量级，那计数排序就比快排、合并排序慢

#  radixsort

基数排序利用了计数排序，然后可以克服 计数排序在数的范围很大的情况下效率低的缺点

思路是：给定 n 个 d 位数（或者不超过 d 位的数），每一位数的取值可能是 0 ~ k （例如：二进制是0 ~ 1，十进制是 0 ~ 9），从低位到高位，对每一位进行计数排序。

伪代码：

Radix-sort(A, d)

for i = 1  to  d
	do use a stable sort to sort array A on digit i
	
算法复杂度是 d 遍的计数排序，也就是 O(d(n+k))，不一定要用计数排序，用任何线性时间的排序算法就行。


迭代地取个位数、十位数、、、、各个位的数字的方法：

~~~
temp = (int)pow(10, looptimes);
index = (num / temp) % 10;

//如798
//个位index=(798/1)%10=8
//十位index=(798/10)%10=9
//百位index=(798/100)%10=7
//tempNum为上式中的1、10、100

~~~