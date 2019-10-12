#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define LEN 15
typedef char Element; 
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
Hash** createHash(int* key, int key_len,int* value)
{
	int i,index;
	struct Hash** hashArr= (struct Hash**) malloc(sizeof(struct Hash*)*LEN);
	for(i=0;i<LEN;i++)
	{
		hashArr[i]=NULL;
	}
	
	for(i=0;i<key_len;i++)
	{
		index=key[i]%LEN;	
		while(hashArr[index])
		{
			index++;
		}
		hashArr[index]=(struct Hash*) malloc(sizeof(struct Hash));
		if(!hashArr[index])exit(-1);
		hashArr[index]->key=key[i];
		hashArr[index]->val=value[i];
	}
	return hashArr;
}
//直接链地址法
Hash** create_Hash(int* key, int key_len,int* value)
{
	int i,index;
	struct Hash** hashArr= (struct Hash**) malloc(sizeof(struct Hash*)*LEN);
	struct LinkedList* p=NULL;
	for(i=0;i<LEN;i++)
	{
		hashArr[i]=(struct Hash*) malloc(sizeof(struct Hash));
		hashArr[i]->head=NULL;
	}
	for(i=0;i<key_len;i++)
	{
		index=key[i]%LEN;	
		if(!hashArr[index]->head)
		{
			hashArr[index]->head=(struct LinkedList*)malloc(sizeof(struct LinkedList));
			hashArr[index]->head->key=key[i];
			hashArr[index]->head->val=value[i];
			hashArr[index]->head->next=NULL;
		}
		else
		{
			p=(struct LinkedList*)malloc(sizeof(struct LinkedList));
			p->key=key[i];
			p->val=value[i];
			p->next=hashArr[index]->head;
			hashArr[index]->head=p;	
		}		
	}
	return hashArr;
}
int searchValue(int key,Hash** hashArr)
{
	int index=key%LEN;
	struct LinkedList* p = hashArr[index]->head;
	if(!p)return -1;
	while(p!=NULL&&p->key!=key)
	{
		p=p->next;
	}
	return p==NULL?-1:p->val;
}
int findValue(int key,Hash** hashArr)
{
	int index=key%LEN;
	while(hashArr[index]&&hashArr[index]->key!=key)
	{
		index++;
	}
	return hashArr[index]?hashArr[index]->val:-1;
}
int main()
{
	int key[] = {4,7,1,3,5,12,23,9,11,15,6,8};
	int value[] = {2,6,10,13,24,13,45,24,67,18,26,43};
	int key_len = sizeof(key)/sizeof(int),i=0;
	struct Hash** hashArr = create_Hash(key, key_len,value);
	/*
	for(;i<LEN;i++)
	{
		if(hashArr[i])
		{
			printf("key:%d,value:%d\n",hashArr[i]->key,hashArr[i]->val);
		}
	}
	printf("查找key:12对应的value:%d\n",findValue(12,hashArr));
	*/
	printf("查找key:4对应的value:%d\n",searchValue(4,hashArr));
	return 0;
}
