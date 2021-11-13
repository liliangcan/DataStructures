#include<stdio.h>
#include<stdlib.h>

#define MaxSiblings 10

typedef int ElementType;

typedef struct PairHeapNode;
typedef struct PairHeapNode *Position;
typedef struct PairHeapNode *PairHeap;

struct PairHeapNode
{
	ElementType Elment;
	Position Prev;
	Position LeftChild;
	Position NextSibling;
};

void FatalError(char *s)
{
	printf("%s",s);
}

int IsEmpty(PairHeap P)
{
	if(P==NULL)
		return 1;
	else
		return 0;
}

//this is the basic operation to maintain order
//links first and second together to saticfy heap order
//returns the resulting tree
//first is assumed not null
//first->nextsibling must be null on entry

Position CompareAndLink(Position First,Position Second)
{
	if(Second==NULL)
		return First;
	else if(First->Elment<=Second->Elment)
	{
		//attach second as the leftmost child of first
		Second->Prev=First;
		First->NextSibling=Second->NextSibling;
		if(First->NextSibling!=NULL)
			First->NextSibling->Prev=First;
		Second->NextSibling=First->LeftChild;
		if(Second->NextSibling!=NULL)
			Second->NextSibling->Prev=Second;
		First->LeftChild=Second;
		return First;
	}
	else
	{
		//attach first as the leftmost child of second
		Second->Prev=First->Prev;
		First->Prev=Second;
		First->NextSibling=Second->LeftChild;
		if(First->NextSibling!=NULL)
			First->NextSibling->Prev=First;
		Second->LeftChild=First;
		return Second;
	}
}

//insert item into pairing heap H
//return resulting pairing heap
//a pointer to the newly allocated node
//is passed back by reference and accessed as *Loc

PairHeap Insert(ElementType Item,PairHeap H,Position Loc)
{
	Position NewNode;

	NewNode=malloc(sizeof(struct PairHeapNode));
	if(NewNode==NULL)
		FatalError("Out of space!!!");
	NewNode->Elment=Item;
	NewNode->LeftChild=NewNode->NextSibling=NULL;
	NewNode->Prev=NULL;

	Loc=NewNode;
	if(H==NULL)
		return NewNode;
	else
		return CompareAndLink(H,NewNode);
}

//lower item in position P by Delta
PairHeap DecreaseKey(Position P,ElementType Delta,PairHeap H)
{
	if(Delta<0)
		FatalError("DecreaseKey called with nagative Delta");

	P->Elment-=Delta;
	if(P==H)
		return H;

	if(P->NextSibling!=NULL)
		P->NextSibling->Prev=P->Prev;
	if(P->Prev->LeftChild==P)
		P->Prev->LeftChild=P->NextSibling;
	else
		P->Prev->NextSibling=P->NextSibling;

	P->NextSibling=NULL;
	return CompareAndLink(H,P);
}

//assumes firstsibling is not NULL
PairHeap CombineSiblings(Position FirstSibling)
{
	static Position TreeArray[MaxSiblings];
	int i,j,NumSiblings;

	//if only one teee, return it
	if(FirstSibling->NextSibling==NULL)
		return FirstSibling;

	//place each subtree in treearray
	for(NumSiblings=0;FirstSibling!=NULL;NumSiblings++)
	{
		TreeArray[NumSiblings]=FirstSibling;
		FirstSibling->Prev->NextSibling=NULL;	//break links
		FirstSibling=FirstSibling->NextSibling;
	}
	TreeArray[NumSiblings]=NULL;

	//combine the subtrees two at a time
	//going left to right
	for(i=0;i+1<NumSiblings;i+=2)
		TreeArray[i]=CompareAndLink(TreeArray[i],TreeArray[i+1]);
	//j has the result of the last compareandlink
	//if an odd number of trees, get the last one
	j=i-2;
	if(j==NumSiblings-3)
		TreeArray[j]=CompareAndLink(TreeArray[j],TreeArray[j+2]);
	//now go right to left,merging last tree with
	//next to last.the result becomes the new last
	for(;j>=2;j-=2)
		TreeArray[j-2]=CompareAndLink(TreeArray[j-2],TreeArray[j]);

	return TreeArray[0];
}

/*		no meaning
Position Find(ElementType Item,PairHeap P)
{
	Position Tmp=P;
	if(!IsEmpty(P))
	{
		while(Item>Tmp->Elment && !IsEmpty(Tmp->LeftChild))
			Tmp=Tmp->LeftChild;
		if(!IsEmpty(Tmp->NextSibling))
			Tmp=Tmp->NextSibling;
			...
	}
}
*/

PairHeap DeleteMin(ElementType *MinItem,PairHeap H)
{
	Position NewRoot=NULL;

	if(IsEmpty(H))
		FatalError("Pairing heap is empty!\n");
	else
	{
		*MinItem=H->Elment;
		if(H->LeftChild!=NULL)
			NewRoot=CombineSiblings(H->LeftChild);
		free(H);
	}
	return NewRoot;
}

void PrintHeap(PairHeap P)
{
	if(P!=NULL)
	{
		printf("%d ",P->Elment);
		if(P->LeftChild!=NULL)
			PrintHeap(P->LeftChild);
		if(P->NextSibling!=NULL)
			PrintHeap(P->NextSibling);
	}
}

int main()
{
	int i,MinItem=0;
	Position  Tmp=NULL;
	PairHeap P=NULL;
	int Array[]={65,26,49,58,20,29,17,6};

	for(i=0;i<8;i++)
		P=Insert(Array[i],P,Tmp);

	PrintHeap(P);
	printf("\n");

	P=DeleteMin(&MinItem,P);
	printf("删除最小值%d后遍历堆：",MinItem);
	PrintHeap(P);
	return 0;
}
