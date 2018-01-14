#include <iostream>  
#include <queue>  
using namespace std;
const int maxn = 205; //���ڵ���

vector <pair<int,int>>E[maxn]; //�߼�
int n, m; // n ���� m����
int s, t; // source �� �յ�
int dis[maxn]; //��Դ�㵽���������̾���
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
			cin >> x >> y >> z; // x �� y ��һ��ȨΪ z ��˫���
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
