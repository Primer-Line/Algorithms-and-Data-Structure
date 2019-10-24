#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define MAX_LEN 20 //最大单词长度
typedef unsigned int UINT;
typedef void* elemType;
typedef int dataType;
//字典树的存储结构
typedef struct TreeNode
{
	char character;
	UINT tag;//结束符 1表示结束
	struct TreeNode* node[26];//26个孩子节点
}Node;//根节点
//插入字符
void addCharacter(Node** root,char c)//返回字符所在的孩子节点
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
	while(*s)addCharacter(&p,*s++);//依次插入字符
	p->tag = 1;//结束符
}
//查找指定字符串 成功返回1 失败返回0
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
//查找单词
void searchWords(Node* root,char* str,UINT index)
{
	UINT i;
	for(i=0;i<26;i++)
	{
		if(root->node[i])
		{
			str[index] = root->node[i]->character;//字符拼接
			if(root->node[i]->tag)
			{
				str[index+1] = '\0';//结束符
				printf("%s\n",str);
			}
			searchWords(root->node[i],str,index+1);
		}
	}
}
//显示所有以指定字符串为前缀的字符串
void showWordsWithPrefix(Node* root,char* str)
{
	Node* p=root;
	UINT index;
	char s[MAX_LEN];
	strcpy(s,str);//复制前缀
	while(*str)
	{
		index = (int)*str++ - 97;
		if(!p->node[index])return;//不符合则退出
		p=p->node[index];
	}
	searchWords(p,s,strlen(s));//查找后缀
}
//显示所有字符串
void showAllWords(Node* root)
{
	char str[MAX_LEN];
	searchWords(root,str,0);
}
//删除指定字符串 成功返回1 失败返回0
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
		p->tag = 0;//结束符置为0 表示被删除
		return 1;
	}
	return 0;
}
//查找是否存在后缀 存在返回1 不存在返回0 目的是防止重复计算已经被删除的字符串
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
//查找是否存在指定前缀的字符串 存在返回1 不存在返回0
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
//销毁字典树
void destory(Node** root)
{
	UINT i;
	Node* p[26];
	if(!*root)return;
	for(i=0;i<26;i++)p[i] = (*root)->node[i];
	free(*root);
	*root = NULL;
	for(i=0;i<26;i++)destory(&p[i]);
}
int main()
{
	Node* root=(struct TreeNode* )malloc(sizeof(struct TreeNode));
	char* arr[]={"add","delete","deep","up","update","search","select"};
	UINT len=sizeof(arr)/sizeof(char*),i;
	if(!root)return 0;
	memset(root->node,0x00,sizeof(root->node));
	for(i=0;i<len;i++)addStr(&root,arr[i]);//插入字符串
	showAllWords(root);//显示所有字符串
	if(!searchStr(root,"up"))printf("不存在该字符串,查找失败\n");
	else printf("查找成功\n");
	if(!deleteStr(root,"up"))printf("未知的字符串,删除失败\n");
	else printf("删除成功\n");
	if(!deleteStr(root,"update"))printf("未知的字符串,删除失败\n");
	else printf("删除成功\n");
	if(!strWithPrefix(root,"up"))printf("不存在符合的字符串\n");
	else printf("查找成功\n");
	showWordsWithPrefix(root,"de");//查找后缀
	destory(&root);//销毁字典树
	return 0;
}