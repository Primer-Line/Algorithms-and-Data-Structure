#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*
平衡二叉树的链式存储实现
1.二叉搜索树的节点插入与平衡处理
2.二叉搜索树的节点删除与平衡处理
3.销毁平衡二叉树
*/
#define FALSE 0
#define TRUE 1
#define ERROR -1
typedef char Element; 
enum STATUS
{
	a = 0,
	b = -1,
	c = 1
};
//联合
union BinaryTree{
	int val;
	union BinaryTree* parent;
	union BinaryTree* left;
	union BinaryTree* right;
}binaryTree;
//平衡二叉树的存储结构
typedef struct BalanceBinaryTree
{
	int val;//键值
	int bf;//平衡因子
	struct BalanceBinaryTree* parent;//父节点指针
	struct BalanceBinaryTree* left;//左孩子指针
	struct BalanceBinaryTree* right;//右孩子指针
}Tree;
int getHeight(Tree* root);
void createNode(Tree** node,int data);
void leftRotation(Tree** root);
void rightRotation(Tree** root);
void setBalance(Tree** root,Tree* node);
void recoverBalance(Tree** root);
void insertNode(Tree** root,int val);
void deleteNode(Tree** root,int val);
void preOrder(Tree* root);
void order(Tree* root);
void destoryTree(Tree** root);
//创建树节点指针
void createNode(Tree** node,int data)
{
	//内存分配
	*node = (struct BalanceBinaryTree* )malloc(sizeof(struct BalanceBinaryTree));
	if(!(*node))
	{
		printf("内存分配失败\n");
		exit(-1);
	}
	memset((*node),0,sizeof((*node)));
	(*node)->val = data;
}
//左旋
void leftRotation(Tree** root)
{
	Tree* node=(*root)->right;
	(*root)->right=node->left;
	if(node->left)
	{
		node->left->parent=(*root);
	}
	//更新根节点
	node->left=(*root);
	(*root)->parent=node;
	(*root)=node;
}
//右旋
void rightRotation(Tree** root)
{
	Tree* node=(*root)->left;
	(*root)->left=node->right;
	if(node->right)
	{
		node->right->parent=*root;
	}
	node->right=(*root);
	(*root)->parent=node;
	(*root)=node;
}
//计算平衡因子
int getBF(Tree* root)
{
	int left,right;
	left=getHeight(root->left);
	right=getHeight(root->right);
	return left-right;
}
//查找指定键值的节点
void searchNode(Tree* root,Tree** p,int val)
{
	Tree* node=root;
	while(node&&node->val!=val)node=node->val>val?node->left:node->right;
	(*p) = node;
}
//查找最低不平衡节点并恢复平衡
void splitNode(Tree** root,Tree* p)
{
	Tree *q=NULL;
	int k;
	while(p&&(p->bf=getBF(p))>=-1&&p->bf<=1) p=p->parent;
	if(p)
	{
		q=p->parent;
		if(q) k=p==q->left?0:1;
		recoverBalance(&p);
		if(q)
		{
			if(k) q->right=p;
			else q->left=p;
			p->parent=q;
		}
		else
		{
			*root=p;
			(*root)->parent=NULL;
		}
	}
}
//左旋、右旋、双旋恢复平衡
void recoverBalance(Tree** root)
{
	if((*root)->bf<-1)
	{
		if((*root)->right->left)
		{
			rightRotation(&((*root)->right));
			(*root)->right->parent=(*root);
			leftRotation(&(*root));
		}
		else leftRotation(&(*root));
	}
	else
	{
		if((*root)->left->right)
		{
			leftRotation(&((*root)->left));
			(*root)->left->parent=(*root);
			rightRotation(&(*root));
		}
		else rightRotation(&(*root));
	}
	(*root)->bf=getBF((*root));
}
//查找键值最小的节点
void getMinNode(Tree* root,Tree** node)
{
	Tree* p=root;
	while(p->left)p=p->left;
	(*node) = p;
}
//恢复平衡
void setBalance(Tree** root,Tree* node)
{
	if((*root)->bf>1)
	{
		if(node->val<(*root)->left->val)rightRotation(&(*root));
		else
		{
			leftRotation(&((*root)->left));
			(*root)->left->parent=(*root);
			rightRotation(&(*root));
		}
	} 
	else if((*root)->bf<-1)
	{
		if(node->val>(*root)->right->val)leftRotation(&(*root));
		else
		{
			rightRotation(&((*root)->right));
			(*root)->right->parent=(*root);
			leftRotation(&(*root)); 
		}
	}
	(*root)->bf=getBF(*root);
}
//删除节点并恢复平衡
void deleteNode(Tree** root,int val)
{
	Tree* node=NULL,*p = NULL;
	int temp;
	searchNode(*root,&node,val);
	if(!node)return;
	if(!node->left&&!node->right)
	{
		if(node==(*root))
		{
			(*root)=NULL;
			return;
		}
		if(node==node->parent->left)node->parent->left=NULL;
		else node->parent->right=NULL;
		splitNode(&(*root),node->parent);
	}
	else if(node->left&&!node->right)
	{
		if(node==(*root))
		{
			(*root)=(*root)->left;
			splitNode(&(*root),(*root));
			return;
		}
		if(node==node->parent->left)node->parent->left=node->left;
		else node->parent->right=node->left;
		node->left->parent=node->parent;
		splitNode(&(*root),node->parent);
	}else if(!node->left&&node->right)
	{
		if((*root)==node)
		{
			(*root)=(*root)->right;
			splitNode(&(*root),(*root));
			return;
		}
		if(node==node->parent->left)node->parent->left=node->right;
		else node->parent->right=node->right;
		node->right->parent=node->parent;
		splitNode(&(*root),node->parent);
	}else
	{
		getMinNode(node->right,&p);
		temp=p->val;
		p->val=node->val;
		node->val=temp;
		if(p==p->parent->left)p->parent->left=NULL;
		else p->parent->right=NULL;
		splitNode(&(*root),p->parent);	
	}
}
//插入节点并恢复平衡
void insertNode(Tree** root,int val)
{
	struct BalanceBinaryTree* node=NULL,*p=(*root),*q=NULL,*h=NULL,*parent=NULL;
	int k;
	if(!(*root))
	{
		createNode(&(*root),val);
		(*root)->left=NULL;
		(*root)->right=NULL;
		(*root)->parent=NULL;
		(*root)->bf=0;
		return;
	}
	createNode(&node,val);
	node->left=NULL;
	node->right=NULL;
	while(p)
	{
		q=p;
		p=node->val<p->val?p->left:p->right;
	}
	if(q->val>val)q->left=node;
	else q->right=node;
	node->parent=q;
	node->bf=0;
	h=node->parent;
	while(h&&(h->bf=getBF(h))>=-1&&h->bf<=1)h=h->parent;
	if(h)
	{
		parent=h->parent;
		if(parent)k=h==parent->left?0:1;
		setBalance(&h,node);
		if(parent)
		{
			if(k)parent->right=h;
			else parent->left=h;
			h->parent=parent;
		}
		else
		{
			*root=h;
			(*root)->parent=NULL;
		}
	}
}
//前序遍历
void preOrder(Tree* root)
{
	if(!root)return;
	printf("%d ",root->val);
	preOrder(root->left);
	preOrder(root->right);

}
//中序遍历
void order(Tree* root)
{
	if(!root)return;
	order(root->left);
	printf("%d ",root->val);
	order(root->right);

}
//获取树高
int getHeight(Tree* root)
{
	int left,right;
	if(root==NULL)return 0;
	left=getHeight(root->left);
	right=getHeight(root->right);
	return left>right?left+1:right+1;

}
//判断二叉搜索树是否平衡
int isBalance(Tree* root)
{
	int left,right;
	if(!root)return 1;
	left=getHeight(root->left);
	right=getHeight(root->right);
	if(left-right>1||left-right<-1)return 0;
	return isBalance(root->left)&&isBalance(root->right);
}
//销毁平衡二叉树
void destoryTree(Tree** root)
{
	Tree* left = NULL,*right = NULL;
	if(!(*root))return;
	left = (*root)->left;
	right = (*root)->right;
	free(*root);
	*root = NULL;
	destoryTree(&left);
	destoryTree(&right);
}
int main()
{
	int arr[]={0,1,2,3,4,5,6,7,8,9,10,11};
	//int arr[]={55,31,11,37,46,73,63,2,7};
	//int arr[]={12,4,1,7,8,10,9,2,11,6,5};
	int i,len=sizeof(arr)/sizeof(int);
	Tree* root=NULL;
	for(i=0;i<len;i++)
	{
		insertNode(&root,arr[i]);
	}
	printf("二叉搜索树建立完毕:%s\n",isBalance(root)?"二叉搜索树已平衡":"二叉搜索树不平衡");
	printf("根节点的平衡因子:%d\n",root->bf);
	printf("前序遍历:\n");
	preOrder(root);
	printf("\n");
	printf("中序遍历:\n");
	order(root);
	printf("\n");
	//printf("删除节点10:\n");
	//deleteNode(&root,10);
	//printf("删除节点8:\n");
	//deleteNode(&root,8);
	printf("删除节点3:%s\n",isBalance(root)?"二叉搜索树保持平衡":"二叉搜索树不平衡");
	printf("根节点的平衡因子:%d\n",root->bf);
	deleteNode(&root,3);
	printf("前序遍历:\n");
	preOrder(root);
	printf("\n");
	printf("中序遍历:\n");
	order(root);
	printf("\n");
	destoryTree(&root);
	return 0;
}
