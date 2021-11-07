#include<stdio.h>
#include<stdlib.h>

typedef int ElementType;
struct AANode;
typedef struct AANode *AATree;
typedef struct AANode *Position;
//return for failures
Position NullNode=NULL;

struct AANode
{
	ElementType Element;
	AATree Left;
	AATree Right;
	int Level;
};

void FatalError(char *s)
{
	printf("%s",s);
}

AATree Initialize(void)
{
	if(NullNode==NULL)
	{
		NullNode=malloc(sizeof(struct AANode));
		if(NullNode==NULL)
			FatalError("Out of space!!!");
		NullNode->Left=NullNode->Right=NullNode;
		NullNode->Level=0;
	}
	return NullNode;
}

AATree SingleRotateWithLeft(AATree T)
{
	Position Tmp;
	Tmp=T->Right;
	T->Right=Tmp->Left;
	Tmp->Left=T;
	T=Tmp;

	return T;
}

AATree SingleRotateWithRight(AATree T)
{
	Position Tmp;
	Tmp=T->Left;
	T->Left=Tmp->Right;
	Tmp->Right=T;
	T=Tmp;

	return T;
}

//if T's left child is on the same level as T,perform a rotation
AATree Skew(AATree T)
{
	if(T->Left->Level==T->Level)
		T=SingleRotateWithLeft(T);
	return T;
}

//if T's rightmost grandchild is on the same level,rotate right child up
AATree Split(AATree T)
{
	if(T->Right->Right->Level==T->Level)
	{
		T=SingleRotateWithRight(T);
		T->Level++;
	}
	return T;
}

AATree Insert(ElementType Item,AATree T)
{
	if(T==NullNode)
	{
		//create and return a one-node tree
		T=malloc(sizeof(struct AANode));
		if(T==NULL)
			FatalError("Out of space!!!");
		else
		{
			T->Element=Item;
			T->Level=1;
			T->Left=T->Right=NullNode;
		}
		return T;
	}
	else if(Item<T->Element)
		T->Left=Insert(Item,T->Left);
	else if(Item>T->Element)
		T->Right=Insert(Item,T->Right);

	//otherwise it's a duplicate;do nothing
	T=Skew(T);
	T=Split(T);
	return T;
}

AATree Remove(ElementType Item,AATree T)
{
	static Position DeletePtr,LastPtr;

	if(T!=NullNode)
	{
		//step1:search down tree
		//set lastptr and deleteptr
		LastPtr=T;
		if(Item<T->Element)
			T->Left=Remove(Item,T->Left);
		else
		{
			DeletePtr=T;
			T->Right=Remove(Item,T->Right);
		}
		//step2:if at the bottom of the tree and item is present,we remove it
		if(T==LastPtr)
		{
			if(DeletePtr!=NullNode && Item==DeletePtr->Element)
			{
				DeletePtr->Element=T->Element;
				DeletePtr=NullNode;
				T=T->Right;
				free(LastPtr);
			}
		}
		//step3:otherwise,we are not at the bottom;
		//rebalance
		else if(T->Left->Level<T->Level-1 || T->Right->Level<T->Level-1)
		{
			if(T->Right->Level > --T->Level)
				T->Right->Level=T->Level;
			T=Skew(T);
			T->Right=Skew(T->Right);
			T->Right->Right=Skew(T->Right->Right);
			T=Split(T);
			T->Right=Split(T->Right);
		}
	}
	return T;
}

void Print(AATree T)
{
	if(T!=NullNode)
	{
		Print(T->Left);
		printf("%d ",T->Element);
		Print(T->Right);
	}
}

int main()
{
	int i;
	AATree T=Initialize();

	int Array[]={10,85,15,70,20,60,30,50,65,80,90,40,5,55};

	for(i=0;i<14;i++)
		T=Insert(Array[i],T);

	Print(T);
	return 0;
}
