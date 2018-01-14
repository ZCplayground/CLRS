
//Prim：从已构造的 MST 上连接一条最小的边（轻边）不断扩造MST
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
vector<edge> G[MAXN]; // G[i]是一个 vector，存那个点关联的边。可以理解为邻接表
bool vis[MAXN];// 该节点在算法中是否被访问过
int n, m;// n 个节点 m 条边

long long prim()
{
	long long res = 0;//MST 的权值合
	vis[1] = 1;//要随便选一个点作为起始点，就选 1
	for (int i = 0; i < G[1].size(); i++)
		que.push(G[1][i]); // 先将 节点 1 的所有相邻边压入优先队列

	while (que.size()) // 优先队列不为空
	{
		edge e = que.top(); //轻边
		que.pop();

		if (vis[e.to])continue; // 如果这条边的另一侧已经在MST内了，就continue
		//否则，将这个点加入最小生成树，这点的邻边压入优先队列
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
		memset(vis, 0, sizeof(vis));//初始化别忘了

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
