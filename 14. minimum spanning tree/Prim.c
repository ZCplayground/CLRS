
//Prim�����ѹ���� MST ������һ����С�ıߣ���ߣ���������MST
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>

#define MAXN 105
using namespace std;

struct edge {
	int to;
	long long cost;
	edge(int tt, long long cc) :to(tt), cost(cc) {}
	edge() {}
	bool operator<(const edge &a) const {
		return a.cost < cost;
	}
};

priority_queue<edge> que;
vector<edge> G[MAXN]; // G[i]��һ�� vector�����Ǹ�������ıߡ��������Ϊ�ڽӱ�
bool vis[MAXN];// �ýڵ����㷨���Ƿ񱻷��ʹ�
int n, m;// n ���ڵ� m ����

long long prim()
{
	long long res = 0;//MST ��Ȩֵ��
	vis[1] = 1;//Ҫ���ѡһ������Ϊ��ʼ�㣬��ѡ 1
	for (int i = 0; i < G[1].size(); i++)
		que.push(G[1][i]); // �Ƚ� �ڵ� 1 ���������ڱ�ѹ�����ȶ���

	while (que.size()) // ���ȶ��в�Ϊ��
	{
		edge e = que.top(); //���
		que.pop();

		if (vis[e.to])continue; // ��������ߵ���һ���Ѿ���MST���ˣ���continue
		//���򣬽�����������С�������������ڱ�ѹ�����ȶ���
		vis[e.to] = 1;
		res += e.cost;
		for (int i = 0; i < G[e.to].size(); i++)
			que.push(G[e.to][i]);
	}
	return res;
}

int main()
{
	while (scanf("%d%d", &m, &n) == 2) {
		if (m == 0)break;
		for (int i = 0; i <= n; i++) 
			G[i].clear();
		while (que.size())que.pop(); 
		memset(vis, 0, sizeof(vis));//��ʼ��������

		for (int i = 1; i <= m; i++)
		{
			int u, v;
			long long cost;
			scanf("%d%d%lld", &u, &v, &cost);
			G[u].push_back(edge(v, cost));
			G[v].push_back(edge(u, cost));
		}

		long long res = prim();
		for (int i = 1; i <= n; i++)
			if (!vis[i])res = -1;
		if (res == -1)printf("?\n");
		else printf("%lld\n", res);
	}
	return 0;
}
