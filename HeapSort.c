#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//������
void swap(int* a,int* b)
{
	int temp = *a;
	*a=*b;
	*b=temp;
}
void adjustHeap(int* arr,int n)
{
	int i,temp;
	for(i = n/2-1;i>=0;i--)
	{
		if(i == n/2 - 1 && 2*i < n - 3)temp = arr[2*i+1];
		else temp = arr[2*i+1] > arr[2*i+2] ? arr[2*i+1]:arr[2*i+2];
 		if(arr[i]<temp)swap(&arr[i],temp == arr[2*i+1]?&arr[2*i+1]:&arr[2*i+2]);
	}
	for(i = 1;i<=n/2-1;i++)
	{
		
		if(i == n/2 - 1 && 2*i < n - 3)temp = arr[2*i+1];
		else temp = arr[2*i+1] > arr[2*i+2] ? arr[2*i+1]:arr[2*i+2];
		if(arr[i]<temp)swap(&arr[i],temp == arr[2*i+1]?&arr[2*i+1]:&arr[2*i+2]);
	}
	
}
void heapSort(int* arr,int n)
{
	while(n -- > 1)
	{
		adjustHeap(arr,n);
		swap(&arr[0],&arr[n]);
	}
}
int main()
{
	int arr[]={5,4,11,8,9,6,12,8,0,10},* sortArr;
	int n = sizeof(arr)/sizeof(int),i=0;
	printf("ԭ����:\n");
	for(;i<n;i++)
	{
		printf("%d ",arr[i]);
	}
	printf("\n");
	heapSort(arr,n);
	printf("����������:\n");
	for(i=0;i<n;i++)
	{
		printf("%d ",arr[i]);
	}
	printf("\n");
	return 0;
}