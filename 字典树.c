#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define MAX_LEN 20 //��󵥴ʳ���
typedef unsigned int UINT;
typedef void* elemType;
typedef int dataType;
#include"queue.h"
//�ֵ����Ĵ洢�ṹ
typedef struct TreeNode
{
	char character;
	UINT tag;//������ 1��ʾ����
	struct TreeNode* node[26];//26�����ӽڵ�
}Node;//���ڵ�
//�����ַ�
void addCharacter(Node** root,char c)//�����ַ����ڵĺ��ӽڵ�
{
	UINT index=(UINT)c-97;
	if((*root)->node[index])
	{
		(*root) = (*root)->node[index];
		return;
	}
	(*root)->node[index] = (struct TreeNode* )malloc(sizeof(struct TreeNode));
	memset((*root)->node[index]->node,0x00,sizeof((*root)->node[index]->node));
	(*root)->node[index]->character=c;
	(*root)->node[index]->tag = 0;
	*root = (*root)->node[index];
}
void addStr(Node** root,char* str)
{
	Node* p = (*root);
	char* s = str;
	while(*s)addCharacter(&p,*s++);//���β����ַ�
	p->tag = 1;//������
}
//����ָ���ַ��� �ɹ�����1 ʧ�ܷ���0
UINT searchStr(Node* root,char* str)
{
	Node* p=root;
	UINT index;
	while(*str)
	{
		index = (int)*str++ - 97;
		if(!p->node[index])return 0;
		p=p->node[index];
	}
	if(p->tag)return 1;
	return 0;
}
//���ҵ���
void searchWords(Node* root,char* str,UINT index)
{
	UINT i;
	for(i=0;i<26;i++)
	{
		if(root->node[i])
		{
			str[index] = root->node[i]->character;//�ַ�ƴ��
			if(root->node[i]->tag)
			{
				str[index+1] = '\0';//������
				printf("%s\n",str);
			}
			searchWords(root->node[i],str,index+1);
		}
	}
}
//��ʾ������ָ���ַ���Ϊǰ׺���ַ���
void showWordsWithPrefix(Node* root,char* str)
{
	Node* p=root;
	UINT index;
	char s[MAX_LEN];
	strcpy(s,str);//����ǰ׺
	while(*str)
	{
		index = (int)*str++ - 97;
		if(!p->node[index])return;//���������˳�
		p=p->node[index];
	}
	searchWords(p,s,strlen(s));//���Һ�׺
}
//��ʾ�����ַ���
void showAllWords(Node* root)
{
	char str[MAX_LEN];
	searchWords(root,str,0);
}
//ɾ��ָ���ַ��� �ɹ�����1 ʧ�ܷ���0
UINT deleteStr(Node* root,char* str)
{
	Node* p=root;
	UINT index;
	while(*str)
	{
		index = (int)*str++ - 97;
		if(!p->node[index])return 0;
		p=p->node[index];
	}
	if(p->tag)
	{
		p->tag = 0;//��������Ϊ0 ��ʾ��ɾ��
		return 1;
	}
	return 0;
}
//�����Ƿ���ں�׺ ���ڷ���1 �����ڷ���0 Ŀ���Ƿ�ֹ�ظ������Ѿ���ɾ�����ַ���
UINT search(Node* root)
{
	UINT i,result = 0;
	for(i=0;i<26;i++)
	{
		if(root->node[i])
		{
			if(root->node[i]->tag)return 1;
			result = search(root->node[i]);
		}
	}
	return result;
}
//�����Ƿ����ָ��ǰ׺���ַ��� ���ڷ���1 �����ڷ���0
UINT strWithPrefix(Node* root,char* str)
{
	Node* p=root;
	UINT index;
	while(*str)
	{
		index = (int)*str++ - 97;
		if(!p->node[index])return 0;
		p=p->node[index];
	}
	return search(p);
}
int main()
{
	Node* root=(struct TreeNode* )malloc(sizeof(struct TreeNode));
	char* arr[]={"add","delete","deep","up","update","search","select"};
	UINT len=sizeof(arr)/sizeof(char*),i;
	if(!root)return 0;
	memset(root->node,0x00,sizeof(root->node));
	for(i=0;i<len;i++)addStr(&root,arr[i]);//�����ַ���
	showAllWords(root);//��ʾ�����ַ���
	if(!searchStr(root,"up"))printf("�����ڸ��ַ���,����ʧ��\n");
	else printf("���ҳɹ�\n");
	if(!deleteStr(root,"up"))printf("δ֪���ַ���,ɾ��ʧ��\n");
	else printf("ɾ���ɹ�\n");
	if(!deleteStr(root,"update"))printf("δ֪���ַ���,ɾ��ʧ��\n");
	else printf("ɾ���ɹ�\n");
	if(!strWithPrefix(root,"up"))printf("�����ڷ��ϵ��ַ���\n");
	else printf("���ҳɹ�\n");
	showWordsWithPrefix(root,"de");//���Һ�׺
	return 0;
}