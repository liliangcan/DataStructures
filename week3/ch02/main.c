/********************.c文件**********************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include"LeftHeap.h"

struct TreeNode;
typedef struct TreeNode *PriorityQueue;
typedef int ElementType;

static PriorityQueue Merge1(PriorityQueue H1,PriorityQueue H2);

struct TreeNode
{
	ElementType Element;
	PriorityQueue Left;
	PriorityQueue Right;
	int Npl;
};

void FatalError(char *s)
{
    printf("%s\n",s);
}

PriorityQueue Initialize(void)
{
	PriorityQueue H;
	H=malloc(sizeof(struct TreeNode));
	if(H==NULL)
		FatalError("Out of space!!!");

	H->Left=H->Right=NULL;
	H->Npl=0;

	return H;
}

void Error(char *s)
{
    printf("%s\n",s);
}

int IsEmpty(PriorityQueue H)
{
	if(H->Left==NULL && H->Right==NULL && !H->Element)
		return 1;
	else
		return 0;
}

static PriorityQueue SwapChildren(PriorityQueue H)
{
	PriorityQueue TmpQueue;
	if(H==NULL)
		printf("priority queue is NULL");
	else if(H->Left || H->Right)
	{
		TmpQueue=H->Left;
		H->Left=H->Right;
		H->Right=TmpQueue;
	}
	return H;

}

PriorityQueue Merge(PriorityQueue H1,PriorityQueue H2)
{
	if(H1==NULL)
		return H2;
	if(H2==NULL)
		return H1;
	if(H1->Element<H2->Element)
		return Merge1(H1,H2);
	else
		return Merge1(H2,H1);
}

static PriorityQueue Merge1(PriorityQueue H1,PriorityQueue H2)
{
	if(H1->Left==NULL)/* single node */
		H1->Left=H2;/* H1->Right is already NULL,H1->Npl is already 0 */
	else
	{
		H1->Right=Merge(H1->Right,H2);
		if(H1->Left->Npl<H1->Right->Npl)
			SwapChildren(H1);

		H1->Npl=H1->Right->Npl+1;
	}
	return H1;
}

PriorityQueue Insert1(ElementType X,PriorityQueue H)
{
	PriorityQueue SingleNode;

	SingleNode=malloc(sizeof(struct TreeNode));
	if(SingleNode==NULL)
		FatalError("Out of space!!!");
	else
	{
		SingleNode->Element=X;
		SingleNode->Npl=0;
		SingleNode->Left=SingleNode->Right=NULL;
		H=Merge(SingleNode,H);
	}
	return H;
}

/* DeleteMin1 return the new tree */
/* To get the minimum,use FindMin */
/* This is for convenience */

PriorityQueue DeleteMin1(PriorityQueue H)
{
	PriorityQueue LeftHeap,RightHeap;

	if(IsEmpty(H))
	{
		Error("Priority queue is empty");
		return H;
	}
	LeftHeap=H->Left;
	RightHeap=H->Right;
	free(H);
	return Merge(LeftHeap,RightHeap);
}

ElementType FindMin(PriorityQueue H)
{
	return H->Element;
}

void Print(PriorityQueue H)
{
	if(H != NULL)
	{
		printf("%d ",H->Element);
		Print(H->Left);
		Print(H->Right);
	}
	else return;
}

int main()
{
	int i;
	PriorityQueue H1,H2;
	ElementType element;

//	H1=Initialize();
//	H2=Initialize();
	H1=NULL;
	H2=NULL;
	srand((unsigned int)time(NULL));
	for(i=0;i<5;i++)
	{
		H1=Insert1(rand()%100+1,H1);
		H2=Insert1(rand()%100+1,H2);
	}

	printf("H1前序遍历：");
	Print(H1);
	printf("\n");
	printf("H2前序遍历：");
	Print(H2);
	printf("\n");

	H1=Merge(H1,H2);
	printf("H1前序遍历：");
	Print(H1);
	printf("\n");

	element=FindMin(H1);
	printf("最小值为：%d\n",element);

	H1=DeleteMin1(H1);
	printf("删除最小值后，H1前序遍历：");
	Print(H1);
	printf("\n");

	return 0;
}
