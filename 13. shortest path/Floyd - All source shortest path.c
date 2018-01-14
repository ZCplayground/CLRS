
#include<iostream>
using namespace std;
int n, m; //n���ڵ� m����
int map[205][205];//�ڽӾ���
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
				else map[i][j] = 22222;
	

		for (int i = 1; i <= m; i++)//����m��·
		{
			int x, y, z; scanf("%d%d%d", &x, &y, &z);
			//�ڵ� x ���ڵ� y ��һ��·��Ȩ�� z
			map[x][y] = min(z, map[x][y]);//����ߴ�С��
			map[y][x] = min(z, map[y][x]);
		}
		int s, t;//��� �յ�
		scanf("%d%d", &s, &t);
				for (int k = 0; k < n; k++)
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					map[i][j] = min(map[i][j], map[i][k] +map[k][j]);

		if (map[s][t] == 22222) cout << "-1" << endl;
		else cout << map[s][t] << endl;//���·
	}
	return 0;
}
