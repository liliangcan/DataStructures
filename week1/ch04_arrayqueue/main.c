/******************.h文件部分*******************/

typedef int ElementType;
struct QueueRecord;
typedef struct QueueRecord *Queue;

#ifdef _Queue_h

int IsEmpty(Queue Q);
Int IsFull(Queue Q);
Queue CreateQueue(int MaxElements);
void DisposeQueue(Queue Q);
void MakeEmpty(Queue Q);
void Enqueue(ElementType X,Queue Q);
ElementType Front(Queue Q);
void Dequeue(Queue Q);
ElementType FrontAndDequeue(Queue Q);
void Traverse(Queue Q);

#endif  /* _Queue_h */

#define MinQueueSize 5

struct QueueRecord
{
	int Capacity;
	int Front;
	int Rear;
	int Size;
	ElementType Array[MinQueueSize];
};

void Error(char *s)
{
    printf("%s\n",s);
  
}

void DisposeQueue(Queue Q)
{
	if(Q!=NULL)
	{
		free(Q->Array);
		free(Q);
	}
}

int IsEmpty(Queue Q)
{
	return Q->Size == 0;
}

int IsFull(Queue Q)
{
	return (Q->Rear+2)%(Q->Capacity) == Q->Front;
}

void MakeEmpty(Queue Q)
{
	Q->Size=0;
	Q->Front=1;
	Q->Rear=0;
}

Queue CreateQueue(int MaxElements)
{
	Queue Q=(Queue)malloc(sizeof(struct QueueRecord));
	if(!Q)
	{
		printf("out of space!!!");
		return NULL;
	}
	Q->Capacity=MaxElements;
	MakeEmpty(Q);
	return Q;
}

static int Succ(int value,Queue Q)
{
	if(++value == Q->Capacity)
		value=0;
	return value;
}

void Enqueue(ElementType X,Queue Q)
{
	if(IsFull(Q))
		Error("Full queue");
	else
	{
		Q->Size++;
		Q->Rear=Succ(Q->Rear,Q);
		Q->Array[Q->Rear]=X;
	}
}

void Dequeue(Queue Q)
{
	Q->Front++;
	Q->Size--;
}

ElementType Front(Queue Q)
{
	return Q->Array[Q->Front];
}

ElementType FrontAndDequeue(Queue Q)
{
	ElementType element;
	element=Q->Array[Q->Front];
	Q->Front++;
	Q->Size--;
	return element;
}

void Traverse(Queue Q)
{
	int i,index;
	if(IsEmpty(Q))
	{
		printf("Empty queue!\n");
		return;
	}
	index=Q->Front;
	for(i=0;i<Q->Size;i++)
	{
		printf("%d ",Q->Array[index]);
		index=Succ(index,Q);
	}
	printf("\n");
}

/******************.c文件部分*******************/

#include<stdio.h>
#include<stdlib.h>
#include"Queue.h"

int main()
{
	int i,element;
	Queue Q=CreateQueue(6);
	for(i=1;i<=MinQueueSize;i++)
	{
		Enqueue(i*i,Q);
	}
	Traverse(Q);
	Enqueue(44,Q);
	printf("加入数44后：");
	Traverse(Q);

	Dequeue(Q);
	printf("第一个数出队后：");
	Traverse(Q);

	element=FrontAndDequeue(Q);
	printf("出来第一个数%d后,剩下队列为：",element);
	Traverse(Q);

	MakeEmpty(Q);
	Traverse(Q);

//	DisposeQueue(Q);

	return 0;
}
