#include <iostream>  
#include <queue>  
using namespace std;
const int maxn = 205; //最大节点数

vector <pair<int,int>>E[maxn]; //边集
int n, m; // n 个点 m条边
int s, t; // source 和 终点
int dis[maxn]; //从源点到各个点的最短距离
void Init()
{
	for (int i = 0; i<maxn; i++)
	{
		E[i].clear();
		dis[i] = 1e9;
	}
}
void Dijkstra()
{
	priority_queue<pair<int, int>>q;
	dis[s] = 0;
	q.push(make_pair(-dis[s], s));

	while (!q.empty())
	{
		int p = q.top().second;
		q.pop();
		for (int i = 0; i<E[p].size(); i++)
		{
			int v = E[p][i].first;
			if (dis[v]>dis[p] + E[p][i].second)
			{
				dis[v] = dis[p] + E[p][i].second;
				q.push(make_pair(-dis[v], v));
			}
		}
	}
}
int main()
{
	while (cin >> n >> m)
	{
		Init();
		for (int i = 0; i<m; i++)
		{
			int x, y, z;
			cin >> x >> y >> z; // x 到 y 有一条权为 z 的双向边
			E[x].push_back(make_pair(y, z));
			E[y].push_back(make_pair(x, z));
		}
		cin >> s >> t;
		Dijkstra();
		if (dis[t] == 1e9)
			cout << "-1" << endl;
		else
			cout << dis[t] << endl;
	}
	return 0;
}
