#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 100//最大顶点数
#define MAX_VALUE (2<<30)-1//最大值
typedef void* elemType;
typedef int dataType;
typedef unsigned int UINT;
#ifdef MAX_LEN
//邻接矩阵
typedef struct Matrix
{
	dataType weight;
}matrix;
//最短路径Floyd算法
void shortestPath_Floyd(dataType arc[][3],UINT n,char* adjvex,UINT adjvex_num)
{
	UINT i,j,k;
	matrix m[MAX_LEN][MAX_LEN];//定义邻接矩阵
	dataType** data = (dataType**)malloc(sizeof(dataType*)*adjvex_num);//存储权值
	if(!data)exit(-1);
	for(i=0;i<adjvex_num;i++)
	{
		for(j=0;j<adjvex_num;j++)m[i][j].weight = MAX_VALUE;//初始化权值为最大值
	}
	for(i=0;i<n;i++)//建立邻接矩阵
	{
		m[arc[i][0]][arc[i][0]].weight = 0;
		m[arc[i][1]][arc[i][1]].weight = 0;
		m[arc[i][0]][arc[i][1]].weight = arc[i][2];
		m[arc[i][1]][arc[i][0]].weight = arc[i][2];
	}
	for(i=0;i<adjvex_num;i++)
	{
		data[i] = (dataType*)malloc(sizeof(dataType)*adjvex_num);
		if(!data[i])exit(-1);
		for(j=0;j<adjvex_num;j++)data[i][j] = m[i][j].weight;//初始化结果集
	}
	//o(n3)算法实现
	for(i=0;i<adjvex_num;i++)
	{
		for(j=0;j<adjvex_num;j++)
		{
			for(k = 0;k<adjvex_num;k++)//中转节点 只需比较data[i][j]与data[i][k]+data[k][j]的大小进行取值
			{
				if(data[i][k]!=MAX_VALUE&&data[k][j]!=MAX_VALUE)data[i][j] = data[i][j] < data[i][k]+data[k][j] ? data[i][j] : data[i][k]+data[k][j];
			}
		}
	}
	for(i=0;i<adjvex_num;i++)
	{
		for(j=0;j<adjvex_num;j++)
		{
			printf("%c->%c %d\n",adjvex[i],adjvex[j],data[i][j]);//输出路径和权值
		}
	}
	//释放指针
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
