在**平摊分析**（amortized analysis）中，一系列操作所需要时间是通过对执行的所有的操作**求平均**得到的。平摊分析**可以用来证明在一系列操作中，即使某一单一操作具有较大的代价，整体平均代价依旧是比较小的**。平摊分析与平均情况下的复杂度分析的不同之处在于，它不涉及到概率。平摊分析保证了在最坏情况下，平均下来，每个操作具有一个平均性能。

# 例子：动态表

在某些应用中，无法预知要在表中存储多少个对象（eg：动态内存分配）。为表分配了空间，到后面不够用，就要重新为该表分配一个更大的空间，并将原表的对象赋值到更大空间的表中。这个操作中，我们要研究动态表的扩展和收缩过程，通过利用平摊分析，来证明插入和删除操作的**平摊代价**仅为 O(1) ，即使插入和删除操作引起了表的扩张和收缩而导致的实际代价较大时，也是如此。

当一个表中的所有槽（slot）都被占用时，或者说，装载因子（load factor，是 hash table 中的一个概念）等于 1 时，这个表就被装满了。一个常用的启发式方法是：**分配一个是原表两倍槽数的新表。**。如果只执行插入操作，则表的装载因子始终最少为 1/2，被浪费的空间始终不超过表空间的一半。

伪代码：

~~~
TABLE-INSERT(T, x)

if size[T] = 0
    then allocate table[T] with 1 slot
         size[T] = 1

if num[T] = size[T]  // 溢出
    then allocate a new-table with 2 * size[T] slots
         insert all items in table[T] into new-table
         free table[T]
         table[T] = new-table
         size[T] *= 2
insert x into table[T]
num[T]++
~~~

下面来分析动态表的 TABLE-INSERT 操作代价，设第 i 次操作的代价为 ci。

- 如果当前表还有空间，或者该操作是第一个操作的话，则 ci = 1。
- 如果当期表是满的，则会发生一次扩张，则 ci = i

以之前寻常的分析方法来分析复杂度的话，发生扩张时，由于要进行复制操作，代价为 i。如果执行了 n 次操作，则一次操作的**最坏情况**代价为 O(n)，由此可得 n 次 INSERT 的**运行时间上界**是 O(n^2) 。加粗的部分都是我们之前寻常的思考方式，固然没错。不过，**这个上界很不切确**，因为执行 n 次 INSERT 中，**并不会经常包括出现表扩展的情况**。经过分析可得：**仅当 i - 1 是 2 的整数幂时，第 i 次操作才会引发一次表扩张。**

$$ c_i = \begin{cases}
i,  & \text{如果 i-1 是 2 的整数幂} \\
1, & \text{否则}  \\
\end{cases} $$ 

由此，n 次 INSERT 的**总代价**为：

$$ \sum_{i=1}^n \le n + \sum_{j=0}^{\lfloor{lg n}} \lt n + 2n = 3n  $$

总代价为 **θ(n)**。第一项是小于等于 n 个 1 也就是n， 没什么疑问。第二项是 lg n 级别的表扩展操作，是一个几何级数（等比数列求和），用公式可求结果是 2n。下面是平摊分析方法：**TABLE-INSERT 的操作总代价为 3n ，因为有 n 次操作，故单一一次的平摊代价为 3。**平摊分析，不涉及概率，却能给出一个序列的某一操作的时间效率下界。

# 平摊分析的分析方法

aggregate analysis、accounting、potential method

## 聚集分析

aggregate analysis

证明对所有的 n 由 n 个操作构成的序列最坏情况下为 T(n) 。因此在最坏情况下的每个操作平均代价为 T(n) / n。

栈操作：push、pop，这两种基本的栈操作，时间代价为 O(1)。考虑一个新操作：`multipop(S,k)`，作用是弹出栈 S 的 k 个栈顶对象。

~~~
MULTIPOP(S, k)

while not STACK-EMPTY(S) and k != 0
    do POP(S)
    k--
~~~

这个操作的运行时间是多少？只要按 push 和 pop 具有抽象代价 1 来分析就足够了。设栈 S 中实际包含 s 个对象，则 while 的次数就是 min(s,k)，总代价也就是 min(s,k)。线性关系。

**分析一个由 n 个 push、pop、multipop 操作构成的操作序列，作用于一个初始为空的栈 S**。序列中一个 multipop 的最坏代价为 O(n)，所以任意单个操作的最坏情况为 O(n)，n 个操作的代价就是 O(n^2)。学了平摊分析，可以明显的知道，这个上界是不确切的。

利用聚集分析，分析一系列操作的**最坏情况下总时间**。事实上，虽然一次 multipop 的操作代价可能较高。但一个由 n 个 push、pop、multipop 操作构成的操作序列，作用在一个初始为空的栈上时，代价至多为 O(n)，因为**一个对象被压入栈中，至多被弹出一次**。pop 的次数（包括 multipop 里调用的 pop）至多等于 push 的次数，也就是至多为 n。因此总时间为 O(n)。则平摊代价为 T(n)/n = O(1)。

可以看到，证明了平均代价是 O(1)，但没有用到概率推理。

## 记账方法

accounting

对不同的操作赋予不同的**费用**，某些操作的费用会比它们的实际代价或多或少。都一个操作的收费数量称为**平摊代价**。当平摊代价超过实际代价，超额部分被收为**存款**（credit）。存款（可以理解为存在银行里）在以后用于补偿那些其平摊代价低于实际代价的操作。**总存款必须始终非负**，如果总存款允许是负，则这是总平摊代价会低于总实际代价，而按理来说总平摊代价应该是总实际代价的一个上界，不合理。

采用记账方法来分析动态表，我们可以对为什么一次 INSERT 的平摊代价是 3 有一定理解。

- 对每一次插入操作收费 3 元
    - 随即发生的基本插入代价为 1 元（意即像数组插入一个元素要支付 1 元）
    - 另有 1 元放在刚插入的元素上作为存款
    - 余下 1 元放在已在表中的 m/2 个项中的某一个作为存款（填满该表还需要 m/2 - 1 次插入）

- 到了该表包含了 m 个项（已满）时，每一项上**都有 1 元钱来支付表扩张的再次插入操作费用。**

## 势能分析

potential method

不是用存款来表示预付工作、支付未来的工作，而是将其表示成一种**势能**，它在需要的时候可以释放出来。势是与整个数据结构而不是与个别对象发生联系的。

# 总结

平摊分析为数据结构的性能分析提供了一个简介的抽象模型，例如可以以平摊分析来推断动态表的操作效率为 θ(n)。如果你只关注聚集效应，即使有的时候操作会有些复杂。

三种方法：记账分析、聚集分析、势能分析