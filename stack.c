#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef void* elemType;
typedef int Element;
typedef struct Stack
{
	struct Stack* next;
	elemType elem;
}stack;
void pop(stack** sHead,elemType*);
void push(stack** sHead,const elemType);
void stackTop(stack* sHead,elemType*);
void visitStackElement(stack* sHead);
int stackEmpty(stack* sHead);
int getStackSize(stack* sHead);
void destoryStack(stack** sHead);
void clearStack(stack** sHead);
int stackEmpty(stack* sHead)
{
	return sHead == NULL;
}
void clearStack(stack** sHead)
{
	memset(*sHead,0,sizeof(*sHead));
}
int getStackSize(stack* sHead)
{
	return !sHead?0:getStackSize(sHead->next)+1;
}
void push(stack** sHead,const elemType elem)
{	
	stack* p,*q=(*sHead);
	if(!(*sHead))
	{
		(*sHead)=(stack* )malloc(sizeof(struct Stack));
		if(!(*sHead))
		{
			printf("内存分配失败\n");
			exit(-1);
		}
		memset((*sHead),0,sizeof((*sHead)));
		(*sHead)->elem = elem;
		(*sHead)->next=NULL;
		return;
	}
	p=(stack* )malloc(sizeof(struct Stack));
	if(!p)
	{
		printf("内存分配失败\n");
		exit(-1);
	}
	memset(p,0,sizeof(p));
	p->elem=elem;
	p->next=(*sHead);
	(*sHead)=p;   
}
void pop(stack** sHead,elemType* elem)
{
	*elem=(*sHead)->elem;
	(*sHead)=(*sHead)->next;
}
void stackTop(stack* sHead,elemType* elem)
{
	*elem = sHead->elem;
}
void destoryStack(stack** sHead)
{
	free((*sHead));
	(*sHead)=NULL;
}
int main()
{
	stack* s=NULL;
	void* elem;
	int i=1,j=2,k=3;
	push(&s,&i);
	push(&s,&j);
	push(&s,&k);
	while(!stackEmpty(s))
	{
		pop(&s,&elem);
		printf("%d\n",*(int*)elem);
	}
	free(s);
	return 0;
}
