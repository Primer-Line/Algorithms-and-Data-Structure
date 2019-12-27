#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LENGTH 5//��ʼ��������󳤶�
/*
���ȼ����е�ʵ��
 */
//����ѵĴ洢�ṹ
typedef struct Heap
{
	int* arr;
	int current_length;
	int max_length;
}heap;
void adjustHeap(int* num,int size);
//��ʼ�����ȶ���
void initHeap(struct Heap** heap)
{
	(*heap) = (struct Heap* )malloc(sizeof(struct Heap));
	(*heap)->arr=(int* )malloc(sizeof(int)*MAX_LENGTH);
	(*heap)->current_length=0;
	(*heap)->max_length=MAX_LENGTH;
}
//����в���Ԫ��
void insertHeap(struct Heap** heap,int num)
{
	if((*heap)->current_length==(*heap)->max_length)
	{
		(*heap)->max_length+=(*heap)->max_length;
		(*heap)->arr = (int*)realloc((*heap)->arr,((*heap)->max_length)*sizeof(int));//���·����ڴ�
	}
	(*heap)->arr[(*heap)->current_length++]=num;
	adjustHeap((*heap)->arr,(*heap)->current_length);

}
//�����ѽڵ�
void swap(int* a,int* b)
{
	int temp=*a;
	*a=*b;
	*b=temp;
}
//ɾ����Ԫ��
void deleteHeap(struct Heap** heap)
{
	swap(&((*heap)->arr[0]),&((*heap)->arr[(*heap)->current_length-1]));
	adjustHeap((*heap)->arr,--(*heap)->current_length);
}
//��������ʹ֮����ѵ�����
void adjustHeap(int* num,int size)
{
	int i;
	int temp;
	if(size==1)return;
	//�������ϵ���
	for(i = size/2-1;i>=0;i--)
	{

		temp=i == size/2-1&&(2*i)!=size-3?num[2*i+1]:(num[2*i+1]<num[2*i+2]?num[2*i+1]:num[2*i+2]);
		if(temp<num[i])swap(temp==num[2*i+1]?(&num[2*i+1]):(&num[2*i+2]),&num[i]);
	}
	//�������µ���
	for(i = 0;i<=size/2-1;i++)
	{
		temp=i == size/2-1&&(2*i)!=size-3?num[2*i+1]:(num[2*i+1]<num[2*i+2]?num[2*i+1]:num[2*i+2]);
		if(temp<num[i])swap(temp==num[2*i+1]?(&num[2*i+1]):(&num[2*i+2]),&num[i]);
	}
}
//������
void heapSort(struct Heap* heap)
{
	int n = heap->current_length,i;
	while(--n>0)
	{
		swap(&(heap->arr[0]),&(heap->arr[n]));
		adjustHeap(heap->arr,n);
	}
	for(i=0;i<heap->current_length;i++)printf("%d ",heap->arr[i]);
	printf("\n");

}
int main()
{
	struct Heap* heap=NULL;
	int i,arr[]={6,9,0,2,4,1,7,8,5,3},size=sizeof(arr)/sizeof(int);
	initHeap(&heap);
	printf("���ȶ���\n");
	for(i=0;i<size;i++)insertHeap(&heap,arr[i]);
	while(heap->current_length>0)
	{
		for(i=0;i<heap->current_length;i++)printf("%d ",heap->arr[i]);
		printf("\n");
		deleteHeap(&heap);
	}
	free(heap->arr);
	free(heap);
	return 0;
}