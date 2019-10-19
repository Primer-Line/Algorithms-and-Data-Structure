#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<limits.h>
#include<string.h>
#include<stdlib.h>
const int MAX_LEN = 100;//��ʼ�����С�ջ����󳤶�
//ö�ٶ��巵��״̬����
enum TYPE
{
    TRUE=1,
    FALSE=0,
    ERROR=-1
};
//�������Ĵ洢�ṹ
typedef struct
{
    int val;
    struct BinaryTree* left;
    struct BinaryTree* right;
} BinaryTree,*TreeNode;
typedef BinaryTree* Tree;
typedef BinaryTree DataType;
//����ջ�Ĵ洢�ṹ
struct Stack
{
    int top;
    DataType** arr;
};
typedef struct Stack stack;
//��ʼ������ջ
void initStack(stack** s)
{
    *s=(stack*)malloc(sizeof(stack));
    if(!(*s))
    {
        printf("�ڴ����ʧ��\n");
        exit(-1);
    }
    (*s)->top=-1;
    (*s)->arr=(DataType** )malloc(MAX_LEN*sizeof(DataType*));
}
//���Զ��еĴ洢�ṹ
typedef struct Queue
{
    int front;
    int rear;
    DataType** arr;
} queue;
//��ʼ�����Զ���
void initQueue(queue** q)
{
    (*q)=(queue*)malloc(sizeof(queue));
    (*q)->front = (*q)->rear = -1;
    (*q)->arr=(DataType** )malloc(MAX_LEN*sizeof(DataType* ));
}
//�ж϶����Ƿ�Ϊ��
int queueFull(queue* q)
{
    return (q->rear + 1)%MAX_LEN==q->front;
}
//�ж϶����Ƿ�Ϊ��
int queueEmpty(queue* q)
{
    return q->rear==q->front&&q->rear==-1;
}
//Ԫ�����
void enQueue(queue** q,DataType* dataType)
{
    if(queueFull((*q)))
    {
        printf("Queue Full\n");
        return;
    }
    if((*q)->front==-1)
    {
        (*q)->front=0;
    }
    (*q)->arr[++((*q)->rear)]=dataType;
}
//Ԫ�س���
void deQueue(queue** q,DataType** dataType)
{
    if(queueEmpty(*q))
    {
        printf("Queue Empty\n");
        return;
    }

    *dataType=(*q)->arr[((*q)->front)++];
    if((*q)->rear<(*q)->front)
    {
        (*q)->front=(*q)->rear=-1;
    }
}
//�ж�ջ�Ƿ�Ϊ��
int stackEmpty(stack* s)
{
    return s->top==-1;
}
//ȡջ��Ԫ��
int getFront(stack** s,DataType** dataType)
{
    if((*s)->top==-1)
    {
        return FALSE;
    }
    *dataType=(*s)->arr[((*s)->top)];
    return TRUE;
}
//��Ԫ��ѹ��ջ��
void push(stack** s,DataType* dataType)
{
    if((*s)->top==MAX_LEN)
    {
        printf("stack full!\n");
        return;
    }
    (*s)->arr[++((*s)->top)]=dataType;
}
//��Ԫ�ص���
void pop(stack** s,DataType** dataType)
{
    if((*s)->top==-1)
    {
        printf("stack empty!\n");
        return;
    }
    *dataType=(*s)->arr[((*s)->top)--];
}
//����������
void createTree(Tree* root)
{
    int val;
    printf("input node's val:\n");
    scanf("%d",&val);
    if(val<=0)
    {
        *root=NULL;
        return;
    }
    *root=(Tree)malloc(sizeof(BinaryTree));
    (*root)->val=val;
    createTree(&((*root)->left));
    createTree(&((*root)->right));
}
//�ݹ�ǰ�����
void preOrder(Tree root)
{
    if(!root)return;
    printf("%d ",root->val);
    preOrder(root->left);
    preOrder(root->right);
}
//�ǵݹ�ǰ�����
void pre_order(Tree root)
{
    stack* s=NULL;
    Tree node=NULL;
    if(!root)return;
    initStack(&s);
    push(&s,root);
    while(!stackEmpty(s))
    {
        pop(&s,&node);
        printf("%d ",node->val);
        if(node->right)
        {
            push(&s,node->right);
        }
        if(node->left)
        {
            push(&s,node->left);
        }
    }
}
//����ʵ�ֲ�α���
void levelOrder(Tree root)
{
    Tree node=NULL;
    queue* q=NULL;
    if(!root)return;
    initQueue(&q);
    enQueue(&q,root);
    while(!queueEmpty(q))
    {
        deQueue(&q,&node);
        printf("%d ",node->val);
        if(node->left)
        {
            enQueue(&q,node->left);
        }
        if(node->right)
        {
            enQueue(&q,node->right);
        }
    }
	printf("\n");
}
//���ٶ�����
void destoryTree(Tree* root)
{
	Tree left,right;
	if(!(*root))return;
	left=(*root)->left;
	right=(*root)->right;
	free(*root);
	(*root)=NULL;
	destoryTree(&left);
	destoryTree(&right);
}
int main()
{
    Tree root;
    createTree(&root);
    printf("�ݹ�ǰ�����\n");
    preOrder(root);
    printf("\n�ǵݹ�ǰ�����\n");
    pre_order(root);
    printf("\n������ȱ���\n");
    levelOrder(root);
    free(root);
    return 0;
}