#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Heap.h"
#include"ArrayList.h"
typedef struct HuffmanCode
{
	char data;
	char* code;
}Code;
void order(Tree* root);
huffmanTree createHuffmanTree(struct HuffmanTree*** nodes,int* n,char** s,int* weight)
{
	char str[1000];
	int count[128]={0},i,size,val=0;
	struct Heap* heap=NULL,*h=NULL;
	struct HuffmanTree** node,*l=NULL,*r=NULL,*root=NULL;
	List* list=NULL;
	initArrayList(&list);
	initHeap(&heap);
	printf("输入任意序列:\n");
	scanf("%s",str);
	*s=str;
	for(i=0;i<(int)strlen(str);i++)
	{
		count[(int)str[i]]++;
	}
	for(i=0;i<128;i++)
	{
		if(count[i]>0)
		{
			add(&list,(char)i,count[i]);
		}
	}
	size=list->current_length;
	node=(struct HuffmanTree** )malloc((2*size-1)*sizeof(struct HuffmanTree*));
	for(i=0;i<size;i++)
	{
		node[i]=(struct HuffmanTree* )malloc(sizeof(struct HuffmanTree));
		node[i]->data=list->arr[i]->data;
		node[i]->weight=list->arr[i]->frequency;
		node[i]->left=NULL;
		node[i]->right=NULL;
		insertHeap(&heap,&node[i]);
	}
	printf("排序后的各字符出现频率如下:\n");
	//heapSort(heap);
	for(i=size;i<2*size-1;i++)
	{
		node[i]=(struct HuffmanTree* )malloc(sizeof(struct HuffmanTree));
		deleteHeap(&heap,&l);
		deleteHeap(&heap,&r);
		if(!l->left&&!l->right)
		{
			printf("%c %d\n",l->data,l->weight);
		}
		if(!r->left&&!r->right)
		{
			printf("%c %d\n",r->data,r->weight);
		}
		node[i]->weight=l->weight+r->weight;
		val+=node[i]->weight;
		node[i]->left=l;
		node[i]->right=r;
		l->parent=node[i];
		r->parent=node[i];
		insertHeap(&heap,&node[i]);
	}
	(*nodes)=node;
	deleteHeap(&heap,&root);
	printf("哈夫曼树前序遍历:\n");
	order(root);
	printf("\n");
	(*n)=size;
	(*weight)=val;
	free(list);
	free(heap);
	return root;
}
void order(Tree* root)
{
	if(!root)return;
	printf("%d ",root->weight);
	order(root->left);
	order(root->right);
}
void reverseStr(char** str)
{
	int i = 0,j=(int)strlen(*str)-1;
	char c;
	while(i<j)
	{
		c=(*str)[i];
		(*str)[i]=(*str)[j];
		(*str)[j]=c;
		i++;
		j--;
	}
}
void searchCode(struct HuffmanCode** code,int size,char data,char** s)
{
	int i;
	for(i=0;i<size;i++)
	{
		if(code[i]->data==data)
		{
			(*s)=code[i]->code;
			break;
		}
	}
}
void createHuffmanCode(Tree* root,Tree** nodes,struct HuffmanCode*** codes,int size)
{
	int i,index;
	struct HuffmanTree* node=NULL;
	struct HuffmanCode** code=(struct HuffmanCode** )malloc(size*sizeof(struct HuffmanCode*));
	for(i=0;i<size;i++)
	{
		node=nodes[i];
		code[i]=(struct HuffmanCode* )malloc(sizeof(struct HuffmanCode));
		if(!code[i])
		{
			printf("内存分配失败!\n");
			exit(-1);
		}
		code[i]->code=(char* )malloc(100*sizeof(char));
		memset(code[i]->code,0,sizeof(code[i]->code));
		code[i]->data=node->data;
		index=0;
		while(node!=root)
		{
			code[i]->code[index++]=node==node->parent->left?'0':'1';
			node=node->parent;
		}
		code[i]->code[index]='\0';
		reverseStr(&(code[i]->code));
		printf("%c  %s\n",code[i]->data,code[i]->code);
	}
	(*codes)=code;
}
int main()
{
	struct HuffmanTree** nodes=NULL;
	struct HuffmanCode** code=NULL;
	int size,weight;
	char* s,str[10000]="",*string;
	printf("哈夫曼编码-优先队列\n");
	huffmanTree root=createHuffmanTree(&nodes,&size,&s,&weight);
	printf("哈夫曼树的带权路径长度:%d\n",weight);
	printf("各字符的哈夫曼编码:\n");
	createHuffmanCode(root,nodes,&code,size);
	while(*s)
	{
		searchCode(code,size,*s,&string);
		strcat(str,string);
		s++;
	}
	printf("字符序列的哈夫曼编码:\n");
	printf("%s\n",str);
	free(nodes);
	free(root);
	free(code);
	return 0;
}