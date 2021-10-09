/***************.h文件*******************/

typedef int ElementType;
struct AvlNode;
typedef struct AvlNode *Position;
typedef struct AvlNode *AvlTree;

#ifdef _AvlTree_H

AvlTree MakeEmpty(AvlTree T);
Position Find(ElementType X,AvlTree T);
Position FindMin(AvlTree T);
Position FindMax(AvlTree T);
AvlTree Insert(ElementType X,AvlTree T);
AvlTree Delete(ElemnetType X,AvlTree T);
ElementType Retrieve(Position P);
void PrintTree(AvlTree T);

#endif   /* _AvlTree_H */

struct AvlNode
{
	ElementType Element;
	AvlTree Left;
	AvlTree Right;
	int Height;
};

void FatalError(char *s)
{
    printf("%s\n",s);
}

void Error(char *s)
{
    printf("%s\n",s);
}

static Max(ElementType a,ElementType b)
{
	ElementType max;
	max=a>b?a:b;
	return max;
}

AvlTree MakeEmpty(AvlTree T)
{
	if(T != NULL)
	{
		MakeEmpty(T->Left);
		MakeEmpty(T->Right);
		free(T);
	}
	return NULL;
}

Position Find(ElementType X,AvlTree T)
{
	if(T == NULL)
		return NULL;
	if(X < T->Element)
		return Find(X,T->Left);
	else if(X > T->Element)
		return Find(X,T->Right);
	else
		return T;
}

Position FindMin(AvlTree T)
{
	if(T == NULL)
		return NULL;
	else if(T->Left == NULL)
		return T;
	else
		return FindMin(T->Left);
}

Position FindMax(AvlTree T)
{
	if(T!=NULL)
		while(T->Right != NULL)
			T=T->Right;
	return T;
}

ElementType Retrieve(Position P)
{
	if(P != NULL)
		return P->Element;
	else
		return 0;
}

static int Height(Position P)
{
	if(P==NULL)
		return -1;
	else
		return P->Height;
}

static Position SingleRotateWithRight(Position K2)
{
	Position K1;

	K1=K2->Left;
	K2->Left=K1->Right;
	K1->Right=K2;

	K2->Height=Max(Height(K2->Left),Height(K2->Right))+1;
	K1->Height=Max(Height(K1->Left),Height(K1->Right))+1;

	printf("singlerotateright calls\n");

	return K1;
}

static Position SingleRotateWithLeft(Position K2)
{
	Position K1;

	K1=K2->Right;
	K2->Right=K1->Left;
	K1->Left=K2;

	K2->Height=Max(Height(K2->Left),Height(K2->Right))+1;
	K1->Height=Max(Height(K1->Left),Height(K1->Right))+1;

	printf("singlerotateleft calls\n");

	return K1;
}

static Position DoubleRotateWithLeft(Position K3)
{
	printf("doublerotateleft calls\n");

	K3->Right=SingleRotateWithRight(K3->Right);
//	K3=SingleRotateWithLeft(K3);
	return SingleRotateWithLeft(K3);
}

static Position DoubleRotateWithRight(Position K3)
{
	printf("doublerotateright calls\n");

	K3->Left=SingleRotateWithLeft(K3->Left);
	
	return SingleRotateWithRight(K3);
}

AvlTree Insert(ElementType X,AvlTree T)
{
	if(T==NULL)
	{
		T=malloc(sizeof(struct AvlNode));
		if(T==NULL)
			FatalError("Out of space!!!");
		else
		{
			T->Element=X;
			T->Height=0;
			T->Left=T->Right=NULL;
		}
	}
	else if(X < T->Element)
	{
		T->Left=Insert(X,T->Left);
		if(Height(T->Left) - Height(T->Right) == 2)
		{
			if(X < T->Left->Element)
				T=SingleRotateWithRight(T);
			else
				T=DoubleRotateWithRight(T);
		}
	}
	else if(X > T->Element)
	{
		T->Right=Insert(X,T->Right);
		if(Height(T->Right) - Height(T->Left) == 2)
		{
			if(X > T->Right->Element)
				T=SingleRotateWithLeft(T);
			else
				T=DoubleRotateWithLeft(T);
		}
	}
	T->Height=Max(Height(T->Left),Height(T->Right))+1;
	return T;
}

AvlTree Delete(ElementType X,AvlTree T)
{
	Position TmpCell;

	if(T==NULL)
		Error("Element not found!");
	else if(X < T->Element)
	{
		T->Left=Delete(X,T->Left);
		T->Height=Max(Height(T->Left),Height(T->Right))+1;
	}
	else if(X > T->Element)
	{
		T->Right=Delete(X,T->Right);
		T->Height=Max(Height(T->Left),Height(T->Right))+1;
	}

	else if(T->Left && T->Right)
	{
		TmpCell=FindMin(T->Right);
		T->Element=TmpCell->Element;
		T->Right=Delete(T->Element,T->Right);
		if(Height(T->Left) - Height(T->Right) == 2)
		{
			if(Height(T->Left->Right) - Height(T->Left->Left) == 1)
				T=DoubleRotateWithRight(T);	
			else
				T=SingleRotateWithRight(T);
			T->Height--;
		}
		if(Height(T->Right->Right) - Height(T->Right->Left) == 2)
		{
			if(Height(T->Right->Right->Left) - Height(T->Right->Right->Right) == 1)
				T=DoubleRotateWithLeft(T);
			else
				T=SingleRotateWithLeft(T);
			T->Height--;
		}
		T->Height=Max(Height(T->Left),Height(T->Right))+1;
	}
	else
	{
		TmpCell=T;

		if(T->Left==NULL && T->Right==NULL)
		{
			printf("delete calls\n");
			T=NULL;
//			T->Height = -1;
			printf("delete calls\n");
		}
		else if(T->Right == NULL)
		{
			T=T->Right;
			T->Height = T->Height-1;
		}
		else if(T->Left == NULL)
		{
			T=T->Left;
			T->Height = T->Height-1;
		}
		free(TmpCell);
		
		printf("delete calls\n");
	}
	
	return T;
}

void PrintTree(AvlTree T)
{
	if(T != NULL)
	{
		PrintTree(T->Left);
		printf("%d ",Retrieve(T));
		PrintTree(T->Right);
	}
//  else
//		printf("empty tree!!\n");
}

/******************.c文件*******************/

#include<stdio.h>
#include<stdlib.h>
#include"AvlTree.h"

int main()
{
	int i,elemnet;
	Position P;
	AvlTree T=NULL;

	for(i=1;i<=15;i++)
		T=Insert(i,T);

	printf("遍历一次后输出为：");
	PrintTree(T);
	printf("\n");
	printf("目前树高度为：%d\n",Height(T));

	P=Find(2,T);
	elemnet=Retrieve(P);
	printf("根据找到的2的位置，取出数据为：%d\n",elemnet);

	T=Insert(99,T);
	T=Insert(88,T);
	T=Insert(44,T);
	printf("插入99,88,44后树高度为：%d\n",Height(T));
	printf("遍历一次后输出为：");
	PrintTree(T);
	printf("\n");

	P=FindMax(T);
	elemnet=Retrieve(P);
	printf("根据找到的最大值的位置，取出数据为：%d\n",elemnet);

	T=Delete(8,T);
	P=FindMax(T);
	elemnet=Retrieve(P);
	printf("删除目前的根节点8后根据找到的最大值的位置，再取出数据为：%d\n",elemnet);
	printf("遍历一次后输出为：");
	PrintTree(T);
	printf("\n");
/*
	T=Delete(88,T);
	P=FindMax(T);
	elemnet=Retrieve(P);
	printf("删除88后根据找到的最大值的位置，再取出数据为：%d\n",elemnet);
*/
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
