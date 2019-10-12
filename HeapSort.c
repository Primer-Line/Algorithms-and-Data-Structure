#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void swap(int* arr,int a,int b)
{
int temp;
temp=arr[b];
arr[b]=arr[a];
arr[a]=temp;
}
void createHeap(int* arr,int n)
{
	int i;
	for(i = n/2-1;i>=0;i--)
	{
		if(arr[2*i+1]>arr[i])
		{
			if(2*i+2<=n-1&&arr[2*i+2]>arr[2*i+1])
			{
				swap(arr,2*i+2,i);
			}
			else
			{
				swap(arr,2*i+1,i);
			}
		} 
		 else if(2*i+2<=n-1&&arr[2*i+2]>arr[i])
		{
			swap(arr,2*i+2,i);
		}
	}
	for(i = 1;i<=n/2-1;i++)
	{
		
		if(arr[2*i+1]>arr[i])
		{
			if(2*i+2<=n-1&&arr[2*i+2]>arr[2*i+1])
			{
				swap(arr,2*i+2,i);
			}
			else
			{
				swap(arr,2*i+1,i);
			}
		} 
		 else if(2*i+2<=n-1&&arr[2*i+2]>arr[i])
		{
			swap(arr,2*i+2,i);
		}
	}
	
}
int* heapSort(int* arr,int n)
{
	while(n>=2)
	{
		createHeap(arr,n);
		swap(arr,0,n-1);
		n--;
	}
	return arr;
}
int main()
{
	int arr[]={5,4,11,8,9,6,12,8,0,10},* sortArr;
	int n = sizeof(arr)/sizeof(int),i=0;
	printf("原数组:\n");
	for(;i<n;i++)
	{
		printf("%d ",arr[i]);
	}
	printf("\n");
	sortArr=heapSort(arr,n);
	printf("堆排序数组:\n");
	for(i=0;i<n;i++)
	{
		printf("%d ",sortArr[i]);
	}
	printf("\n");
	return 0;
}