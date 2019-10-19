#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef int dataType;
typedef char elemType;
//队列的链式存储
//先进先出FIFO
struct Queue
{
	struct Queue* next;
	void* elem;
};
typedef struct Queue queue;
//定义队列的头尾指针
typedef struct LinkQueue
{
	queue* front;
	queue* rear;
}linkQueue;
void initQueue(linkQueue**);
void visitQueue(linkQueue* queue);
void queueTop(linkQueue* queue,void** elem);
void destoryQueue(linkQueue** queue);
void enQueue(linkQueue** queue,void* elem);
void deQueue(linkQueue** queue,void**);
dataType queueEmpty(linkQueue* queue);
dataType getQueueSize(linkQueue* queue);
//初始化队列
void initQueue(linkQueue** queue)
{
	*queue=(linkQueue*)malloc(sizeof(struct LinkQueue));
	if(!(*queue))
	{
		printf("内存分配失败\n");
		exit(-1);
	}
	(*queue)->front=(*queue)->rear=(struct Queue* )malloc(sizeof(struct Queue));
}
//计算队列长度
dataType getQueueSize(linkQueue* lQueue)
{
	queue* q=lQueue->front,*p=lQueue->rear;
	dataType length=0;
	while(q!=p)
	{
		q=q->next;		
		length++;
	}
	return length;
}
//判断队列是否为空
dataType queueEmpty(linkQueue* queue)
{
	return queue->front == queue->rear;
}
//取队顶元素
void queueTop(linkQueue* queue, void** elem)
{
	*elem = queue->front->next->elem;
}
//元素入队并删除队顶指针
void enQueue(linkQueue** lQueue,void* elem)
{
	queue* q=NULL;
	q=(queue* )malloc(sizeof(struct Queue));
	if(!q)
	{
		printf("内存分配失败\n");
		exit(-1);
	}
	q->elem = elem;
	(*lQueue)->rear->next=q;
	(*lQueue)->rear=q;
}
//元素出队并删除队顶指针
void deQueue(linkQueue** lQueue,void** elem)
{
	queue* q=(*lQueue)->front;
	if(q->next==(*lQueue)->rear)
	{
		*elem=(*lQueue)->rear->elem;
		(*lQueue)->rear=(*lQueue)->front;
		return;
	}
	*elem=(*lQueue)->front->next->elem;
	(*lQueue)->front->next=(*lQueue)->front->next->next;
}
//销毁队列指针
void destoryQueue(linkQueue** lQueue)
{
	queue* q,*p = (*lQueue)->rear;
	while((*lQueue)->front!=p)
	{
		q = (*lQueue)->front->next;
		free((*lQueue)->front);
		(*lQueue)->front = q;
	}
	free((*lQueue)->front);
}
int main()
{
	linkQueue* queue = NULL;
	int i,nums[]={2,4,1,5,6,7,1,2,9},size = sizeof(nums)/sizeof(int);
	void* elem;
	initQueue(&queue);
	for(i=0;i<size;i++)
	{
		enQueue(&queue,(void*)&nums[i]);
	}
	while(!queueEmpty(queue))
	{
		deQueue(&queue,&elem);
		printf("%d ",*(int*)elem);
	}
	printf("\n");
	destoryQueue(&queue);
	free(queue);
	return 0;
}
