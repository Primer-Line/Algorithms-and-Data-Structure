#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef int dataType;
/*
�����
1.������Ĳ����㷨ʵ��
2.�������ɾ���㷨ʵ��
3.���ٺ����
*/
//ö�ٶ��������ڵ���ɫ
enum COLOR
{
	RED=0,
	BLACK=1
};
//���������ʽ�洢ʵ��
typedef struct RedBlackTree
{
	int val;//��ֵ
	int color;//��ɫ
	struct RedBlackTree* left;//��ڵ�ָ��
	struct RedBlackTree* right;//�ҽڵ�ָ��
	struct RedBlackTree* parent;//���ڵ�ָ��
}Tree;
//�����ڵ�ָ��
void createNode(struct RedBlackTree** node,int val)
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
//����ת
void leftRotation(Tree** root)
{
	Tree* p=(*root)->right;
	(*root)->right=p->left;
	if(p->left)p->left->parent=(*root);
	p->left=(*root);
	(*root)->parent=p;
	(*root)=p;
}
//����ת
void rightRotation(Tree** root)
{
	Tree* p=(*root)->left;
	(*root)->left=p->right;
	if(p->right)p->right->parent=(*root);
	p->right=(*root);
	(*root)->parent=p;
	(*root)=p;
}
//�������ڵ㣬ʹ����ʼ�ձ��ֺ����������
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
//������Ľڵ�����㷨
void insertNode(Tree** root,int val)
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
//����ָ����ֵ�Ľڵ�
void searchNode(Tree* root,Tree** node,int val)
{
	Tree* p=root;
	while(p&&p->val!=val)
	{
		p=p->val>val?p->left:p->right;
	}
	(*node) = p;
}
//��ȡ��ֵ��С�Ľڵ�
void getMinNode(Tree* root,Tree** node)
{
	Tree* p=root;
	while(p->left)p=p->left;
	(*node) = p;
}
//�����
int leftAdjust(Tree** root)
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
//�ҵ���
int rightAdjust(Tree** root)
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
��תָ���ڵ�󣬷��صĽڵ����滻�������ڵ㣬��Ҫ����ǰ�ڵ���¸��ڵ� 
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
				//��֧q->left�Ѿ��ı�,q->left->parent��ԭ����ֵ,��Ҫ���¸���Ϊ:q->left->parent=q;
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
//ɾ���㷨ʵ��
void deleteNode(Tree** root,int val)
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
			//pһ���Ǻ�ɫ�ڵ�
			p->right->color=BLACK;
			if(p==p->parent->left)p->parent->left=p->right;
			else p->parent->right=p->right;
			p->right->parent=p->parent;
		}
		else
		{
			//�����Ǻ�ɫ�ڵ㣬Ҳ�����Ǻ�ɫ�ڵ�
			if(p->color)adjustNode(&(*root),p);
			if(p==p->parent->left)p->parent->left=NULL;
			else p->parent->right=NULL;
		}
	}
}
//ǰ�����
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
	printf("%s ",!root->color?"��":"��");
	preOrder(root->left);
	preOrder(root->right);

}
//���ٺ����
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
	int arr[]={6,9,1,0,3,4,12,2,7,11,10,5,8};
	int len=sizeof(arr)/sizeof(int),i=0;
	struct RedBlackTree* root=NULL;
	printf("��ʼ�����й�������:\n");
	for(;i<len;i++)
	{
		insertNode(&root,arr[i]);
	}
	for(i=0;i<len;i++)
	{
		printf("%d ",arr[i]);
	}
	printf("\n");
	printf("ǰ�����:\n");
	pre_Order(root);
	printf("\n");
	printf("ɾ���ڵ�:2\n");
	deleteNode(&root,2);
	printf("ǰ�����:\n");
	pre_Order(root);
	printf("\n");
	printf("ɾ���ڵ�:0\n");
	deleteNode(&root,0);
	printf("ǰ�����:\n");
	pre_Order(root);
	printf("\n");
	printf("ɾ���ڵ�:5\n");
	deleteNode(&root,5);
	printf("ǰ�����:\n");
	pre_Order(root);
	printf("\n");
	printf("ɾ���ڵ�:1\n");
	deleteNode(&root,1);
	printf("ǰ�����:\n");
	pre_Order(root);
	printf("\n");
	/*
	preOrder(root);
	printf("\n");
	*/
	destoryTree(&root);
	return 0;
}