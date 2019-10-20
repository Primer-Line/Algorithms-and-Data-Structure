#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//void* 存储数据时不能用输入值或是一个固定变量 共享内存会发生影响 只有不同的数据地址才能防止这种情况发生
typedef void* Element;
typedef unsigned int UINT;
typedef int elemType;
//结构体内部发生改变才能有效
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
//函数指针 比较节点大小
int cmp(const void* a,const void* b)
{
	int* m = (int*)a,*n = (int*)b;
	if(*m<*n)return -1;
	if(*m==*n)return 0;
	return 1;
}
//添加节点
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
//冒泡排序
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
//截取子链表
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
//交换相邻节点
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
//函数调用与过程的区别
//交换节点
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
//获取链表长度
UINT getLinkedListLength(List* head)
{
	//(*head).next
	return !head?0:getLinkedListLength(head->next)+1;
}
//遍历链表
void visitLinkedList(List* head)
{
	List* p=head;
	//(*head) (*p)取内容 head p指针移动
	void* elem;
	int data;
	printf("遍历链表:\n");
	while(p!=NULL)
	{
		elem = p->data;
		data = *(int*)elem;
		printf("%d ",data);
		p=p->next;
	}
	printf("\n");
}
//不访问内存地址 与链表无关 只针对于指针不能发生改变 只有内容发生改变才有效
//反转链表
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
//向指定索引处插入数据
void insertElement(List** head,UINT index,Element data)
{
	List* p=(*head),*q=NULL;
	UINT length=0,len;
	q=(List* )malloc(sizeof(struct LinkedList));
	if(!q)
	{
		printf("内存分配失败\n");
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
	p->next=q;//结构体内部发生改变 p  =  q 结构体赋值 不影响 函数!!!! 不是过程
}
//删除指定索引处的数据
void deleteElement(List** head,UINT index)
{
	List* p=(*head);//辅助指针 发生内部值的改变才能使原指针变化 本质指针与辅助指针的区别
	UINT length=0;
	if(!index)
	{
		(*head) = (*head)->next;
		return;
	}
	while(p!=NULL&&length++!=index-1)p=p->next;
	p->next=p->next->next;
}
//获取指定数据所在索引处
void getElement(List* head,UINT index,Element* data)
{
	List* p=head;
	while(p!=NULL&&index--)p=p->next;//本质上不能使原链表发生改变 p->next->data = 1  == (*p).next->data = 1
	*data = p->data;
}
//查找指定数据是否存在于链表中
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
//判断链表是否有环
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
//查找指定索引处的节点值
void searchNode(List* head,UINT i,Element* elem)
{
	List* p=head;
	while(p!=NULL&&!i--)p=p->next;
	*elem = p ?  p->data : NULL;
}
//销毁链表
void destoryLinkedList(List** head)
{
	List* p;
	while(*head)
	{
		p = (*head)->next;
		free(*head);
		*head=p;
	}
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
		printf("链表排序\n");
		sortLinkedList(&head);
		visitLinkedList(head);
		printf("链表裁剪\n");
		subList(&head,1,7);
		visitLinkedList(head);
		printf("交换节点\n");
		swapNode(&head,4,5);
		visitLinkedList(head);
		printf("反转链表\n");
		reverseLinkedList(&head);
		visitLinkedList(head);
		printf("查找元素\n");
		getElement(head,3,&elem);
		printf("%d\n",*(int*)elem);
		printf("插入元素:\n");
		printf("请输入索引和数据(0<=索引<=%d):\n",getLinkedListLength(head));
		scanf("%d %d",&index,&data);
		insertElement(&head,index,&data);
		visitLinkedList(head);
		printf("删除元素:\n");
		printf("请输入索引(0<=索引<=%d):\n",getLinkedListLength(head)-1);
		scanf("%d",&index);
		deleteElement(&head,index);
		visitLinkedList(head);
		printf("%s\n",hasLoop(head)?"链表存在环":"链表不存在环");
		destoryLinkedList(&head);
	} else printf("创建长度为0的空链表\n");
	return 0;
}
