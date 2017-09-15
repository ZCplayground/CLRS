#include<stdio.h>
#include<stdlib.h>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 100
#define INFINITY 65535/*65535被为int类型最大值，定义为"无穷大"*/ 
typedef char VertexType;/*顶点类型char*/
typedef int Arc;/*边的类型为int*/
typedef int Status;

typedef struct MGragh {
	VertexType Vexs[MAXSIZE];/*定义顶点表*/
	Arc Edge[MAXSIZE][MAXSIZE];/*定义边数组*/
	int EdgeNum;
	int VexsNum;
}MGragh;

/*创建无向网图*/
void CreateMGragh(MGragh *G) {
	int i = 0, j = 0, k = 0, wet = 0;/*i,j,j做循环变量,wet为边的权值*/
	char ch;
	/*用户输入，获取顶点数，边数*/
	printf("请输入顶点数和边数\n");
	scanf_s("%d%d", &G->VexsNum, &G->EdgeNum);
	ch = getchar();/*上面的顶点数和边数输入完成后，会按一次enter键，这里的ch用于"吸收"enter防止对下一步输入造成影响*/
				   /*对边数组进行初始化*/
	for (i = 0; i<G->VexsNum; i++) {
		for (j = 0; j<G->VexsNum; j++)
			G->Edge[i][j] = INFINITY;
	}
	/*用户输入，生成顶点数组*/
	printf("请输入顶点信息(char类型)\n");
	for (i = 0; i<G->VexsNum; i++) {
		scanf_s("%c", &G->Vexs[i]);
		ch = getchar();
	}
	/*用户输入,为各条边赋权值*/
	for (k = 0; k<G->EdgeNum; k++) {
		printf("请输入(vi,vj)边的下标i,j和权值w");
		scanf_s("%d%d%d", &i, &j, &wet);
		ch = getchar();
		G->Edge[i][j] = wet;
		G->Edge[j][i] = G->Edge[i][j];/*由于是无向图，为对称矩阵，可用此法创建边数组*/
	}
}

/*在屏幕上显示邻接矩阵*/
void DispMGragh(MGragh *G) {
	int i = 0, j = 0;
	printf("G含有%d个顶点,%d条边\n", G->VexsNum, G->EdgeNum);
	printf("打印顶点表信息\n");
	for (i = 0; i<G->VexsNum; i++)
		printf("%c ", G->Vexs[i]);
	printf("各节点相连情况\n");
	for (i = 0; i<G->VexsNum; i++) {
		printf("[%d]\t", i);
		for (j = 0; j<G->VexsNum; j++) {
			if (G->Edge[i][j] == INFINITY)
				printf("∞\t");
			else
				printf("%d\t", G->Edge[i][j]);
		}
		printf("\n");
	}
}

int main(void) {
	MGragh G;
	CreateMGragh(&G);
	DispMGragh(&G);
}
