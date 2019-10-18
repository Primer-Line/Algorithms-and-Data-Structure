#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//void* �洢����ʱ����������ֵ����һ���̶����� �����ڴ�ᷢ��Ӱ�� ֻ�в�ͬ�����ݵ�ַ���ܷ�ֹ�����������
typedef void* Element;
typedef unsigned int UINT;
typedef int elemType;
//�ṹ���ڲ������ı������Ч
typedef struct LinkedList
{
	void* data;
	struct LinkedList* next;
}List;
void addNode(List**,Element);
void visitLinkedList(List* head);
void insertElement(List** head,UINT index,Element data);
void deleteElement(List** head,UINT index);
UINT getLinkedListLength(List* head);
void reverseLinkedList(List** head);
void getElement(List* head,UINT index,Element*);
UINT findElement(List* head,Element data);
void searchNode(List* head,UINT i,Element*);
void sortLinkedList(List** head);
void swapNode(List** head,UINT i,UINT j);
void subList(List** head,UINT i,UINT j);
void swap_node(List** head,UINT i,UINT j);
int hasLoop(List* head);
//����ָ�� �ȽϽڵ��С
int (*cmp(const void* a,const void* b))
{
	int* m = (int*)a,*n = (int*)b;
	if(*m<*n)return -1;
	if(*m==*n)return 0;
	return 1;
}
//��ӽڵ�
void addNode(List** head,void* data)
{
	List* p = (*head),*q;
	if(!(*head))
	{
		*head=(List* )malloc(sizeof(struct LinkedList));
		if(!(*head))exit(-1);
		memset(*head,0,sizeof(*head));
		(*head)->data=data;
		(*head)->next=NULL;
		return;
	}
	q=(List* )malloc(sizeof(struct LinkedList));
	if(!q)exit(-1);
	q->data=data;
	while(p->next)p=p->next;
	q->next = p->next;
	p->next = q;
}
//ð������
void sortLinkedList(List** head)
{
	List* p=(*head),*temp;
	UINT i,j;
	if((*head)==NULL||(*head)->next==NULL)return;
	if((*head)->next->next==NULL)
	{
		temp=(*head)->next;
		(*head)->next=NULL;
		temp->next=(*head);
		(*head) =  temp;
		return;
	}
	for(i=0;i<getLinkedListLength(p)-1;i++)
	{
		for(j=0;j<getLinkedListLength(p)-1;j++)swap_node(&p,j,j+1);
	}
}
//��ȡ������
void subList(List** head,UINT i,UINT j)
{
	List* p=(*head),*q;
	UINT temp;
	if(i==j)return;
	if(i>j)
	{
		temp=i;
		i=j;
		j=temp;
	}
	while(p)
	{
		if(!i--)q=p;
		if(j--==1)
		{
			free(p->next);
			p->next=NULL;
			break;
		}
		p=p->next;	
	}
}
//�������ڽڵ�
void swap_node(List** head,UINT i,UINT j)
{
	List*p=(*head),*start,*end,*t,*q;
	if(!i&&cmp((*head)->data,(*head)->next->data) == 1)
	{
		q=p->next;
		(*head)->next=q->next;
		q->next=(*head);
		q = (*head);
		return;
	}
	while(p)
	{
		if(i==1)q=p;
		if(!i--)start=p;
		if(!j--)
		{
			end=p;
			break;
		}
		p=p->next;
	}
	if(cmp(start->data,end->data) == 1)
	{
		t=end;
		start->next=end->next;
		t->next=start;
		q->next=t;
	}
}
//������������̵�����
//�����ڵ�
void swapNode(List** head,UINT i,UINT j)
{
	List*p=(*head),*start,*end,*t,*q,*h,*k;
	UINT temp;
	if(i==0||j==0||i==j)return;
	if(j<i)
	{
		temp=j;
		j=i;
		i=temp;
	}
	while(p)
	{
		if(i==1)q=p;
		if(!i--)start=p;
		if(j==1)k=p;
		if(!j--)
		{
			end=p;
			break;
		}
		p=p->next;
	}
	if(!cmp(start->data,end->data))return;
	if(start->next==end)
	{
		t=end;
		start->next=end->next;
		t->next=start;
		q->next=t;
		return;
	}
	t=start;
	start=start->next;//1->2->3->5->6->7->4->9
	t->next=end->next;
	end->next=t;
	h=end;
	end=end->next;
	k->next=end;
	h->next=start;
	q->next=h;
}
//��ȡ������
UINT getLinkedListLength(List* head)
{
	//(*head).next
	return !head?0:getLinkedListLength(head->next)+1;
}
//��������
void visitLinkedList(List* head)
{
	List* p=head;
	//(*head) (*p)ȡ���� head pָ���ƶ�
	void* elem;
	int data;
	printf("��������:\n");
	while(p!=NULL)
	{
		elem = p->data;
		data = *(int*)elem;
		printf("%d ",data);
		p=p->next;
	}
	printf("\n");
}
//�������ڴ��ַ �������޹� ֻ�����ָ�벻�ܷ����ı� ֻ�����ݷ����ı����Ч
//��ת����
void reverseLinkedList(List** head)
{
	List* node=NULL,*h;
	while(*head)
	{	
		h=(*head)->next;
		(*head)->next=node;
		node=(*head);
		(*head)=h;
	}
	(*head) = node;
}
//��ָ����������������
void insertElement(List** head,UINT index,Element data)
{
	List* p=(*head),*q=NULL;
	UINT length=0,len;
	q=(List* )malloc(sizeof(struct LinkedList));
	if(!q)
	{
		printf("�ڴ����ʧ��\n");
		exit(-1);
	}
	memset(q,0,sizeof(q));
	q->data=data;
	if(!index)
	{
		q->next=p;
		(*head) = q;
		return;
	}
	len=getLinkedListLength(*head)-1==index?index:index-1;
	while(p!=NULL&&length++!=index-1)p=p->next;
	q->next=p->next;
	p->next=q;//�ṹ���ڲ������ı� p  =  q �ṹ�帳ֵ ��Ӱ�� ����!!!! ���ǹ���
}
//ɾ��ָ��������������
void deleteElement(List** head,UINT index)
{
	List* p=(*head);//����ָ�� �����ڲ�ֵ�ĸı����ʹԭָ��仯 ����ָ���븨��ָ�������
	UINT length=0;
	if(!index)
	{
		(*head) = (*head)->next;
		return;
	}
	while(p!=NULL&&length++!=index-1)p=p->next;
	p->next=p->next->next;
}
//��ȡָ����������������
void getElement(List* head,UINT index,Element* data)
{
	List* p=head;
	while(p!=NULL&&index--)p=p->next;//�����ϲ���ʹԭ�������ı� p->next->data = 1  == (*p).next->data = 1
	*data = p->data;
}
//����ָ�������Ƿ������������
UINT findElement(List* head,Element data)
{
	List* p=head;
	UINT index=0;
	while(p!=NULL&&cmp(p->data,data))
	{
		index++;
		p=p->next;
	}
	return p ? index : -1;
}
//�ж������Ƿ��л�
int hasLoop(List* head)
{
	List* p=head,*q=head;
	if(head==NULL)return 0;
	if(head->next==NULL)return 1;
	while(p!=NULL&&q->next!=NULL)
	{
		p=p->next;
		if(q->next->next!=NULL)q=q->next->next->next;
		if(p==q)return 1;	
	}
	return 0;
}
//����ָ���������Ľڵ�ֵ
void searchNode(List* head,UINT i,Element* elem)
{
	List* p=head;
	while(p!=NULL&&!i--)p=p->next;
	*elem = p ?  p->data : NULL;
}
int main(int* arg, char* arv)
{
	List* head=NULL;
	void* elem;
	UINT index, data;
	int nums[] = {1,2,3,4,5,6,7,8,9,10},len = sizeof(nums)/sizeof(int),i;
	for(i=0;i<len;i++)addNode(&head,(void*)&nums[i]);
	if(head!=NULL)
	{
		visitLinkedList(head);
		printf("��������\n");
		sortLinkedList(&head);
		visitLinkedList(head);
		printf("����ü�\n");
		subList(&head,1,7);
		visitLinkedList(head);
		printf("�����ڵ�\n");
		swapNode(&head,4,5);
		visitLinkedList(head);
		printf("��ת����\n");
		reverseLinkedList(&head);
		visitLinkedList(head);
		printf("����Ԫ��\n");
		getElement(head,3,&elem);
		printf("%d\n",*(int*)elem);
		printf("����Ԫ��:\n");
		printf("����������������(0<=����<=%d):\n",getLinkedListLength(head));
		scanf("%d %d",&index,&data);
		insertElement(&head,index,&data);
		visitLinkedList(head);
		printf("ɾ��Ԫ��:\n");
		printf("����������(0<=����<=%d):\n",getLinkedListLength(head)-1);
		scanf("%d",&index);
		deleteElement(&head,index);
		visitLinkedList(head);
		printf("%s\n",hasLoop(head)?"������ڻ�":"�������ڻ�");
	} else printf("��������Ϊ0�Ŀ�����\n");
	return 0;
}