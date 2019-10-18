#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<limits.h>
#include<string.h>
#include<stdlib.h>
const int MAX_LEN=20;
enum TYPE
{
    TRUE=1,
    FALSE=0,
    ERROR=-1
};
typedef struct
{
    int val;
    struct BinaryTree* left;
    struct BinaryTree* right;
} BinaryTree,*TreeNode;
typedef BinaryTree* Tree;
typedef BinaryTree DataType;
struct Stack
{
    int top;
    DataType** arr;
};
typedef struct Stack stack;
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
typedef struct Queue
{
    int front;
    int rear;
    DataType** arr;
} queue;
void initQueue(queue** q)
{
    (*q)=(queue*)malloc(sizeof(queue));
    (*q)->front = (*q)->rear = -1;
    (*q)->arr=(DataType** )malloc(MAX_LEN*sizeof(DataType* ));
}
int queueFull(queue* q)
{
    return (q->rear + 1)%MAX_LEN==q->front;
}
int queueEmpty(queue* q)
{
    return q->rear==q->front&&q->rear==-1;
}
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
int stackEmpty(stack* s)
{
    return s->top==-1;
}
int getFront(stack** s,DataType** dataType)
{
    if((*s)->top==-1)
    {
        return FALSE;
    }
    *dataType=(*s)->arr[((*s)->top)];
    return TRUE;
}
void push(stack** s,DataType* dataType)
{
    if((*s)->top==MAX_LEN)
    {
        printf("stack full!\n");
        return;
    }
    (*s)->arr[++((*s)->top)]=dataType;
}
void pop(stack** s,DataType** dataType)
{
    if((*s)->top==-1)
    {
        printf("stack empty!\n");
        return;
    }
    *dataType=(*s)->arr[((*s)->top)--];
}
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
void preOrder(Tree root)
{
    if(!root)return;
    printf("%d ",root->val);
    preOrder(root->left);
    preOrder(root->right);
}
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
void levelOrder(Tree root)
{
    Tree node=NULL;
    queue* q=NULL;
    int i,num,count=0;
    if(!root)return;
    initQueue(&q);
    enQueue(&q,root);
    num=1;
    while(!queueEmpty(q))
    {
        for(i=0; i<num; i++)
        {
            deQueue(&q,&node);
            printf("%d ",node->val);
            if(node->left)
            {
                enQueue(&q,node->left);
                count++;
            }
            if(node->right)
            {
                enQueue(&q,node->right);
                count++;
            }
        }
        num=count;
        count=0;
    }
}
int main()
{
    Tree root;
    createTree(&root);
    printf("递归前序遍历\n");
    preOrder(root);
    printf("\n非递归前序遍历");
    pre_order(root);
    printf("广度优先遍历\n");
    levelOrder(root);
    free(root);
    return 0;
}