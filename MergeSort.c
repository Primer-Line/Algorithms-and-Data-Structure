#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//归并排序
void merge_sort(int** arr,int* array,int left,int right);
void mergeSort(int** arr,int* array,int left,int right)
{ 
	int m=(left+right)/2;
	if(left<right)
	{
		mergeSort(&(*arr),array,left,m);
		mergeSort(&(*arr),array,m+1,right);
		merge_sort(&(*arr),array,left,right);
	}
}
void merge_sort(int** arr,int* array,int left,int right)
{
	int middle = (left+right)/2;
	int a=left,b=middle+1,index=0,i;
	while(a<=middle&&b<=right)
	{
		if((*arr)[a]>(*arr)[b])array[index++]=(*arr)[b++];
		else array[index++]=(*arr)[a++];
	}
	while(a<=middle)array[index++]=(*arr)[a++];
	while(b<=right)array[index++]=(*arr)[b++];
    for(i=0;i<=right-left;i++)(*arr)[left+i]=array[i];
}
int main()
{
	int arr[]={5,1,10,3,8,9,2,4,0,6,7},n=sizeof(arr)/sizeof(int),i;
	int* array=(int* )malloc(n*sizeof(int));
	int* temp=&arr[0];
	printf("归并排序\n");
	printf("原始数组:\n");
	for(i=0;i<n;i++)
	{
		printf("%d ",temp[i]);
	}
	printf("\n");
	mergeSort(&temp,array,0,n-1);
	printf("现数组:\n");
	for(i=0;i<n;i++)
	{
		printf("%d ",temp[i]);
	}
	printf("\n");
	return 0;
}