/**************.c文件****************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include"BinQueue.h"

#define Capacity 500
#define MaxTrees 10
#define Infinity 999999

struct BinNode;
struct Collection;
typedef int ElementType;
typedef struct BinNode *BinTree;
typedef struct BinNode *Position;
typedef struct Collection *BinQueue;

struct BinNode
{
	ElementType Element;
	Position LeftChild;
	Position NextSibling;
};

struct Collection
{
	int CurrentSize;
	BinTree TheTree[MaxTrees];
};

void FatalError(char *s)
{
    printf("%s\n",s);
}

void Error(char *s)
{
    printf("%s\n",s);
}

int IsEmpty(BinQueue H)
{
	if(!H->CurrentSize)
		return 1;
	else
		return 0;
}

BinQueue Initialize(void)
{
	int i;
	BinQueue H;
	H=(BinQueue)malloc(sizeof(struct Collection));
	if(H==NULL)
		FatalError("Out of space!!!");

	H->CurrentSize=0;
//	H->TheTree=(BinTree*)malloc(sizeof(BinTree)*MaxTrees);
	
	for(i=0;i<MaxTrees;i++)
		H->TheTree[i]=NULL;                 //加上后，之后循环时可运行了
	
	printf("initialize calls\n");
	return H;
}

/* return the result of merging equal-sized T1 and T2 */
BinTree CombineTrees(BinTree T1,BinTree T2)
{
	if(T1->Element > T2->Element)
		return CombineTrees(T2,T1);
	T2->NextSibling=T1->LeftChild;
	T1->LeftChild=T2;

	printf("combinetrees calls\n");
	return T1;
}

/* merge two binomial queues */
/* not optimized for early termination */
/* H1 contains merged result */
BinQueue Merge(BinQueue H1,BinQueue H2)
{
	BinTree T1,T2,Carry=NULL;
	int i,j;

	if(H1->CurrentSize+H2->CurrentSize > Capacity)
		Error("Merge would exceed capacity");

	H1->CurrentSize += H2->CurrentSize;

	printf("merge calls\n");
	printf("%d\n",H1->CurrentSize);

//	printf("%d ",Carry->Element);
	if(Carry!=NULL)
		printf("carry is not empty\n");

	for(i=0,j=1;j<=H1->CurrentSize;i++,j*=2)
	{
		T1=H1->TheTree[i];
		T2=H2->TheTree[i];

		if(Carry!=NULL)
		{
			printf("carry的值为：%d ",Carry->Element);
			printf("carry is not empty\n");
		}
		if(T1!=NULL)
		{
			printf("T1的值为：%d ",T1->Element);
			printf("T1 is not empty\n");                  //为什么会显示不为空（已解决）
		}
		if(T2!=NULL)
		{
			printf("T2的值为：%d ",T2->Element);
			printf("T2 is not empty\n");
		}

		switch(!!T1 + 2*!!T2 + 4*!!Carry)
		{
		case 0:			/* no trees */
			printf("case 0 calls\n");
			break;
		case 1:			/* only H1 */
			break;
		case 2:			/* only H2 */
			H1->TheTree[i]=T2;
			H2->TheTree[i]=NULL;
			break;
		case 4:			/* only Carry */
			H1->TheTree[i]=Carry;
			Carry=NULL;

			printf("case 4 calls\n");

			break;
		case 3:			/* H1 and H2 */
			Carry=CombineTrees(T1,T2);                    //此处可运行
			H1->TheTree[i]=H2->TheTree[i]=NULL;
			break;
		case 5:			/* H1 and Carry */
			Carry=CombineTrees(T1,Carry);
			H1->TheTree[i]=NULL;
			break;
		case 6:			/* H2 and Carry */
			Carry=CombineTrees(T2,Carry);
			H2->TheTree[i]=NULL;
			break;
		case 7:			/* all trees */
			H1->TheTree[i]=Carry;
			Carry=CombineTrees(T1,T2);
			H2->TheTree[i]=NULL;
			break;
		}
//		printf("merge calls\n");
	}
	printf("merge calls\n");
	return H1;
}

ElementType DeleteMin(BinQueue H)
{
	int i,j;
	int MinTree;	/* the tree with the minimum item */
	BinQueue DeletedQueue;
	Position DeletedTree,OldRoot;
	ElementType MinItem;

	if(IsEmpty(H))
	{
		Error("empty binomial queue");
		return -Infinity;
	}

	MinItem=Infinity;
	for(i=0;i<MaxTrees;i++)
	{
		if(H->TheTree[i] &&	H->TheTree[i]->Element<MinItem)
		{
			/* update minimum */
			MinItem=H->TheTree[i]->Element;
			MinTree=i;
		}
	}

	DeletedTree=H->TheTree[MinTree];
	OldRoot=DeletedTree;
	DeletedTree=DeletedTree->LeftChild;
	free(OldRoot);
	
	DeletedQueue=Initialize();
	DeletedQueue->CurrentSize=(1<<MinTree)-1;
	for(j=MinTree-1;j>=0;j--)
	{
		DeletedQueue->TheTree[j]=DeletedTree;
		DeletedTree=DeletedTree->NextSibling;
		DeletedQueue->TheTree[j]->NextSibling=NULL;
	}

	H->TheTree[MinTree]=NULL;
	H->CurrentSize -= DeletedQueue->CurrentSize+1;

	Merge(H,DeletedQueue);
	return MinItem;
}

static BinQueue ProduSingle(ElementType X)
{
	BinQueue H;
	BinTree T=malloc(sizeof(struct BinNode));
	H=Initialize();
	H->CurrentSize+=1;
	T->Element=X;
	T->LeftChild=T->NextSibling=NULL;
	H->TheTree[0]=T;

	printf("ProduSingle calls\n");

	return H;
}

BinQueue Insert(ElementType X,BinQueue H)
{
	BinQueue H1;
	H1=ProduSingle(X);
	printf("%d\n",H1->CurrentSize);

	if(H->CurrentSize==0)
		H=H1;
	else
		H=Merge(H1,H);
	printf("%d\n",H->CurrentSize);
	printf("Merge calls\n");
	printf("insert calls\n");
	return H;
}

static void PrintTree(BinTree T)
{
//	printf("PrintTree calls\n");
	if(T!=NULL)
	{
//		printf("T is not NULL\n");
		printf("%d ",T->Element);
		PrintTree(T->LeftChild);
		PrintTree(T->NextSibling);
	}
//	else
//		printf("this position is empty\n");
//	printf("PrintTree calls\n");
}

void Print(BinQueue H)
{
	int i,j;
	for(i=0,j=1;j<H->CurrentSize;i++,j*=2)
		PrintTree(H->TheTree[i]);

	printf("Print calls\n");
}

int main()
{
	int i;
	ElementType minimum;
	BinQueue H;
	H=Initialize();

	srand((unsigned int)time(NULL));
	for(i=0;i<15;i++)
		H=Insert(rand()%100+1,H);

	printf("\nstart print all:\n");
	Print(H);
	printf("高度为2的（即i=2）的树遍历为：");
	PrintTree(H->TheTree[2]);
	printf("\n");

	minimum=DeleteMin(H);
	printf("\n删除最小值后，start print all:\n");
	Print(H);

	return 0;
}
