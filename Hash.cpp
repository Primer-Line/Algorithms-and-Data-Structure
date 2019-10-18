#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define LEN 15
typedef char Element; 
typedef unsigned int UINT;
typedef struct Hash
{
	int key;
	int val;
	struct LinkedList* head;
}hash;
typedef struct LinkedList
{
	int key;
	int val;
	struct LinkedList* next;
}linkeList;
//hash函数 hash(x)=key%LEN
//开放定址法
void createHash(hash*** hashArr,int* key, int key_len,int* value)
{
	int i,index;
	*hashArr= (struct Hash**) malloc(sizeof(struct Hash*)*LEN);
	memset(*hashArr,0x00,sizeof(struct Hash*)*LEN);
	for(i=0;i<key_len;i++)
	{
		index=key[i]%LEN;	
		while((*hashArr)[index])index++;
		(*hashArr)[index]=(struct Hash*) malloc(sizeof(struct Hash));
		if(!(*hashArr)[index])exit(-1);
		(*hashArr)[index]->key=key[i];
		(*hashArr)[index]->val=value[i];
	}
}
//直接链地址法
void create_Hash(hash*** hashArr,int* key, int key_len,int* value)
{
	int i,index;
	*hashArr= (struct Hash**) malloc(sizeof(struct Hash*)*LEN);
	struct LinkedList* p=NULL;
	memset(*hashArr,0x00,sizeof(struct Hash*)*LEN);
	for(i=0;i<LEN;i++)
	{
		(*hashArr)[i] = (struct Hash*) malloc(sizeof(struct Hash));
		(*hashArr)[i]->head=NULL;
	}
	for(i=0;i<key_len;i++)
	{
		index=key[i]%LEN;	
		if(!((*hashArr)[index]->head))
		{
			(*hashArr)[index]->head=(struct LinkedList*)malloc(sizeof(struct LinkedList));
			(*hashArr)[index]->head->key=key[i];
			(*hashArr)[index]->head->val=value[i];
			(*hashArr)[index]->head->next=NULL;
		}
		else
		{
			p=(struct LinkedList*)malloc(sizeof(struct LinkedList));
			p->key=key[i];
			p->val=value[i];
			p->next=(*hashArr)[index]->head;
			(*hashArr)[index]->head=p;	
		}		
	}
}
//查找key对应的val 成功返回1 失败返回0
UINT searchValue(int key,Hash** hashArr,int* val)
{
	int index=key%LEN;
	struct LinkedList* p = hashArr[index]->head;
	if(!p)return -1;
	while(p!=NULL&&p->key!=key)p=p->next;
	if(p)
	{
		*val = p->val;
		return 1;
	}
	return 0;
}
UINT findValue(int key,Hash** hashArr,int* val)
{
	int index=key%LEN;
	while(hashArr[index]&&hashArr[index]->key!=key)index++;
	if(hashArr[index])
	{
		*val = hashArr[index]->val;
		return 1;
	}
	return 0;
}
int main()
{
	int key[] = {4,7,1,3,5,12,23,9,11,15,6,8};
	int value[] = {2,6,10,13,24,13,45,24,67,18,26,43},val;
	int key_len = sizeof(key)/sizeof(int),i=0;
	struct Hash** hashArr = NULL;
	create_Hash(&hashArr,key, key_len,value);
	UINT status = searchValue(4,hashArr,&val);
	if(status)printf("查找key:4对应的value:%d\n",val);
	else printf("不存在该key对应的value\n");
	return 0;
}
