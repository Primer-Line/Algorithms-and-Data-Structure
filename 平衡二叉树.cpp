#include<stdio.h>
#include<stdlib.h>
#include<string.h>
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
union BinaryTree{
	int val;
	union BinaryTree* parent;
	union BinaryTree* left;
	union BinaryTree* right;
}binaryTree;
typedef struct BalanceBinaryTree
{
	int val;
	int bf;
	struct BalanceBinaryTree* parent;
	struct BalanceBinaryTree* left;
	struct BalanceBinaryTree* right;
}Tree;
Tree* initTree();
int getHeight(Tree* root);
struct BalanceBinaryTree* createNode(int data);
void leftRotation(Tree** root);
void rightRotation(Tree** root);
void setBalance(Tree** root,Tree* node);
void recoverBalance(Tree** root);
void insertNode(Tree** root,int val);
void deleteNode(Tree** root,int val);
void preOrder(Tree* root);
void order(Tree* root);
Tree* initTree()
{
	struct BalanceBinaryTree* root=NULL;
	return root;
}
struct BalanceBinaryTree* createNode(int data)
{
	struct BalanceBinaryTree* node = (struct BalanceBinaryTree* )malloc(sizeof(struct BalanceBinaryTree));
	if(!node)
	{
		printf("�ڴ����ʧ��\n");
		exit(-1);
	}
	memset(node,0,sizeof(node));
	node->val = data;
	return node;
}
void leftRotation(Tree** root)
{
	Tree* node=(*root)->right;
	(*root)->right=node->left;
	if(node->left)
	{
		node->left->parent=(*root);
	}
	node->left=(*root);
	(*root)->parent=node;
	(*root)=node;
}
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
int getBF(Tree* root)
{
	int left,right;
	left=getHeight(root->left);
	right=getHeight(root->right);
	return left-right;
}
Tree* searchNode(Tree* root,int val)
{
	Tree* node=root;
	while(node&&node->val!=val)
	{
		node=node->val>val?node->left:node->right;
	}
	return node;
}
void splitNode(Tree** root,Tree* p)
{
	Tree *q=NULL;
	int k;
	while(p&&(p->bf=getBF(p))>=-1&&p->bf<=1)
	{
			p=p->parent;
	}
	if(p)
	{
		q=p->parent;
		if(q)
		{
			k=p==q->left?0:1;
		}
		recoverBalance(&p);
		if(q)
		{
			if(k)
			{
				q->right=p;
			}
			else
			{
				q->left=p;
			}
			p->parent=q;
		}
		else
		{
			*root=p;
			(*root)->parent=NULL;
		}
	}
}
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
		else
		{
			leftRotation(&(*root));
		}
	}
	else
	{
		if((*root)->left->right)
		{
			leftRotation(&((*root)->left));
			(*root)->left->parent=(*root);
			rightRotation(&(*root));
		}
		else
		{
			rightRotation(&(*root));
		}
	}
	(*root)->bf=getBF((*root));
}
Tree* getMinNode(Tree* root)
{
	Tree* p=root;
	while(p->left)
	{
		p=p->left;
	}
	return p;
}
void setBalance(Tree** root,Tree* node)
{
	if((*root)->bf>1)
	{
		if(node->val<(*root)->left->val)
		{
			rightRotation(&(*root));
		} 
		else
		{
			leftRotation(&((*root)->left));
			(*root)->left->parent=(*root);
			rightRotation(&(*root));
		}
	} 
	else if((*root)->bf<-1)
	{
		if(node->val>(*root)->right->val)
		{
			leftRotation(&(*root));
		} 
		else
		{
			rightRotation(&((*root)->right));
			(*root)->right->parent=(*root);
			leftRotation(&(*root)); 
		}
	}
	(*root)->bf=getBF(*root);
}

void deleteNode(Tree** root,int val)
{
	Tree* node=searchNode(*root,val),*p=NULL;
	int temp;
	if(!node)return;
	if(!node->left&&!node->right)
	{
		if(node==(*root))
		{
			(*root)=NULL;
			return;
		}
		if(node==node->parent->left)
		{
			node->parent->left=NULL;
		}
		else
		{
			node->parent->right=NULL;
		}
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
		if(node==node->parent->left)
		{
			node->parent->left=node->left;
		}
		else
		{
			node->parent->right=node->left;
		}
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
		if(node==node->parent->left)
		{
			node->parent->left=node->right;
		}
		else
		{
			node->parent->right=node->right;
		}
		node->right->parent=node->parent;
		splitNode(&(*root),node->parent);
	}else
	{
		p=getMinNode(node->right);
		temp=p->val;
		p->val=node->val;
		node->val=temp;
		if(p==p->parent->left)
		{
			p->parent->left=NULL;
		}
		else
		{
			p->parent->right=NULL;
		}
		splitNode(&(*root),p->parent);	
	}
}
void insertNode(Tree** root,int val)
{
	struct BalanceBinaryTree* node=NULL,*p=(*root),*q=NULL,*h=NULL,*parent=NULL;
	int k;
	if(!(*root))
	{
		(*root)=createNode(val);
		(*root)->left=NULL;
		(*root)->right=NULL;
		(*root)->parent=NULL;
		(*root)->bf=0;
		return;
	}
	node=createNode(val);
	node->left=NULL;
	node->right=NULL;
	while(p)
	{
		q=p;
		p=node->val<p->val?p->left:p->right;
	}
	if(q->val>val)
	{
		q->left=node;
	}
	else
	{
		q->right=node;
	}
	node->parent=q;
	node->bf=0;
	h=node->parent;
	while(h&&(h->bf=getBF(h))>=-1&&h->bf<=1)
	{
		h=h->parent;
	}
	if(h)
	{
		parent=h->parent;
		if(parent)
		{
			k=h==parent->left?0:1;
		}
		setBalance(&h,node);
		if(parent)
		{
			if(k)
			{
				parent->right=h;
			}
			else
			{
				parent->left=h;
			}
			h->parent=parent;
		}
		else
		{
			*root=h;
			(*root)->parent=NULL;
		}
	}
}
void preOrder(Tree* root)
{
	if(!root)return;
	printf("%d ",root->val);
	preOrder(root->left);
	preOrder(root->right);

}
void order(Tree* root)
{
	if(!root)return;
	order(root->left);
	printf("%d ",root->val);
	order(root->right);

}
int getHeight(Tree* root)
{
	int left,right;
	if(root==NULL)return 0;
	left=getHeight(root->left);
	right=getHeight(root->right);
	return left>right?left+1:right+1;

}
int isBalance(Tree* root)
{
	int left,right;
	if(!root)return 1;
	left=getHeight(root->left);
	right=getHeight(root->right);
	if(left-right>1||left-right<-1)
	{
		return 0;
	}
	return isBalance(root->left)&&isBalance(root->right);
}
int main()
{
	int arr[]={0,1,2,3,4,5,6,7,8,9,10,11};
	//int arr[]={55,31,11,37,46,73,63,2,7};
	//int arr[]={12,4,1,7,8,10,9,2,11,6,5};
	int i,len=sizeof(arr)/sizeof(int);
	Tree* root=initTree();
	for(i=0;i<len;i++)
	{
		insertNode(&root,arr[i]);
	}
	printf("�����������������:%s\n",isBalance(root)?"������������ƽ��":"������������ƽ��");
	printf("���ڵ��ƽ������:%d\n",root->bf);
	printf("ǰ�����:\n");
	preOrder(root);
	printf("\n");
	printf("�������:\n");
	order(root);
	printf("\n");
	//printf("ɾ���ڵ�10:\n");
	//deleteNode(&root,10);
	//printf("ɾ���ڵ�8:\n");
	//deleteNode(&root,8);
	printf("ɾ���ڵ�3:%s\n",isBalance(root)?"��������������ƽ��":"������������ƽ��");
	printf("���ڵ��ƽ������:%d\n",root->bf);
	deleteNode(&root,3);
	printf("ǰ�����:\n");
	preOrder(root);
	printf("\n");
	printf("�������:\n");
	order(root);
	printf("\n");
	free(root);
	return 0;
}
