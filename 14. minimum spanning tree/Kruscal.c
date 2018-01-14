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

int n, m; // n ���� m ����

//���鼯
int fa[MAXN];
void init()
{
	for (int i = 1; i <= n; i++) // ��һ�ݴ����������±��1��ʼ
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

long long Kruskal()//����С��������Ȩֵ��
{
	long long res = 0;
	//��������Ȼ��̰�ĵ�ȡ����һ�±����ӵ��������Ƿ���ͬһ�����鼯��
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
		init();//���鼯��ʼ��
		for (int i = 1; i <= m; i++)
			scanf("%d%d%d", &E[i].from, &E[i].to, &E[i].cost);
		
		long long res = Kruskal();

		// �����ǲ���ͨ����ô������������֮�󣬿�һ�����е��ǲ��Ǻͽڵ�1����ͬһ�����ϵ�
		for (int i = 1; i <= n; i++)
			if (!same(i, 1))
				res = -1;

		if (res == -1)
			printf("?\n");//�в���ͨ����
		else
			printf("%lld\n", res);
	}
	return 0;
}
