#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<limits.h>
#include<string.h>
#include<stdlib.h>
const int MAX_LEN = 100;//初始化队列、栈的最大长度
//枚举定义返回状态类型
enum TYPE
{
    TRUE=1,
    FALSE=0,
    ERROR=-1
};
//二叉树的存储结构
typedef struct
{
    int val;
    struct BinaryTree* left;
    struct BinaryTree* right;
} BinaryTree,*TreeNode;
typedef BinaryTree* Tree;
typedef BinaryTree DataType;
//线性栈的存储结构
struct Stack
{
    int top;
    DataType** arr;
};
typedef struct Stack stack;
//初始化线性栈
void initStack(stack** s)
{
    *s=(stack*)malloc(sizeof(stack));
    if(!(*s))
    {
        printf("内存分配失败\n");
        exit(-1);
    }
    (*s)->top=-1;
    (*s)->arr=(DataType** )malloc(MAX_LEN*sizeof(DataType*));
}
//线性队列的存储结构
typedef struct Queue
{
    int front;
    int rear;
    DataType** arr;
} queue;
//初始化线性队列
void initQueue(queue** q)
{
    (*q)=(queue*)malloc(sizeof(queue));
    (*q)->front = (*q)->rear = -1;
    (*q)->arr=(DataType** )malloc(MAX_LEN*sizeof(DataType* ));
}
//判断队列是否为满
int queueFull(queue* q)
{
    return (q->rear + 1)%MAX_LEN==q->front;
}
//判断队列是否为空
int queueEmpty(queue* q)
{
    return q->rear==q->front&&q->rear==-1;
}
//元素入队
void enQueue(queue** q,DataType* dataType)
{
    if(queueFull((*q)))
    {
        printf("Queue Full\n");
        return;
    }
    if((*q)->front==-1)(*q)->front=0;
    (*q)->arr[++((*q)->rear)]=dataType;
}
//元素出队
void deQueue(queue** q,DataType** dataType)
{
    if(queueEmpty(*q))
    {
        printf("Queue Empty\n");
        return;
    }
    *dataType=(*q)->arr[((*q)->front)++];
    if((*q)->rear<(*q)->front)(*q)->front=(*q)->rear=-1;
}
//判断栈是否为空
int stackEmpty(stack* s)
{
    return s->top==-1;
}
//取栈顶元素
int getFront(stack** s,DataType** dataType)
{
    if((*s)->top==-1)return FALSE;
    *dataType=(*s)->arr[((*s)->top)];
    return TRUE;
}
//将元素压入栈底
void push(stack** s,DataType* dataType)
{
    if((*s)->top==MAX_LEN)
    {
        printf("stack full!\n");
        return;
    }
    (*s)->arr[++((*s)->top)]=dataType;
}
//将元素弹出
void pop(stack** s,DataType** dataType)
{
    if((*s)->top==-1)
    {
        printf("stack empty!\n");
        return;
    }
    *dataType=(*s)->arr[((*s)->top)--];
}
//创建二叉树
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
//递归前序遍历
void preOrder(Tree root)
{
    if(!root)return;
    printf("%d ",root->val);
    preOrder(root->left);
    preOrder(root->right);
}
//非递归前序遍历
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
        if(node->right)push(&s,node->right);
        if(node->left)push(&s,node->left);
    }
}
//队列实现层次遍历
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
        if(node->left)enQueue(&q,node->left);
        if(node->right) enQueue(&q,node->right);
    }
	printf("\n");
}
//销毁二叉树
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
    printf("递归前序遍历\n");
    preOrder(root);
    printf("\n非递归前序遍历\n");
    pre_order(root);
    printf("\n广度优先遍历\n");
    levelOrder(root);
    free(root);
    return 0;
}
