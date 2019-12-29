#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define LEN 16
typedef char Element; 
typedef unsigned int UINT;
//散列
typedef struct Hash
{
	int key;
	int val;
	struct LinkedList* head;
}hash;
//链表
typedef struct LinkedList
{
	int key;
	int val;
	struct LinkedList* next;
}linkeList;
//hash函数
UINT hashCode(UINT hash)
{
	return (((hash<<16) ^ 0x6f6f3d) & 0xff2) & (LEN - 1);
}
//开放定址法
void createHash(hash*** hashArr,int* key, UINT key_len,int* value)
{
	UINT i,index,k;
	*hashArr= (struct Hash**) malloc(sizeof(struct Hash*)*LEN);
	memset(*hashArr,0x00,sizeof(struct Hash*)*LEN);
	for(i=0;i<key_len;i++)
	{
		index=hashCode(key[i]),k=index+1;
		while(k<LEN&&(*hashArr)[k])k++;
		if(k<LEN)
		{
			(*hashArr)[k]=(struct Hash*)malloc(sizeof(struct Hash));
			if(!(*hashArr)[k])exit(-1);
			(*hashArr)[k]->key=key[i];
			(*hashArr)[k]->val=value[i];
		}
	}
}
//直接链地址法
void create_Hash(hash*** hashArr,int* key, UINT key_len,int* value)
{
	UINT i,index;
	struct LinkedList* p=NULL,*h=NULL;
	*hashArr= (struct Hash**) malloc(sizeof(struct Hash*)*LEN);
	memset(*hashArr,0x00,sizeof(struct Hash*)*LEN);
	for(i=0;i<LEN;i++)
	{
		(*hashArr)[i] = (struct Hash*) malloc(sizeof(struct Hash));
		if(!(*hashArr)[i])exit(-1);
		(*hashArr)[i]->head=NULL;
	}
	for(i=0;i<key_len;i++)
	{
		index=hashCode(key[i]);	
		if(!((*hashArr)[index]->head))
		{
			(*hashArr)[index]->head=(struct LinkedList*)malloc(sizeof(struct LinkedList));
			(*hashArr)[index]->head->key=key[i];
			(*hashArr)[index]->head->val=value[i];
			(*hashArr)[index]->head->next=NULL;
		}
		else
		{
			h = ((*hashArr)[index])->head;
			while(h&&h->key!=key[i])h=h->next;
			if(h)h->val = value[i];
			else
			{	
				p=(struct LinkedList*)malloc(sizeof(struct LinkedList));
				if(!p)exit(-1);
				p->key=key[i];
				p->val=value[i];
				p->next=(*hashArr)[index]->head;
				(*hashArr)[index]->head=p;	
			}
		}		
	}
}
//查找key对应的val 成功返回1 失败返回0
UINT searchValue(int key,hash** hashArr,int* val)
{
	UINT index=hashCode(key);
	struct LinkedList* p = hashArr[index]->head;
	if(!p)return 0;
	while(p!=NULL&&p->key!=key)p=p->next;
	if(p)
	{
		*val = p->val;
		return 1;
	}
	return 0;
}
//查找key对应的val 成功返回1 失败返回0
UINT findValue(int key,hash** hashArr,int* val)
{
	UINT index=hashCode(key),k=index+1;
	while(k<LEN&&hashArr[k]&&hashArr[k]->key!=key)k++;
	if(k<LEN&&hashArr[k]&&hashArr[k]->key==key)
	{
		*val = hashArr[k]->val;
		return 1;
	}
	return 0;
}
//销毁链表
void destoryLinkedList(linkeList** list)
{
	linkeList* p;
	while(*list)
	{
		p = (*list)->next;
		free(*list);
		*list = p;
	}
}
//销毁哈希表
void destoryHash(struct Hash*** hashArr)
{
	UINT i;
	for(i=0;i<LEN;i++)
	{
		destoryLinkedList(&((*hashArr)[i]->head));
		free((*hashArr)[i]);
		(*hashArr)[i]=NULL;
	}
	free(*hashArr);
	*hashArr=NULL;
}
int main()
{
	int key[] = {4,7,1,3,5,12,23,9,11,15,6,8};
	int value[] = {2,6,10,13,24,13,45,24,67,18,26,43},val;
	UINT key_len = sizeof(key)/sizeof(int),status;
	struct Hash** hashArr = NULL;
	create_Hash(&hashArr,key, key_len,value);
	status = searchValue(23,hashArr,&val);
	if(status)printf("查找key:23对应的value:%d\n",val);
	else printf("不存在该key对应的value\n");
	destoryHash(&hashArr);
	return 0;
}
