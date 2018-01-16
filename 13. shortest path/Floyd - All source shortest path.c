#include<iostream>
using namespace std;
int n, m; //n个节点 m条边
int map[205][205];//邻接矩阵
int min(int a, int b)
{
	return a < b ? a : b;
}
int main()
{
	while (scanf("%d%d", &n, &m) != EOF)
	{
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (i == j)map[i][j] = 0;
				else map[i][j] = 1e9;
	

		for (int i = 1; i <= m; i++)//输入m条路
		{
			int x, y, z; scanf("%d%d%d", &x, &y, &z);
			//节点 x 到节点 y 有一条路，权是 z
			map[x][y] = min(z, map[x][y]);//无向边存小的
			map[y][x] = min(z, map[y][x]);
		}
		int s, t;//起点 终点
		scanf("%d%d", &s, &t);
		for (int k = 0; k < n; k++)
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					map[i][j] = min(map[i][j], map[i][k] +map[k][j]);

		if (map[s][t] == 1e9) cout << "-1" << endl;
		else cout << map[s][t] << endl;//最短路
	}
	return 0;
}
