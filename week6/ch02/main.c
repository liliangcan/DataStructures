#include<stdio.h>
#include<stdlib.h>
#include"RedBlackTree.h"

#define Infinity 9999999
#define NegInfinity -9999999

typedef int ElementType;
typedef enum ColorType{Red,Black}ColorType;
struct RedBlackNode;
typedef struct RedBlackNode *RedBlackTree;

struct RedBlackNode
{
	ElementType Element;
	RedBlackTree Parent;
	RedBlackTree Left;
	RedBlackTree Right;
	ColorType Color;
};

typedef struct RedBlackNode *Position;
Position NullNode=NULL;	//needs initialization

void FatalError(char *s)
{
	printf("%s",s);
}

//initialization procedure
RedBlackTree Initialize(void)
{
	RedBlackTree T;

	if(NullNode==NULL)
	{
		NullNode=malloc(sizeof(struct RedBlackNode));
		if(NullNode==NULL)
			FatalError("Out of space!!!");
		NullNode->Left=NullNode->Right=NullNode;
		NullNode->Color=Black;
		NullNode->Element=Infinity;
	}

	//create the header node
	T=malloc(sizeof(struct RedBlackNode));
	if(T==NULL)
		FatalError("Out of space!!!");
	T->Element=NegInfinity;
	T->Left=T->Right=NullNode;
	T->Color=Black;

	return T;
}

Position Find(ElementType Item,RedBlackTree T)
{
	Position Tmp=T;
	if(T!=NullNode)
	{
		if(Item>T->Element)
			Tmp=Find(Item,T->Right);
		else if(Item<T->Element)
			Tmp=Find(Item,T->Left);
	}
	return Tmp;
}

RedBlackTree SingleRotateWithLeft(RedBlackTree T)
{
	Position Tmp;
	Tmp=T->Right;
	T->Right=Tmp->Left;
	Tmp->Left=T;
	T=Tmp;

	return T;
}

RedBlackTree SingleRotateWithRight(RedBlackTree T)
{
	Position Tmp;
	Tmp=T->Left;
	T->Left=Tmp->Right;
	Tmp->Right=T;
	T=Tmp;

	return T;
}

//perform a rztation at node X
//(whose parent is passed as a parameter)
///the child is deduced by examining Item

static Position Rotate(ElementType Item,Position Parent)
{
	if(Item<Parent->Element)
		return Parent->Left = Item < Parent->Left->Element ?
			SingleRotateWithLeft(Parent->Left):
			SingleRotateWithRight(Parent->Left);
	else
		return Parent->Right = Item < Parent->Right->Element ?
			SingleRotateWithLeft(Parent->Right):
			SingleRotateWithRight(Parent->Right);
}

static Position X,P,GP,GGP;

static void HandleReorient(ElementType Item,RedBlackTree T)
{
	X->Color=Red;		//do the color flip
	X->Left->Color=Black;
	X->Right->Color=Black;

	if(P->Color==Red)	//have to rotate
	{
		GP->Color=Red;
		if((Item<GP->Element) != (Item<P->Element))
			P=Rotate(Item,GP);	//start double rotation
		X=Rotate(Item,GGP);
		X->Color=Black;
	}
	T->Right->Color=Black;	//make root black
}

RedBlackTree Insert(ElementType Item,RedBlackTree T)
{
	X=P=GP=T;
	NullNode->Element=Item;
	while(X->Element != Item)		//descend down the tree
	{
		GGP=GP;
		GP=P;
		P=X;
		if(Item<X->Element)
			X=X->Left;
		else
			X=X->Right;
		if(X->Left->Color==Red && X->Right->Color==Red)
			HandleReorient(Item,T);
	}
	if(X!=NullNode)
		return NullNode;	//duplicate

	X=malloc(sizeof(struct RedBlackNode));
	if(X==NULL)
		FatalError("Out of space!!!");
	X->Element=Item;
	X->Left=X->Right=NullNode;

	if(Item<P->Element)	//attach to its parent
		P->Left=X;
	else
		P->Right=X;
	HandleReorient(Item,T);	//color red;maybe ratate

	return T;
}

Position Successor(Position Tmp,RedBlackTree T)
{
	if(Tmp->Right!=NullNode)
	{
		Position q=NullNode;
		Position p=Tmp->Right;
		while(p->Left!=NullNode)
		{
			q=p;
			p=p->Left;
		}
		return q;
	}
	else
	{
		Position Tmpy=Tmp->Parent;
		while(Tmpy!=NullNode && Tmp==Tmpy->Right)
		{
			Tmp=Tmpy;
			Tmpy=Tmpy->Parent;
		}
		return Tmpy;
	}
}

void DeleteFixup(Position Tmp,RedBlackTree T)
{
	while(Tmp!=T && Tmp->Color==Black)
	{
		if(Tmp==Tmp->Parent->Left)
		{
			Position Tmp2=Tmp->Parent->Right;
			if(Tmp2->Color==Red)
			{
				Tmp2->Color=Black;
				Tmp->Parent->Color=Red;
				SingleRotateWithLeft(Tmp->Parent);
				Tmp2=Tmp->Parent->Right;
			}
			if(Tmp2->Left->Color==Black  && Tmp2->Right->Color==Black)
			{
				Tmp2->Color=Red;
				Tmp=Tmp->Parent;
			}
			else if(Tmp2->Right->Color==Black)
			{
				Tmp2->Color=Red;
				Tmp2->Left->Color=Black;
				SingleRotateWithRight(Tmp2);
				Tmp2=Tmp->Parent->Right;
			}
			Tmp2->Color=Tmp->Parent->Color;
			Tmp->Parent->Color=Black;
			Tmp2->Right->Color=Black;
			SingleRotateWithLeft(Tmp->Parent);

			Tmp=T;
		}
		else
		{
			Position Tmp2=Tmp->Parent->Left;
			if(Tmp2->Color==Red)
			{
				Tmp2->Color=Black;
				Tmp->Parent->Color=Red;
				SingleRotateWithRight(Tmp->Parent);
				Tmp2=Tmp->Parent->Left;
			}
			if(Tmp2->Left->Color==Black && Tmp2->Right->Color==Black)
			{
				Tmp2->Color=Red;
				Tmp=Tmp->Parent;
			}
			else if(Tmp2->Left->Color==Black)
			{
				Tmp2->Color=Red;
				Tmp2->Right->Color=Black;
				SingleRotateWithLeft(Tmp2);
				Tmp2=Tmp->Parent->Left;
			}
			Tmp2->Color=Tmp->Parent->Color;
			Tmp->Parent->Color=Black;
			Tmp2->Left->Color=Black;
			SingleRotateWithRight(Tmp->Parent);

			Tmp=T;
		}
	}
	Tmp->Color=Black;
}

void Delete(ElementType Item,RedBlackTree T)
{
	Position Tmpx,Tmpy,Tmpz;
	Tmpz=Find(Item,T);

	if(Tmpz->Left==NullNode || Tmpz->Right==NullNode)
		Tmpy=Tmpz;
	else
		Tmpy=Successor(Tmpz,T);

	if(Tmpy->Left!=NullNode)
		Tmpx=Tmpy->Left;
	else
		Tmpx=Tmpy->Right;
	Tmpx->Parent=Tmpy->Parent;

	if(Tmpy->Parent==NullNode)
		T=Tmpx;
	else
	{
		if(Tmpy==Tmpy->Parent->Left)
			Tmpy->Parent->Left=Tmpx;
		else
			Tmpy->Parent->Right=Tmpx;
	}

	if(Tmpy!=Tmpz)
		Tmpz->Element=Tmpy->Element;

	if(Tmpy->Color==Black)
		DeleteFixup(Tmpx,T);
}

//print the tree,wotch out for NullNode
//and skip header
static void DoPrint(RedBlackTree T)
{
	if(T!=NullNode)
	{
		DoPrint(T->Left);
		printf("%d ",T->Element);
		DoPrint(T->Right);
	}
}

void PrintTree(RedBlackTree T)
{
	DoPrint(T->Right);
}

int main()
{
	int i;
	RedBlackTree T;
	int Array[]={10,85,15,70,20,60,30,50,65,80,90,40,5,55};

	T=Initialize();

	for(i=0;i<14;i++)
		T=Insert(Array[i],T);

	PrintTree(T);
//	Delete(55,T);
//	PrintTree(T);
	return 0;
}
