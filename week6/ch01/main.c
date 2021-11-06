#include<stdio.h>
#include<stdlib.h>

typedef int ElementType;
struct SplayNode;
typedef struct SplayNode *SplayTree;

struct SplayNode
{
	ElementType Element;
	SplayTree Left;
	SplayTree Right;
};

typedef struct SplayNode *Position;
static Position NullNode=NULL;	//needs initialization

void FatalError(char *s)
{
	printf("%s",s);
}

SplayTree Initialize(void)
{
	if(NullNode==NULL)
	{
		NullNode=malloc(sizeof(struct SplayNode));
		if(NullNode==NULL)
			FatalError("Out of space!!!");
		NullNode->Left=NullNode->Right=NullNode;
	}
	return NullNode;
}

SplayTree MakeEmpty(SplayTree T)
{
	T=Initialize();
	return T;
}

ElementType Retrieve(SplayTree T)
{
	return T->Element;
}

SplayTree SingleRotateWithLeft(SplayTree T)
{
	Position Tmp;
	Tmp=T->Right;
	T->Right=Tmp->Left;
	Tmp->Left=T;
	T=Tmp;

	return T;
}

SplayTree SingleRatateWithRight(SplayTree T)
{
	Position Tmp;
	Tmp=T->Left;
	T->Left=Tmp->Right;
	Tmp->Right=T;
	T=Tmp;

	return T;
}

//top-down splay procedure
//not requiring item to be in the tree
SplayTree Splay(ElementType Item,Position X)
{
	static struct SplayNode Header;
	Position LeftTreeMax,RightTreeMin;

	Header.Left=Header.Right=NullNode;
	LeftTreeMax=RightTreeMin=&Header;
	NullNode->Element=Item;

	while(Item != X->Element)
	{
		if(Item<X->Element)
		{
			if(Item<X->Left->Element)
				X=SingleRatateWithRight(X);
			if(X->Left==NullNode)
				break;
			//link right
			RightTreeMin->Left=X;
			RightTreeMin=X;
			X=X->Left;
		}
		else
		{
			if(Item>X->Right->Element)		//书中为<错误，应改为>
				X=SingleRotateWithLeft(X);
			if(X->Right==NullNode)
				break;
			//link left
			LeftTreeMax->Right=X;
			LeftTreeMax=X;
			X=X->Right;
		}
	}
	//reassemble
	LeftTreeMax->Right=X->Left;
	RightTreeMin->Left=X->Right;
	X->Left=Header.Right;
	X->Right=Header.Left;

	return X;
}

SplayTree Find(ElementType X,SplayTree T)
{
	return Splay(X,T);
}

SplayTree FindMin(SplayTree T)
{
	Position Tmp=T;
	while(Tmp->Left!=NullNode)
		Tmp=Tmp->Left;

	return Splay(Tmp->Element,T);
}

SplayTree FindMax(SplayTree T)
{
	SplayTree Tmp=T;
	while(Tmp->Right!=NullNode)
		Tmp=Tmp->Right;

	return Splay(Tmp->Element,T);
}

SplayTree Insert(ElementType Item,SplayTree T)
{
	static Position NewNode=NULL;

	if(NewNode==NULL)
	{
		NewNode=malloc(sizeof(struct SplayNode));
		if(NewNode==NULL)
			FatalError("Out of space!!!");
	}
	NewNode->Element=Item;

	if(T==NullNode)
	{
		NewNode->Left=NewNode->Right=NullNode;
		T=NewNode;
	}
	else
	{
		T=Splay(Item,T);
		if(Item<T->Element)
		{
			NewNode->Left=T->Left;
			NewNode->Right=T;
			T->Left=NullNode;
			T=NewNode;
		}
		else if(Item>T->Element)
		{
			NewNode->Right=T->Right;
			NewNode->Left=T;
			T->Right=NullNode;
			T=NewNode;
		}
		else
			return T;
	}

	NewNode=NULL;	//so next insert will call malloc
	return T;
}

//top-down delete procedure
SplayTree Remove(ElementType Item,SplayTree T)
{
	Position NewTree;
	if(T!=NullNode)
	{
		T=Splay(Item,T);
		if(Item==T->Element)
		{
			//found it
			if(T->Left==NullNode)
				NewTree=T->Right;
			else
			{
				NewTree=T->Left;
				NewTree=Splay(Item,NewTree);
				NewTree->Right=T->Right;
			}
			free(T);
			T=NewTree;
		}
	}
	return T;
}

void print(SplayTree T)
{
	if(T!=NULL)
	{
		if(T->Left!=NullNode)
			print(T->Left);
		printf("%d ",T->Element);
		if(T->Right!=NullNode)
			print(T->Right);
	}
}

int main()
{
	SplayTree T=Initialize();
	int i,element;
	int Array[]={23,54,27,76,44,77,34,56};
	for(i=0;i<8;i++)
		T=Insert(Array[i],T);
	print(T);
	printf("\n");
	T=FindMax(T);
	printf("找到最大值%d ，再遍历：\n",Retrieve(T));
	print(T);
	printf("\n");

	T=Find(44,T);
	element=Retrieve(T);
	printf("查找数值%d后，再遍历：\n",element);		//几次伸展树，结果不会改变性质
	print(T);
	printf("\n");

	T=Find(29,T);
	element=Retrieve(T);
	printf("查找数值29后，输出根值为：%d,再遍历：\n",element);
	print(T);
	printf("\n");

	T=Remove(54,T);
	printf("删除数值54后，再遍历：\n");
	print(T);
	printf("\n");

	return 0;
}
