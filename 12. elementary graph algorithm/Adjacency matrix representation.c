#include<stdio.h>
#include<stdlib.h>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 100
#define INFINITY 65535/*65535��Ϊint�������ֵ������Ϊ"�����"*/ 
typedef char VertexType;/*��������char*/
typedef int Arc;/*�ߵ�����Ϊint*/
typedef int Status;

typedef struct MGragh {
	VertexType Vexs[MAXSIZE];/*���嶥���*/
	Arc Edge[MAXSIZE][MAXSIZE];/*���������*/
	int EdgeNum;
	int VexsNum;
}MGragh;

/*����������ͼ*/
void CreateMGragh(MGragh *G) {
	int i = 0, j = 0, k = 0, wet = 0;/*i,j,j��ѭ������,wetΪ�ߵ�Ȩֵ*/
	char ch;
	/*�û����룬��ȡ������������*/
	printf("�����붥�����ͱ���\n");
	scanf_s("%d%d", &G->VexsNum, &G->EdgeNum);
	ch = getchar();/*����Ķ������ͱ���������ɺ󣬻ᰴһ��enter���������ch����"����"enter��ֹ����һ���������Ӱ��*/
				   /*�Ա�������г�ʼ��*/
	for (i = 0; i<G->VexsNum; i++) {
		for (j = 0; j<G->VexsNum; j++)
			G->Edge[i][j] = INFINITY;
	}
	/*�û����룬���ɶ�������*/
	printf("�����붥����Ϣ(char����)\n");
	for (i = 0; i<G->VexsNum; i++) {
		scanf_s("%c", &G->Vexs[i]);
		ch = getchar();
	}
	/*�û�����,Ϊ�����߸�Ȩֵ*/
	for (k = 0; k<G->EdgeNum; k++) {
		printf("������(vi,vj)�ߵ��±�i,j��Ȩֵw");
		scanf_s("%d%d%d", &i, &j, &wet);
		ch = getchar();
		G->Edge[i][j] = wet;
		G->Edge[j][i] = G->Edge[i][j];/*����������ͼ��Ϊ�Գƾ��󣬿��ô˷�����������*/
	}
}

/*����Ļ����ʾ�ڽӾ���*/
void DispMGragh(MGragh *G) {
	int i = 0, j = 0;
	printf("G����%d������,%d����\n", G->VexsNum, G->EdgeNum);
	printf("��ӡ�������Ϣ\n");
	for (i = 0; i<G->VexsNum; i++)
		printf("%c ", G->Vexs[i]);
	printf("���ڵ��������\n");
	for (i = 0; i<G->VexsNum; i++) {
		printf("[%d]\t", i);
		for (j = 0; j<G->VexsNum; j++) {
			if (G->Edge[i][j] == INFINITY)
				printf("��\t");
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
