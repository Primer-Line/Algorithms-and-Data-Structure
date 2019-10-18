#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct DoubleLinkeList
{
	int data;
	struct DoubleLinkeList* prior;
	struct DoubleLinkeList* next;	
}doubleLinkeList;
void insertNode(doubleLinkeList** head,struct DoubleLinkeList* s,int index)
{
	doubleLinkeList* p=(*head),*q;
	if(!index)
	{
		q=(*head)->prior;
		s->next=(*head);
		(*head)->prior=s;
		q->next=s;
		s->prior=q;
		(*head)=s;
		return;
	}
	while(--index>=0)p=p->next;
	s->next=p;
	s->prior=p->prior;
	p->prior->next=s;
	p->prior=s;
}
void deleteNode(doubleLinkeList** head,int index)
{
	doubleLinkeList* p=(*head);
	if(!index)
	{
		(*head)->prior->next=(*head)->next;
		(*head)->next->prior=(*head)->prior;
		(*head)=(*head)->next;
		return;
	}
	while(--index>=0)p=p->next;
	p->next->prior=p->prior;
	p->prior->next=p->next;
}
void swapNode(doubleLinkeList** head,int a,int b)
{
	if(a==b-1)
	{
		doubleLinkeList* p=(*head),*q;
		while(--a>=0&&p->next!=(*head))p=p->next;
		q=p;
		p->next->prior=p->prior;
		p->prior->next=p->next;
		p->prior->next->next->prior=q;
		q->next=p->prior->next->next;
		q->prior=p->prior->next;
		p->prior->next=q;
		return;
	}
}
void addNode(doubleLinkeList** head,int data)
{
	struct DoubleLinkeList* p,*q;
	if(!(*head))
	{
		(*head)=(struct DoubleLinkeList* )malloc(sizeof(struct DoubleLinkeList));
		(*head)->data=data;
		(*head)->next=(*head);
		(*head)->prior=(*head);
		return;
	}
	p=(*head);
	q=(struct DoubleLinkeList* )malloc(sizeof(struct DoubleLinkeList));
	q->data=data;
	while(p->next!=(*head))p=p->next;
	q->next=p->next;
	p->next->prior=q;
	p->next=q;
	q->prior=p;
}
void visit(struct DoubleLinkeList* head)
{
	doubleLinkeList* p=head,*q=head->prior;
	printf("正序输出:\n");
	while(p->next!=head)
	{
		printf("%d ",p->data);
		p=p->next;
	}
	printf("%d\n",p->data);
	printf("逆序输出:\n");
	while(q!=head)
	{
		printf("%d ",q->data);
		q=q->prior;
	}
	printf("%d\n",q->data);
}
int main()
{
	int i;
	struct DoubleLinkeList* head=NULL;
	struct DoubleLinkeList* s=(struct DoubleLinkeList* )malloc(sizeof(struct DoubleLinkeList));
	for(i=0;i<10;i++)addNode(&head,i);
	visit(head);
	printf("插入节点:\n");
	s->data=100;
	insertNode(&head,s,1);
	visit(head);
	printf("删除节点:\n");
	deleteNode(&head,3);
	visit(head);
	printf("交换相邻节点:\n");
	swapNode(&head,3,4);
	visit(head);
	return 0;
}