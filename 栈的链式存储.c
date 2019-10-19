#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef void* elemType;//void*指针方便于存储任何类型的指针
typedef int Element;
/*
栈的链式存储结构
 */
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
//判断栈是否为空
int stackEmpty(stack* sHead)
{
	return !sHead;
}
//计算栈的的长度
int getStackSize(stack* sHead)
{
	return !sHead?0:getStackSize(sHead->next)+1;
}
//将元素压入栈底
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
//元素出栈并删除栈顶指针
void pop(stack** sHead,elemType* elem)
{
	*elem=(*sHead)->elem;
	(*sHead)=(*sHead)->next;
}
//取栈顶元素
void stackTop(stack* sHead,elemType* elem)
{
	*elem = sHead->elem;
}
//销毁栈指针
void destoryStack(stack** sHead)
{
	stack* p;
	while(*sHead)
	{
		p = (*sHead)->next;
		free(*sHead);
		*sHead = p;
	}
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
		printf("%d ",*(int*)elem);
	}
	printf("\n");
	destoryStack(&s);
	return 0;
}