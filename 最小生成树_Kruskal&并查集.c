#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef unsigned int UINT;
typedef int dataType;
typedef void* elemType;
//�ߵĴ洢�ṹ
typedef struct EDGE
{
	UINT weight;//Ȩֵ
	UINT arc[2];//��
}edge;
//��Ϊ��������ĺ���ָ�����
int cmp(const void* a,const void* b)
{
	edge* e1 = (edge*)a,*e2 = (edge*)b;
	if(e1->weight<e2->weight)return -1;
	if(e1->weight==e2->weight)return 0;
	return 1;
}
//���Ⱥϲ�
void union_set(UINT* rank,UINT* parent,UINT a,UINT b)
{
	if(rank[a]>rank[b])parent[b] = a;
	else
	{
		if(rank[a]==rank[b])rank[b]++;
		parent[a] = b;
	}
}
//·��ѹ��
UINT findParent(UINT* parent,UINT a)
{
	if(parent[a] != a)
	{
		a = findParent(parent,parent[a]);
	}
	return a;
}
//��С������Kruskal�㷨
void miniSpanTree_Kruskal(dataType arc[][3],char* adjvex,UINT n,UINT adjvex_num)
{
	UINT i,count = 0,weight = 0,*rank = (UINT*)malloc(sizeof(UINT)*adjvex_num),*parent = (UINT*)malloc(sizeof(UINT)*adjvex_num),a,b;
	edge* e = (edge*)malloc(sizeof(edge)*n),*edges = (edge*)malloc(sizeof(edge)*(adjvex_num-1));
	if(!e||!rank||!parent||!edges)exit(-1);
	memset(rank,0,sizeof(UINT)*adjvex_num);
	for(i=0;i<adjvex_num;i++)
	{
		parent[i] = i;
	}
	for(i=0;i<n;i++)
	{
		e[i].arc[0] = arc[i][0];
		e[i].arc[1] = arc[i][1];
		e[i].weight = arc[i][2];
	}
	qsort(e,n,sizeof(edge),cmp);//��������
	for(i=0;i<n;i++)
	{
		a = findParent(parent,e[i].arc[0]);
		b = findParent(parent,e[i].arc[1]);
		if(a!=b)
		{
			edges[count].arc[0] = e[i].arc[0];
			edges[count].arc[1] = e[i].arc[1];
			edges[count++].weight = e[i].weight;
			union_set(rank,parent,a,b);//�ϲ�
		}
		if(count == adjvex_num-1)break;
	}
	printf("��С������\n");
	for(i=0;i<adjvex_num-1;i++)
	{
		weight+=edges[i].weight;
		printf("%c->%c  %d\n",adjvex[edges[i].arc[0]],adjvex[edges[i].arc[1]],edges[i].weight);
	}
	printf("��С������������Ȩֵ:%d\n",weight);
	//�ͷ�ָ��
	free(e);
	free(rank);
	free(parent);
	free(edges);
}
int main()
{
	dataType arc[][3]={{0,3,5},{0,1,7},{1,2,8},{1,3,9},{2,4,5},{1,4,7},{3,5,6},{3,4,15},{5,6,11},{4,6,9},{4,5,8}};
	UINT n = sizeof(arc)/sizeof(arc[0]);
	char ch[]={'a','b','c','d','e','f','g'};
	UINT adjvex_num = sizeof(ch)/sizeof(char);
	miniSpanTree_Kruskal(arc,ch,n,adjvex_num);
	return 0;
}