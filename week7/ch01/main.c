#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define Infinity 9999999

typedef int ElementType;
typedef struct TreapNode;
typedef struct TreapNode *Position;
static Position NullNode=NULL;

typedef struct TreapNode *TreapTree;
struct TreapNode
{
	ElementType Element;
	Position Left;
	Position Right;
	int Priority;
};

void FatalError(char *s)
{
	printf("%s",s);
}

TreapTree Initialize(void)
{
	if(NullNode==NULL)
	{
		NullNode=malloc(sizeof(struct TreapNode));
		if(NullNode==NULL)
			FatalError("Out of space!!!");
		NullNode->Left=NullNode->Right=NullNode;
		NullNode->Priority=Infinity;
	}
	return NullNode;
}

TreapTree SingleRotateWithRight(TreapTree T)
{
	Position Tmp;
	Tmp=T->Right;
	T->Right=Tmp->Left;
	Tmp->Left=T;
	T=Tmp;

	return T;
}

TreapTree SingleRotateWithLeft(TreapTree T)
{
	Position Tmp;
	Tmp=T->Left;
	T->Left=Tmp->Right;
	Tmp->Right=T;
	T=Tmp;

	return T;
}

TreapTree Insert(ElementType Item,TreapTree T)
{
	if(T==NullNode)
	{
		//create and return a one-node tree
		T=malloc(sizeof(struct TreapNode));
		if(T==NULL)
			FatalError("Out of space!!!");
		else
		{
			T->Element=Item;
			srand((unsigned)time(NULL));
			T->Priority=rand()%5+1;
			T->Left=T->Right=NullNode;
		}
	}
	else if(Item<T->Element)
	{
		T->Left=Insert(Item,T->Left);
		if(T->Left->Priority<T->Priority)
			T=SingleRotateWithLeft(T);
	}
	else if(Item>T->Element)
	{
		T->Right=Insert(Item,T->Right);
		if(T->Right->Priority<T->Priority)
			T=SingleRotateWithRight(T);
	}

	//otherwise it's a duplicate; do nothing
	return T;
}

TreapTree Remove(ElementType Item,TreapTree T)
{
	if(T!=NullNode)
	{
		if(Item<T->Element)
			T->Left=Remove(Item,T->Left);
		else if(Item>T->Element)
			T->Right=Remove(Item,T->Right);
		else
		{
			//match found
			if(T->Left->Priority<T->Right->Priority)
				T=SingleRotateWithLeft(T);
			else
				T=SingleRotateWithRight(T);

			if(T!=NullNode)	//continue on down
				T=Remove(Item,T);
			else
			{
				//at a leaf
				free(T->Left);
				T->Left=NullNode;
			}
		}
	}
	return T;
}

void print(TreapTree T)
{
	if(T!=NULL)
	{
		if(T->Left!=NullNode)
			print(T->Left);
//		printf("%d ,%d\n",T->Element,T->Priority);
		printf("%d ",T->Element);
		if(T->Right!=NullNode)
			print(T->Right);
	}
}

int main()
{
	int i;
	TreapTree T=Initialize();
	int Array[]={23,65,26,63,49,58,20,29,17,6};

	for(i=0;i<10;i++)
		T=Insert(Array[i],T);

	print(T);
	return 0;
}
