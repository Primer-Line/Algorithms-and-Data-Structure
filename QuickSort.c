#include<stdio.h>
int* quickSort(int* arr,int low,int high)
{
	int i,temp,index=high,j;
	for(i=low;i<high;i++)
	{
		if(arr[i]>=arr[high])
		{
			temp=arr[i];
			while(arr[index]>=arr[high]&&index>i)index--;
			arr[i]=arr[index];
			arr[index]=temp;
		}
		if(index==i)
		{
			temp=arr[high];
			for(j=high;j>index;j--)arr[j]=arr[j-1];
			arr[index]=temp;
			break;
		}
	}
	if(low>=high)return arr;
	arr=quickSort(arr,0,index-1);
	arr=quickSort(arr,index+1,high);
	return arr;
}
int main()
{
	int arr[]={5,6,1,4,9,8,2,5,1,7,8,3,4,6,7,1,0,3,7};
	int* a,i;
	int high=sizeof(arr)/sizeof(int);
	a=quickSort(arr,0,high-1);
	for(i=0;i<high;i++)printf("%d ",a[i]);
	printf("\n");
	return 0;
}
