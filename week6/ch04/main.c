#include<stdio.h>
#include<stdlib.h>
#include"SkipList.h"

#define Infinity 9999999

typedef int ElementType;
struct SkipNode;
typedef struct SkipNode *SkipList;

struct SkipNode
{
	ElementType Element;
	SkipList Right;
	SkipList Down;
};

typedef struct SkipNode *Position;
static Position Bottom=NULL;
static Position Tail=NULL;

void FatalError(char *s)
{
	printf("%s",s);
}

SkipList Initialize(void)
{
	SkipList L;

	if(Bottom==NULL)
	{
		Bottom=malloc(sizeof(struct SkipNode));
		if(Bottom==NULL)
			FatalError("Out of space!!!");
		Bottom->Right=Bottom->Down=Bottom;

		Tail=malloc(sizeof(struct SkipNode));
		if(Tail==NULL)
			FatalError("Out of space!!!");
		Tail->Element=Infinity;
		Tail->Right=Tail;
	}

	//create the header node
	L=malloc(sizeof(struct SkipNode));
	if(L==NULL)
		FatalError("Out of space!!!");
	L->Element=Infinity;
	L->Right=Tail;
	L->Down=Bottom;

	return L;
}

//return position of node containing item,
//or bottom if not found
Position Find(ElementType Item,SkipList L)
{
	Position Current=L;

	Bottom->Element=Item;
	while(Item!=Current->Element)
		if(Item<Current->Element)
			Current=Current->Down;
		else
			Current=Current->Right;

	return Current;
}

SkipList Insert(ElementType Item,SkipList L)
{
	Position Current=L;
	Position NewNode;

	Bottom->Element=Item;
	while(Current!=Bottom)
	{
		while(Item>Current->Element)
			Current=Current->Right;

		//if gap size is 3 or at bottom level
		//and must insert,then promote the middle element
		if(Current->Element > Current->Down->Right->Right->Element)
		{
			NewNode=malloc(sizeof(struct SkipNode));
			if(NewNode==NULL)
				FatalError("Out of space!!!");
			NewNode->Right=Current->Right;
			NewNode->Down=Current->Down->Right->Right;
			Current->Right=NewNode;
			NewNode->Element=Current->Element;
			Current->Element=Current->Down->Right->Element;
		}
		else
			Current=Current->Down;
	}
	//raise height of DSL if necessary
	if(L->Right!=Tail)
	{
		NewNode=malloc(sizeof(struct SkipNode));
		if(NewNode==NULL)
			FatalError("Out of space!!!");
		NewNode->Down=L;
		NewNode->Right=Tail;
		NewNode->Element=Infinity;
		L=NewNode;
	}
	return L;
}

void FindAndModefiyRemoveHelp(ElementType Item,SkipList L,ElementType OtherItem)
{
	Position Current;

	Current=L;
	while(Current!=Bottom)
	{
		while(Item>Current->Element)
			Current=Current->Right;
		if(Item==Current->Element)
			Current->Element=OtherItem;
		Current=Current=Current->Down;
	}
}

void LowerHeadRemoveHelp(SkipList L)
{
	Position tmp;
	if(L->Down->Right==Tail)
	{
		tmp=L->Down;
		L->Down=tmp->Down;
		free(tmp);
	}
}
/*
BOOL Delete(ElementType Item,SkipList L)
{
	if(L->Down==Bottom)
	{
		printf("empty list!!!\n");
		return false;
	}
	Position previous,tmp,next;
	Position Current=L->Down;
	int VisitNum=0;
	bool CanRemove=true;
	for(;;)
	{
		previous=NULL;
		while(Item>Current->Element)
		{
			previous=Current;
			Currrent=Current->Right;
		}
		if(Item==Current->Element)
			VisitNum++;

		if(Current->Down==Bottom)
		{
			if(VisitNum==0)
			{
				LowerHeadRemoveHelp(L);
				CanRemove=false;
				return false;
			}
			else
			{
				if(VisitNum==1)
				{
					tmp=Current->Right;
					Current->Element=Current->Right->Element;
					Current->Right=tmp->Right;
					delete tmp;

					LowerHeadRemoveHelp(L);
				}
				else
				{
					LowerHeadRemoveHelp(L);
					FindAndModefiyRemoveHelp(Current->Element,previous->Element);
					previous->Right=Current->Right;
					delete Current;
				}
				return true;
			}
		}
		next=Current->Down;

		if(Current->Element==Current->Down->Right->Element)
		{
			if(previous==NULL)
			{
				if(Current->Right->Element>Current->Right->Down->Right->Element)
				{
					Current->Element=Current->Right->Down->Element;
					Current->Right->Down=Current->Right->Down->Right;
				}
				else
				{
					tmp=Current->Right;
					Current->Element=tmp->Element;
					Current->Right=tmp->Right;
					delete tmp;
				}
			}
			else
			{
				if(previous->Element>previous->Element>previous->Down->Right->Element)
				{
					tmp=previous->Down->Right;
					if(tmp->Right->Element!=previous->Element)
						tmp=tmp->Right;
					previous->Element=tmp->Element;
					Current->Down=tmp->Right;
				}
				else
				{
					previous->Element=Current->Element;
					previous->Right=Current->Right;
					delete Current;
				}
			}
		}
		Current=next;
	}
}
*/

SkipList Delete(ElementType Item,SkipList L)
{
	Position previous,Current,up,left,right;
	previous=L;

	if(L->Down==Bottom)
	{
		printf("empty list!!!\n");
		return 0;
	}

	while(previous->Down!=Bottom)
	{
		while(Item<previous->Down->Element)
			previous=previous->Down;
		if(previous->Down->Element==Item)
		{
			Current=previous->Down;
			up=previous;
			right=Current->Right;
			up->Right=Current->Right;
			up->Down=Current->Down;
			free(Current);
			previous=up;
			if(previous->Right->Element==previous->Element)
				previous->Right=previous->Right->Right;
			return L;
		}

		if(Item>previous->Down->Element)
			previous=previous->Right;
		if(previous->Right->Element==Item)
		{
			Current=previous->Right;
			left=previous;
			right=Current->Right;
			left->Right=Current->Right;
			right->Down=Current->Down;
			free(Current);
			previous=left;
		}
		
//		if(previous->Right->Element>Item && previous->Element<Item)
//			return L;
	}

	return L;
}

void PrintList(SkipList L)
{
	if(L!=NULL)
	{
		while(L->Down!=Bottom)
			L=L->Down;
		while(L->Right!=Tail)
		{
			printf("%d ",L->Element);
			L=L->Right;
		}
	}
	printf("\n");
}

void PrintCol(SkipList L)
{
	if(L!=NULL)
	{
		while(L->Down!=Bottom)
		{
			printf("%d ",L->Element);
			L=L->Down;
		}
		while(L->Right!=Tail)
		{
			printf("%d ",L->Element);
			L=L->Right;
		}
	}
}

int main()
{
	int i;
	SkipList L=Initialize();

	int Array[]={5,10,15,20,25,30,35,40,45,50};

	for(i=0;i<10;i++)
		L=Insert(Array[i],L);

	L=Insert(27,L);

	PrintList(L);
//	L=Delete(50,L);
//	PrintList(L);
	PrintCol(L);
	return 0;
}
