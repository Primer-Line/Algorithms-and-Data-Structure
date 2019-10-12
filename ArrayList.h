#define DEFALUT_MAX_LENGTH 20	
struct Frequency
{
	char data;
	int frequency;
};
typedef struct ArrayList
{
	struct Frequency** arr;
	int max_length;
	int current_length;
}List;
void initArrayList(struct ArrayList** list)
{
	(*list)=(struct ArrayList* )malloc(sizeof(struct ArrayList));
	(*list)->arr=(struct Frequency** )malloc(DEFALUT_MAX_LENGTH*sizeof(struct Frequency* ));
	(*list)->max_length=DEFALUT_MAX_LENGTH;
	(*list)->current_length=0;
}
void add(struct ArrayList** list,char data,int _frequency)
{
	struct Frequency* frequency=(struct Frequency* )malloc(sizeof(struct Frequency)),**arr;
	frequency->data=data;
	frequency->frequency=_frequency;
	if((*list)->current_length==(*list)->max_length)
	{
		(*list)->max_length+=(*list)->max_length;
		arr=(struct Frequency** )malloc(((*list)->max_length)*sizeof(struct Frequency*));
		arr=(*list)->arr;
		arr[(*list)->current_length++]=frequency;
		(*list)->arr=arr;
		
	}
	else
	{
		(*list)->arr[(*list)->current_length++]=frequency;
	}
}