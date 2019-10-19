#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef void* elemType;//void*ָ�뷽���ڴ洢�κ����͵�ָ��
typedef int Element;
/*
ջ����ʽ�洢�ṹ
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
//�ж�ջ�Ƿ�Ϊ��
int stackEmpty(stack* sHead)
{
	return !sHead;
}
//����ջ�ĵĳ���
int getStackSize(stack* sHead)
{
	return !sHead?0:getStackSize(sHead->next)+1;
}
//��Ԫ��ѹ��ջ��
void push(stack** sHead,const elemType elem)
{	
	stack* p,*q=(*sHead);
	if(!(*sHead))
	{
		(*sHead)=(stack* )malloc(sizeof(struct Stack));
		if(!(*sHead))
		{
			printf("�ڴ����ʧ��\n");
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
		printf("�ڴ����ʧ��\n");
		exit(-1);
	}
	memset(p,0,sizeof(p));
	p->elem=elem;
	p->next=(*sHead);
	(*sHead)=p;   
}
//Ԫ�س�ջ��ɾ��ջ��ָ��
void pop(stack** sHead,elemType* elem)
{
	*elem=(*sHead)->elem;
	(*sHead)=(*sHead)->next;
}
//ȡջ��Ԫ��
void stackTop(stack* sHead,elemType* elem)
{
	*elem = sHead->elem;
}
//����ջָ��
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