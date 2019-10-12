#define MAX_LENGTH 10
typedef char Element;
typedef struct HuffmanTree
{
	Element data;
	int weight;
	struct HuffmanTree* left;
	struct HuffmanTree* right;
	struct HuffmanTree* parent;
}Tree,*huffmanTree;
typedef struct Heap
{
	struct HuffmanTree** arr;
	int current_length;
	int max_length;
}heap;
void adjustHeap(struct HuffmanTree** nodes,int size);
void initHeap(struct Heap** heap)
{
	(*heap) = (struct Heap* )malloc(sizeof(struct Heap));
	(*heap)->arr=(struct HuffmanTree** )malloc(sizeof(struct HuffmanTree*)*MAX_LENGTH);
	(*heap)->current_length=0;
	(*heap)->max_length=MAX_LENGTH;
}
void insertHeap(struct Heap** heap,struct HuffmanTree** node)
{
	struct HuffmanTree** arr;
	if((*heap)->current_length==(*heap)->max_length)
	{
		(*heap)->max_length+=(*heap)->max_length;
		arr=(struct HuffmanTree** )malloc(sizeof(struct HuffmanTree*)*((*heap)->max_length));
		arr=(*heap)->arr;
		arr[(*heap)->current_length++]=(*node);
		(*heap)->arr=arr;
	}
	else
	{
		(*heap)->arr[(*heap)->current_length++]=(*node);
	}
	adjustHeap((*heap)->arr,(*heap)->current_length);

}
void swap(struct HuffmanTree** a,struct HuffmanTree** b)
{
	struct HuffmanTree* temp=(*a);
	(*a)=(*b);
	(*b)=temp;
}
void deleteHeap(struct Heap** heap,struct HuffmanTree** val)
{
	*val=(*heap)->arr[0];
	swap(&((*heap)->arr[0]),&((*heap)->arr[(*heap)->current_length-1]));
	(*heap)->current_length--;
	adjustHeap((*heap)->arr,(*heap)->current_length);
}
void adjustHeap(struct HuffmanTree** nodes,int size)
{
	int i;
	struct HuffmanTree* temp;
	if(size==1)return;
	for(i = size/2-1;i>=0;i--)
	{
		if(i == size/2-1&&(2*i)!=size-3)
		{
			temp=nodes[2*i+1];
		}
		else
		{
			temp=nodes[2*i+1]->weight<nodes[2*i+2]->weight?nodes[2*i+1]:nodes[2*i+2];
		}
		if(temp->weight<nodes[i]->weight)
		{
			swap(temp==nodes[2*i+1]?(&nodes[2*i+1]):(&nodes[2*i+2]),&nodes[i]);
		}
	}
	for(i = 0;i<=size/2-1;i++)
	{
		if(i == size/2-1&&(2*i)!=size-3)
		{
			temp=nodes[2*i+1];
		}
		else
		{
			temp=nodes[2*i+1]->weight<nodes[2*i+2]->weight?nodes[2*i+1]:nodes[2*i+2];
		}
		if(temp->weight<nodes[i]->weight)
		{
			swap(temp==nodes[2*i+1]?(&nodes[2*i+1]):(&nodes[2*i+2]),&nodes[i]);
		}
	}
}
void heapSort(struct Heap* h)
{
	struct Heap* heap=h;
	int n = heap->current_length,i;
	while(--n>0)
	{
		swap(&(heap->arr[0]),&(heap->arr[n]));
		adjustHeap(heap->arr,n);
	}
	for(i=0;i<heap->current_length;i++)
	{
		printf("%c  %d\n",heap->arr[i]->data,heap->arr[i]->weight);
	}

}
