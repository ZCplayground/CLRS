#include<cstdio>
#include<algorithm>
#define MAXN 111 

struct edge {
	int from, to;
	int cost;
}E[MAXN*MAXN];

bool cmp(edge a, edge b)
{
	return a.cost < b.cost;
}

int n, m; // n 个点 m 条边

//并查集
int fa[MAXN];
void init()
{
	for (int i = 1; i <= n; i++) // 这一份代码里所有下标从1开始
		fa[i] = i;
}

int find(int x)
{
	if (x == fa[x])return x;
	return fa[x] = find(fa[x]);
}

void Union(int x, int y)
{
	int p1 = find(x), p2 = find(y);
	if (p1 == p2)return;
	fa[p1] = p2;
}

bool same(int x, int y)
{
	return find(x) == find(y);
}

long long Kruskal()//求最小生成树的权值和
{
	long long res = 0;
	//将边排序，然后贪心地取，看一下边连接的两个点是否在同一个并查集中
	std::sort(E + 1, E + 1 + m, cmp);
	for (int i = 1; i <= m; i++)
	{
		if (same(E[i].from, E[i].to)) continue;
		Union(E[i].from, E[i].to);
		res += E[i].cost;
	}	
	return res;
}

int main()
{
	while (scanf("%d%d", &m, &n) == 2)
	{
		if (m == 0)break;
		init();//并查集初始化
		for (int i = 1; i <= m; i++)
			scanf("%d%d%d", &E[i].from, &E[i].to, &E[i].cost);
		
		long long res = Kruskal();

		// 可能是不连通，那么在生成树生成之后，看一下所有点是不是和节点1都是同一个集合的
		for (int i = 1; i <= n; i++)
			if (!same(i, 1))
				res = -1;

		if (res == -1)
			printf("?\n");//有不连通部分
		else
			printf("%lld\n", res);
	}
	return 0;
}
