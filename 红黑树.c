#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef int dataType;
typedef unsigned int UINT;
/*
红黑树
1.红黑树的插入算法实现
2.红黑树的删除算法实现
3.销毁红黑树
*/
//枚举定义红黑树节点颜色
typedef enum COLOR
{
	RED=0,
	BLACK=1
}Color;
//红黑树的链式存储实现
typedef struct RedBlackTree
{
	dataType val;//键值
	Color color;//颜色
	struct RedBlackTree* left;//左节点指针
	struct RedBlackTree* right;//右节点指针
	struct RedBlackTree* parent;//父节点指针
}Tree;
//创建节点指针
void createNode(struct RedBlackTree** node,dataType val)
{
	*node=(struct RedBlackTree* )malloc(sizeof(struct RedBlackTree));
	if(!(*node))exit(-1);
	memset((*node),0,sizeof((*node)));
	(*node)->parent=NULL;
	(*node)->left=NULL;
	(*node)->right=NULL;
	(*node)->val=val;
	(*node)->color=RED;
}
//左旋转
void leftRotation(Tree** root)
{
	Tree* p=(*root)->right;
	(*root)->right=p->left;
	if(p->left)p->left->parent=(*root);
	p->left=(*root);
	(*root)->parent=p;
	(*root)=p;
}
//右旋转
void rightRotation(Tree** root)
{
	Tree* p=(*root)->left;
	(*root)->left=p->right;
	if(p->right)p->right->parent=(*root);
	p->right=(*root);
	(*root)->parent=p;
	(*root)=p;
}
//调整树节点，使得树始终保持红黑树的性质
void adjustTree(Tree** root,Tree** node)
{
	Tree* h=(*node),*parent=NULL,*q=NULL;
	int k,temp=0;
	while(!h->color&&!h->parent->color)
	{
		parent=h->parent->parent;
		q=parent->parent;
		k=q?(q->left==parent?0:1):-1;
		if(h->parent==parent->right)
		{
			if(!(parent->left&&!parent->left->color))
			{
				if(h==h->parent->left)
				{
					rightRotation(&(parent->right));
					parent->right->parent=parent;
					leftRotation(&parent);
				}
				else leftRotation(&parent);
				parent->color=BLACK;
				parent->left->color=RED;
				parent->right->color=RED;
				temp=1;
			}
		}
		else
		{
			if(!(parent->right&&!parent->right->color))
			{
				if(h==h->parent->right)
				{
					leftRotation(&(parent->left));
					parent->left->parent=parent;
					rightRotation(&parent);
				}
				else rightRotation(&parent);
				parent->color=BLACK;
				parent->left->color=RED;
				parent->right->color=RED;
				temp=1;
			}
		}
		if(temp)
		{
			if(k==-1)
			{
				(*root)=parent;
				(*root)->parent=NULL;
			}
			else
			{
				if(!k)q->left=parent;
				else q->right=parent;
				parent->parent=q;
			}
			break;
		}
		parent->right->color=BLACK;
		parent->left->color=BLACK;
		if(parent!=(*root))parent->color=RED;
		h=parent;
	}
}
//红黑树的节点插入算法
void insertNode(Tree** root,dataType val)
{
	Tree* node=(*root),*p=NULL,*q,*top=NULL,*h=NULL,*parent=NULL,*pre=NULL;
	int k;
	createNode(&p,val);
	if(!(*root))
	{
		(*root)=p;
		(*root)->color=BLACK;
		return;
	}
	while(node)
	{
		if(node->val==val)exit(0);
		q=node;
		node=val<node->val?node->left:node->right;
	}
	if(p->val<q->val)q->left=p;
	else q->right=p;
	p->parent=q;
	if(!q->color)
	{
		top=q->parent->parent;
		k=!top?-1:(q->parent==top->left?0:1);
		pre=q->parent;
		if(q==q->parent->left)
		{
			if(q->parent->right&&q->parent->right->color==RED)
			{
				q->color=BLACK;
				q->parent->right->color=BLACK;
				h=q->parent;
				if(q->parent!=(*root))q->parent->color=RED;
				adjustTree(&(*root),&h);
			}
			else
			{
				if(p==q->left)rightRotation(&pre);
				else
				{
					leftRotation(&(pre->left));
					pre->left->parent=pre;
					rightRotation(&pre);

				}
				pre->color=BLACK;
				pre->right->color=RED;
				pre->left->color=RED;
			}
		}
		else
		{
			if(q->parent->left&&q->parent->left->color==RED)
			{
				q->color=BLACK;
				q->parent->left->color=BLACK;
				if(q->parent!=(*root))q->parent->color=RED;
				adjustTree(&(*root),&pre);
			}
			else
			{
				if(p==q->right)leftRotation(&pre);
				else
				{
					rightRotation(&(pre->right));
					pre->right->parent=pre;
					leftRotation(&pre);

				}
				pre->color=BLACK;
				pre->left->color=RED;
				pre->right->color=RED;
			}
		}
		if(k==-1)
		{
			(*root)=pre;
			(*root)->parent=NULL;
		}
		else
		{
			if(!k)top->left=pre;
			else top->right=pre;
			pre->parent=top;
		}
	}
}
//查找指定键值的节点
void searchNode(Tree* root,Tree** node,dataType val)
{
	Tree* p=root;
	while(p&&p->val!=val)
	{
		p=p->val>val?p->left:p->right;
	}
	(*node) = p;
}
//获取键值最小的节点
void getMinNode(Tree* root,Tree** node)
{
	Tree* p=root;
	while(p->left)p=p->left;
	(*node) = p;
}
//左调整
UINT leftAdjust(Tree** root)
{
	int temp;
	if((*root)->right->right&&!(*root)->right->right->color)
	{
		temp=(*root)->color;
		(*root)->color=(*root)->right->color;
		(*root)->right->color=temp;
		leftRotation(&(*root));
		(*root)->left->color=BLACK;
		(*root)->right->color=BLACK;
		return 1;
	}
	else if((*root)->right->left&&!(*root)->right->left->color)
	{
		rightRotation(&((*root)->right));
		temp=(*root)->color;
		(*root)->color=(*root)->right->color;
		(*root)->right->color=temp;
		leftRotation(&(*root));
		(*root)->left->color=BLACK;
		(*root)->right->color=BLACK;
		return 1;
	}
	else
	{
		if(!(*root)->color)
		{
			(*root)->right->color=RED;
			(*root)->color=BLACK;
			return 1;
		}
		else (*root)->right->color=RED;
	}
	return 0;
}
//右调整
UINT rightAdjust(Tree** root)
{
	int temp;
	if((*root)->left->left&&!(*root)->left->left->color)
	{
		temp=(*root)->color;
		(*root)->color=(*root)->left->color;
		(*root)->left->color=temp;
		rightRotation(&(*root));
		(*root)->left->color=BLACK;
		(*root)->right->color=BLACK;
		return 1;
	}
	else if((*root)->left->right&&!(*root)->left->right->color)
	{
		leftRotation(&((*root)->left));
		temp=(*root)->color;
		(*root)->color=(*root)->right->color;
		(*root)->left->color=temp;
		rightRotation(&(*root));
		(*root)->left->color=BLACK;
		(*root)->right->color=BLACK;
		return 1;
	}
	else
	{
		if(!(*root)->color)
		{
			(*root)->left->color=RED;
			(*root)->color=BLACK;
			return 1;
		}
		else (*root)->left->color=RED;
	}
	return 0;
}
/*
旋转指定节点后，返回的节点已替换至其他节点，需要将当前节点更新父节点 
&parent->left or &parent->right;current->parent=parent->left:right;
 */
void adjustNode(Tree** root,Tree* treeNode)
{
	Tree* node=treeNode,*p=NULL,*q=NULL;
	int k;
	while(node->parent)
	{
		p=node->parent;
		q=p->parent;
		k=q?(p==q->left?0:1):-1;
		q=p->parent;
		if(node==p->left)
		{
			if(p->right->color)
			{
				if(leftAdjust(k==-1?&(*root):(!k?&(q->left):&(q->right))))
				{
					if(!k)q->left->parent=q;
					else if(k==1)q->right->parent=q;
					break;
				}
			}
			else
			{
				p->right->color=BLACK;
				p->color=RED;
				leftRotation(k==-1?&(*root):(!k?&(q->left):&(q->right)));
				if(!k)q->left->parent=q;
				else if(k==1)q->right->parent=q;
				if(leftAdjust(k==-1?&((*root)->left):(!k?&(q->left->left):&(q->right->left))))
				{
					if(!k)q->left->left->parent=q->left;
					else if(k==1)q->right->left->parent=q->right;
					break;
				}
			}
		}
		else
		{
			if(p->left->color)
			{
				if(rightAdjust(k==-1?&(*root):(!k?&(q->left):&(q->right))))
				{
					if(!k)q->left->parent=q;
					else if(k==1)q->right->parent=q;
					break;
				}
			}
			else
			{
				p->left->color=BLACK;
				p->color=RED;
				//分支q->left已经改变,q->left->parent是原来的值,需要重新更新为:q->left->parent=q;
				rightRotation(k==-1?&(*root):(!k?&(q->left):&(q->right)));
				if(!k)q->left->parent=q;
				else if(k==1)q->right->parent=q;
				if(rightAdjust(k==-1?&((*root)->right):(!k?&(q->left->right):&(q->right->right))))
				{
					if(!k)q->left->right->parent=q->left;
					else if(k==1)q->right->right->parent=q->right;
					break;
				}
			}
		}
		node=p;
	}	
}
//删除算法实现
void deleteNode(Tree** root,dataType val)
{
	Tree* node=NULL,*p=NULL;
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
		if(node->color==BLACK)adjustNode(&(*root),node);
		if(node==node->parent->left)node->parent->left=NULL;
		else node->parent->right=NULL;
	} 
	else if(node->left&&!node->right)
	{
		if(node==(*root))
		{
			(*root)=(*root)->left;
			(*root)->parent=NULL;
			(*root)->color=BLACK;
			return;
		}
		node->left->color=BLACK;
		if(node==node->parent->left)node->parent->left=node->left;
		else node->parent->right=node->left;
		node->left->parent=node->parent;
	} 
	else if(!node->left&&node->right)
	{
		if(node==(*root))
		{
			(*root)=(*root)->right;
			(*root)->parent=NULL;
			(*root)->color=BLACK;
			return;
		}
		node->right->color=BLACK;
		if(node==node->parent->left)node->parent->left=node->right;
		else node->parent->right=node->right;
		node->right->parent=node->parent;
	} 
	else 
	{
		getMinNode(*root,&p);
		temp=p->val;
		p->val=node->val;
		node->val=temp;
		if(p->right)
		{
			//p一定是黑色节点
			p->right->color=BLACK;
			if(p==p->parent->left)p->parent->left=p->right;
			else p->parent->right=p->right;
			p->right->parent=p->parent;
		}
		else
		{
			//可能是黑色节点，也可能是红色节点
			if(p->color)adjustNode(&(*root),p);
			if(p==p->parent->left)p->parent->left=NULL;
			else p->parent->right=NULL;
		}
	}
}
//前序遍历
void pre_Order(Tree* root)
{
	if(!root)return;
	printf("%d ",root->val);
	pre_Order(root->left);
	pre_Order(root->right);

}
void preOrder(Tree* root)
{
	if(!root)return;
	printf("%s ",!root->color?"红":"黑");
	preOrder(root->left);
	preOrder(root->right);

}
//销毁红黑树
void destoryTree(Tree** root)
{
	if(*root)
	{
		Tree* left = (*root)->left;
		Tree* right = (*root)->right;
		free(*root);
		*root=NULL;
		destoryTree(&left);
		destoryTree(&right);
	}
}
int main()
{
	//int arr[]={0,1,2,3,4,5,6,7,8,9,10,11,12};
	dataType arr[]={6,9,1,0,3,4,12,2,7,11,10,5,8};
	UINT len=sizeof(arr)/sizeof(int),i=0;
	struct RedBlackTree* root=NULL;
	printf("初始化序列构造红黑树:\n");
	for(;i<len;i++)
	{
		insertNode(&root,arr[i]);
	}
	for(i=0;i<len;i++)
	{
		printf("%d ",arr[i]);
	}
	printf("\n");
	printf("前序遍历:\n");
	pre_Order(root);
	printf("\n");
	printf("删除节点:2\n");
	deleteNode(&root,2);
	printf("前序遍历:\n");
	pre_Order(root);
	printf("\n");
	printf("删除节点:0\n");
	deleteNode(&root,0);
	printf("前序遍历:\n");
	pre_Order(root);
	printf("\n");
	printf("删除节点:5\n");
	deleteNode(&root,5);
	printf("前序遍历:\n");
	pre_Order(root);
	printf("\n");
	printf("删除节点:1\n");
	deleteNode(&root,1);
	printf("前序遍历:\n");
	pre_Order(root);
	printf("\n");
	/*
	preOrder(root);
	printf("\n");
	*/
	destoryTree(&root);
	return 0;
}
