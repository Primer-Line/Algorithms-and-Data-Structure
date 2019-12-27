#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void sort(int* arr,int n)
{
    int i,index=0;
    int min=arr[0],max=arr[0],*nums;
    for(i=1; i<n; i++)
    {
        if(arr[i]<min)min=arr[i];
        if(arr[i]>max)max=arr[i];
    }
    nums=(int* )malloc((max-min+1)*sizeof(int));
    memset(nums,0,(max-min+1)*sizeof(int));
    for(i=0; i<n; i++)nums[arr[i]-min]++;
    for(i=0; i<=max-min; i++)
    {
        if(nums[i]>0)
        {
            while(nums[i]-->0)arr[index++]=i+min;
        }
    }
    free(nums);
}

int main()
{
    int arr[]= {13,15,9,0,11,10,9,6,6,18,7,3,5,11,18,3,2,7};
    int i,n=sizeof(arr)/sizeof(int);
    sort(arr,n);
    for(i=0; i<n; i++)printf("%d ",arr[i]);
    printf("\n");
}
