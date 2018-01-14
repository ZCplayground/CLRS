DFS遍历:
#include<iostream>using namespace std;
int graph[100][100];
bool  visit[100];
void DFS(int v, int n)
{
	visit[v] = true;
	printf("%d ", v);
	for (int i = 0; i < n; i++)
	{
		if (graph[v][i] == 1 && visit[i] == false)
		{
			DFS(i, n);
		}
	}
}
void init_visit(int n)
{
	for (int i = 0; i < n; ++i)
	{
		visit[i] = false;
	}
}
int main()
{
	int n;
	cout << "输入顶点数：" << endl;
	cin >> n;
	cout << "输入图的邻接矩阵：" << endl;
	int f;
	for (int i = 0; i< n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			cin >> f;
			graph[i][j] = f;
		}
	}
	init_visit(n);
	int cnt = 0;
	cout << "DFS序列为：" << endl;
	for (int i = 0; i < n; ++i)
	{
		if (visit[i] == false)
		{
			DFS(i, n);
			cnt++;
		}
	}
	cout << endl;
	cout << "该图联通分量：" << cnt << endl;
	return 0;
}

