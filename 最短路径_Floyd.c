#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 100//��󶥵���
#define MAX_VALUE (2<<30)-1//���ֵ
typedef void* elemType;
typedef int dataType;
typedef unsigned int UINT;
#ifdef MAX_LEN
//�ڽӾ���
typedef struct Matrix
{
	dataType weight;
}matrix;
//���·��Floyd�㷨
void shortestPath_Floyd(dataType arc[][3],UINT n,char* adjvex,UINT adjvex_num)
{
	UINT i,j,k;
	matrix m[MAX_LEN][MAX_LEN];//�����ڽӾ���
	for(i=0;i<adjvex_num;i++)
	{
		for(j=0;j<adjvex_num;j++)m[i][j].weight = MAX_VALUE;//��ʼ��ȨֵΪ���ֵ
	}
	dataType** data = (dataType**)malloc(sizeof(dataType*)*adjvex_num);
	for(i=0;i<n;i++)//�����ڽӾ���
	{
		m[arc[i][0]][arc[i][0]].weight = 0;
		m[arc[i][1]][arc[i][1]].weight = 0;
		m[arc[i][0]][arc[i][1]].weight = arc[i][2];
		m[arc[i][1]][arc[i][0]].weight = arc[i][2];
	}
	for(i=0;i<adjvex_num;i++)
	{
		data[i] = (dataType*)malloc(sizeof(dataType)*adjvex_num);
		for(j=0;j<adjvex_num;j++)data[i][j] = m[i][j].weight;//��ʼ�������
	}
	//o(n3)�㷨ʵ��
	for(i=0;i<adjvex_num;i++)
	{
		for(j=0;j<adjvex_num;j++)
		{
			for(k = 0;k<adjvex_num;k++)//��ת�ڵ� ֻ��Ƚ�data[i][j]��data[i][k]+data[k][j]�Ĵ�С����ȡֵ
			{
				if(data[i][k]!=MAX_VALUE&&data[k][j]!=MAX_VALUE)data[i][j] = data[i][j] < data[i][k]+data[k][j] ? data[i][j] : data[i][k]+data[k][j];
			}
		}
	}
	for(i=0;i<adjvex_num;i++)
	{
		for(j=0;j<adjvex_num;j++)
		{
			printf("%c->%c %d\n",adjvex[i],adjvex[j],data[i][j]);//���·����Ȩֵ
		}
	}
	//�ͷ�ָ��
	for(i=0;i<adjvex_num;i++)
	{
		free(data[i]);
		data[i]=NULL;
	}
	free(data);
	data=NULL;
	
}
int main()
{
	dataType arc[][3]={{0,3,5},{0,1,7},{1,2,8},{1,3,9},{2,4,5},{1,4,7},{3,5,6},{3,4,15},{5,6,11},{4,6,9},{4,5,8}};
	UINT n = sizeof(arc)/sizeof(arc[0]);
	char ch[]={'a','b','c','d','e','f','g'};
	UINT adjvex_num = sizeof(ch)/sizeof(char);
	shortestPath_Floyd(arc,n,ch,adjvex_num);
	return 0;
}
#endif