/******************.h文件**********************/

typedef int ElementType;
struct HeapStruct;
typedef struct HeapStruct *PriorityQueue;

#ifdef _BinHeap_H

PriorityQueue Initialize(int MaxElements);
void Destroy(PriorityQueue H);
void MakeEmpty(PriorityQueue H);
void Insert(ElementType X,PriorityQueue H);
ElementType FindMin(PriorityQueue H);
ELementType DeleteMin(PriorityQueue H);
int IsEmpty(PriorityQueue H);
int IsFull(PriorityQueue H);
PriorityQueue BuildHeap(PriorityQueue H);
void PercolateDown(int CurrentNode,PriorityQueue H);
void Print(PriorityQueue H);

#endif

#define MinPQSize 5
#define MinData   0

struct HeapStruct
{
	int Capacity;
	int Size;
	ElementType *Elements;
};

void FatalError(char *s)
{
    printf("%s\n",s);
}

void Error(char *s)
{
    printf("%s\n",s);
}

int IsEmpty(PriorityQueue H)
{
	if(H->Size==0)
		return 1;
	else
		return 0;
}

int IsFull(PriorityQueue H)
{
	if(H->Size==H->Capacity)
		return 1;
	else
		return 0;
}

void Print(PriorityQueue H)
{
	int i;
	if(IsEmpty(H))
	{
		printf("priority queue is empty\n");
	}
	else
	{
	printf("遍历优先队列为：");
	for(i=1;i<=H->Size;i++)
		printf("%d ",H->Elements[i]);
	printf("\n");
	}
}

void Destroy(PriorityQueue H)
{
	if(H!=NULL)
		free(H);
	printf("destroy calls\n");
}

void MakeEmpty(PriorityQueue H)
{
	if(H->Size!=0)
		H->Size=0;
	printf("makeempty calls\n");
}

ElementType FindMin(PriorityQueue H)
{
	if(IsEmpty(H))
	{
		Error("Priority queue is full");
		return H->Elements[0];
	}
	else
		return H->Elements[1];
}

void PercolateDown(int CurrentNode,PriorityQueue H)
{
	int i,Child;
	ElementType TmpElement;

	if(H->Size<CurrentNode)
	{
		Error("this node doesn't exsit");
		return;
	}

	for(i=CurrentNode;i*2<=H->Size;i=Child)
	{
		Child=i*2;
		if(H->Elements[i]<H->Elements[Child+1] && H->Elements[i]<H->Elements[Child])
			return;
		else
		{
		/* Find smaller child */
		if(Child!=H->Size && H->Elements[Child+1]<H->Elements[Child])
			Child++;
		/* change eachother */
		TmpElement=H->Elements[i];
		H->Elements[i]=H->Elements[Child];
		H->Elements[Child]=TmpElement;
		}
	}
}

PriorityQueue BuildHeap(PriorityQueue H)
{
	int i,N;
	N=H->Size;
	for(i=N/2;i>0;i--)
		PercolateDown(i,H);
	return H;
}

PriorityQueue Initialize(int MaxElements)
{
	PriorityQueue H;

	if(MaxElements < MinPQSize)
		Error("Priority queue size is too small");

	H=malloc(sizeof(struct HeapStruct));
	if(H==NULL)
		FatalError("Out of space!!!");

	H->Elements=malloc((MaxElements+1) *sizeof(ElementType));
	if(H->Elements==NULL)
		FatalError("Out of space!!!");

	H->Capacity=MaxElements;
	H->Size=0;
	H->Elements[0]=MinData;

	return H;
}

void Insert(ElementType X,PriorityQueue H)
{
	int i;

	if(IsFull(H))
	{
		Error("Priority queue is full");
		return;
	}

	for(i=++H->Size;H->Elements[i/2]>X;i/=2)
		H->Elements[i]=H->Elements[i/2];
	H->Elements[i]=X;
}

ElementType DeleteMin(PriorityQueue H)
{
	int i,Child;
	ElementType MinElement,LastElement;

	if(IsEmpty(H))
	{
		Error("Priority queue is full");
		return H->Elements[0];
	}
	MinElement=H->Elements[1];
	LastElement=H->Elements[H->Size--];

	for(i=1;i*2<=H->Size;i=Child)
	{
		/* Find smaller child */
		Child=i*2;
		if(Child!=H->Size && H->Elements[Child+1]<H->Elements[Child])
			Child++;

		/* Percolate one level */
		if(LastElement>H->Elements[Child])
			H->Elements[i]=H->Elements[Child];
		else
			break;
	}
	H->Elements[i]=LastElement;
	return MinElement;
}

/******************.c文件***********************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include"BinHeap.h"

int main()
{
	int i;
	ElementType TmpElement;
	PriorityQueue H;
	H=Initialize(30);
	srand((unsigned int)time(NULL));
	for(i=1;i<=H->Capacity/2;i++)
	{
		H->Elements[i]=rand()%100+1;
		H->Size++;
	}
	printf("未构建堆时，");
	Print(H);

	H=BuildHeap(H);
	printf("构建堆后，");
	Print(H);
	printf("目前优先队列的大小为：%d\n",H->Size);

	printf("此时最小值为：%d\n",FindMin(H));

	TmpElement=DeleteMin(H);
	printf("删除最小值%d后，此时最小值为：%d\n",TmpElement,FindMin(H));

	Insert(55,H);
	printf("插入55后，");
	Print(H);

	MakeEmpty(H);
	Print(H);

	Destroy(H);
	return 0;
}
