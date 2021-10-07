/*****************.h文件部分*******************/

typedef int ElementType;
struct TreeNode;
typedef struct TreeNode *Position;
typedef struct TreeNode *SearchTree;

#ifdef _SearchTree_H

SearchTree MakeEmpty(SearchTree T);                      //置空
Position Find(ElementType X,SearchTree T);				//按数值查找返回位置
Position FindMin(SearchTree T);								//查找最小值
Position FindMax(SearchTree T);						//查找最大值
SearchTree Insert(ElementType X,SearchTree T);			//插入
SearchTree Delete(ElementType X,SearchTree T);			//删除
ElementType Retrieve(Position P);                      //取出当前节点的数
void PrintTree(SearchTree T);                          //中序遍历

#endif  /* _SearchTree_H */

struct TreeNode
{
	ElementType Element;
	SearchTree Left;
	SearchTree Right;
};

void FatalError(char *s)
{
    printf("%s\n",s);
}

void Error(char *s)
{
    printf("%s\n",s);
}

SearchTree MakeEmpty(SearchTree T)
{
	if(T != NULL)
	{
		MakeEmpty(T->Left);
		MakeEmpty(T->Right);
		free(T);
	}
//	T=malloc(sizeof(struct TreeNode));
//	T->Left=NULL;
//	T->Right=NULL;
	printf("make empty calls\n");
	return NULL;
}

Position Find(ElementType X,SearchTree T)
{
	if(T == NULL)
//		Error("Empty tree!\n");
		return NULL;
	if(X < T->Element)
		return Find(X,T->Left);
	else if(X > T->Element)
		return Find(X,T->Right);
	else
		return T;
}

Position FindMin(SearchTree T)
{
	if(T == NULL)
		return NULL;
	else if(T->Left == NULL)
		return T;
	else
		return FindMin(T->Left);
}

Position FindMax(SearchTree T)
{
	if(T!=NULL)
		while(T->Right != NULL)
			T=T->Right;
	return T;
}

SearchTree Insert(ElementType X,SearchTree T)
{
	printf("insert calls first\n");

	if(T==NULL)
	{
		T=malloc(sizeof(struct TreeNode));
		if(T==NULL)
			FatalError("Out of space!!!");
		else
		{
			printf("when null,insert calls\n");

			T->Element=X;
			T->Left=T->Right=NULL;
		}
	}
	else if(X < T->Element)
	{
		printf("when not null,and smaller,insert calls\n");
		T->Left=Insert(X,T->Left);
	}
	else if(X > T->Element)
	{
		printf("when not null,and bigger,insert calls\n");
		T->Right=Insert(X,T->Right);
	}
	printf("insert calls finally\n");

	return T;
}

SearchTree Delete(ElementType X,SearchTree T)
{
	Position TmpCell;

	if(T==NULL)
		Error("Element not found!");
	else if(X < T->Element)
		T->Left=Delete(X,T->Left);
	else if(X > T->Element)
		T->Right=Delete(X,T->Right);
	else if(T->Left && T->Right)
	{
		TmpCell=FindMin(T->Right);
		T->Element=TmpCell->Element;
		T->Right=Delete(T->Element,T->Right);
	}
	else
	{
		TmpCell=T;
		if(T->Left==NULL)
			T=T->Right;
		else if(T->Right==NULL)
			T=T->Left;
		free(TmpCell);
	}

	return T;
}

ElementType Retrieve(Position P)
{
	if(P != NULL)
		return P->Element;
	else
		return 0;
}

void PrintTree(SearchTree T)
{
	if(T !=NULL)
	{
		PrintTree(T->Left);
		printf("%d ",Retrieve(T));
		PrintTree(T->Right);
	}
  else
		printf("empty tree!!\n");
//	printf("\n");
}

/*****************.c文件部分*******************/

#include<stdio.h>
#include<stdlib.h>
#include"SearchTree.h"

int main()
{
	int i,elemnet;
	Position P;
	SearchTree T=NULL;

	for(i=1;i<4;i++)
		T=Insert(i,T);

	printf("遍历一次后输出为：");
	PrintTree(T);
	printf("\n");

	P=Find(2,T);
	elemnet=Retrieve(P);
	printf("根据找到的2的位置，取出数据为：%d\n",elemnet);

	T=Insert(99,T);
	P=FindMax(T);
	elemnet=Retrieve(P);
	printf("根据找到的最大值的位置，取出数据为：%d\n",elemnet);

	T=Delete(99,T);
	P=FindMax(T);
	elemnet=Retrieve(P);
	printf("删除99后根据找到的最大值的位置，再取出数据为：%d\n",elemnet);

	T=MakeEmpty(T);
	P=Find(2,T);
	elemnet=Retrieve(P);
	printf("置空树后根据找到的2的位置，再取出数据为：%d\n",elemnet);
  
  PrintTree(T);
	return 0;
}
