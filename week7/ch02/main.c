#include<stdio.h>
#include<stdlib.h>

typedef int ElementType;
typedef ElementType ItemType[2];
struct KdNode;
typedef struct KdNode *Position;
typedef struct KdNode *KdTree;

struct KdNode
{
	ElementType Element;
	Position Left;
	Position Right;
	ItemType Data;
};

void FatalError(char *s)
{
	printf("%s",s);
}

static KdTree RecursiveInsert(ItemType Item,KdTree T,int Level)
{
	if(T==NULL)
	{
		T=malloc(sizeof(struct KdNode));
		if(T==NULL)
			FatalError("Out of space!!!");
		T->Left=T->Right=NULL;
		T->Data[0]=Item[0];
		T->Data[1]=Item[1];
	}
	else if(Item[Level]<T->Data[Level])
		T->Left=RecursiveInsert(Item,T->Left,!Level);
	else
		T->Right=RecursiveInsert(Item,T->Right,!Level);
	return T;
}

KdTree Insert(ItemType Item,KdTree T)
{
	return RecursiveInsert(Item,T,0);
}

void PrintItem(ItemType Item)
{
	printf("%d %d \n",Item[0],Item[1]);
}

//print items satisfying
//low[0]<=item[0]<=high[0] and
//low[1]<=item[1]<=high[1]

static void RecPrintRange(ItemType Low,ItemType High,KdTree T,int Level)
{
	if(T!=NULL)
	{
		if(Low[0]<=T->Data[0] && T->Data[0]<=High[0] && Low[1]<=T->Data[1] && T->Data[1]<=High[1])
			PrintItem(T->Data);

		if(Low[Level]<=T->Data[Level])
			RecPrintRange(Low,High,T->Left,!Level);
		if(High[Level]>=T->Data[Level])
			RecPrintRange(Low,High,T->Right,!Level);
	}
}

void PrintRange(ItemType Low,ItemType High,KdTree T)
{
	RecPrintRange(Low,High,T,0);
}

int main()
{
	int i;
	KdTree T=NULL;

	int Array[][2]={23,65,26,63,49,58,20,29,17,6,34,19,44,37};
	int array[][2]={10,10,50,70};

	for(i=0;i<7;i++)
		T=Insert(Array[i],T);

	PrintRange(array[0],array[1],T);		//查找[10~50,10~70]之间的元素
	return 0;
}
