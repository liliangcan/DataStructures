/******************.h文件********************/

typedef int ElementType;
typedef unsigned int Index;
struct ListNode;
typedef struct ListNode *Position;
struct HashTbl;
typedef struct HashTbl *HashTable;
#define MinTableSize 3

#ifdef _HashSep_H

HashTable InitializeTable(int TableSize);
void DestroyTable(HashTable H);
Position Find(ElementType Key,HashTable H);
void Insert(ElementType Key,HashTable H);
ElementType Retrieve(Position P);

#endif  /* _HashSep_H */

struct ListNode
{
	ElementType Element;
	Position Next;
};

typedef Position List;

struct HashTbl
{
	int TableSize;
	List *TheLists;
};

void FatalError(char *s)
{
    printf("%s\n",s);
}

void Error(char *s)
{
    printf("%s\n",s);
}

void DestroyTable(HashTable H)
{
	int i;
	Position P,TmpCell;
	if(H != NULL)
	{
		for(i=0;i<H->TableSize;i++)
		{
			P=H->TheLists[i]->Next;
			H->TheLists[i]->Next=NULL;
			while(P!=NULL)
			{
				TmpCell=P->Next;
				free(P);
				P=TmpCell;
			}
		}
		printf("\ndestroy calls\n");
		free(H);
	}
}

static ElementType NextPrime(ElementType TableSize)
{
	int i,j,count;

	for(i=TableSize;i<2*TableSize;i++)
	{
		count=0;
		for(j=2;j<i/2;j++)
			if(i%j == 0)
			{
				count++;
				break;
			}
		if(count == 0)
			return i;
	}
	return 0;
}

static Index Hash(const ElementType Key,int TableSize)
{
	unsigned int HashVal=0;

	HashVal=(HashVal<<5) + Key;

	return HashVal%TableSize;
}

static Index HashString(const char *Key,int TableSize)
{
	unsigned int HashVal=0;

	while(*Key != '\0')
		HashVal=(HashVal<<5) + *Key++;

	return HashVal%TableSize;
}

HashTable InitializeTable(int TableSize)
{
	HashTable H;
	int i;

	if(TableSize < MinTableSize)
	{
		Error("Table size too small");
		return NULL;
	}

	H = malloc(sizeof(struct HashTbl));
	if(H == NULL)
		FatalError("Out of Space!!!");

	H->TableSize = NextPrime(TableSize);

	H->TheLists = malloc(sizeof(List)*H->TableSize);
	if(H->TheLists == NULL)
		FatalError("Out of space!!!");

	for(i=0;i<H->TableSize;i++)
	{
		H->TheLists[i]=malloc(sizeof(struct ListNode));
		if(H->TheLists[i] == NULL)
			FatalError("Out of space!!!");
		else
			H->TheLists[i]->Next=NULL;
	}
	printf("initialize calls\n");

	return H;
}

ElementType Retrieve(Position P)
{
	return P->Element;
}

Position Find(ElementType Key,HashTable H)
{
	Position P;
	List L;

	L = H->TheLists[Hash(Key,H->TableSize)];
	P = L->Next;
	while(P!=NULL && P->Element!=Key)
		P=P->Next;
	if(P==NULL)
		printf("don't find %d     ",Key);
	return P;
}

void Insert(ElementType Key,HashTable H)
{
	Position Pos,NewCell;
	List L;

	Pos=Find(Key,H);
	if(Pos == NULL)
	{
		NewCell=malloc(sizeof(struct ListNode));
		if(NewCell==NULL)
			FatalError("Out of space!!!");
		else
		{
			L=H->TheLists[Hash(Key,H->TableSize)];
			NewCell->Next = L->Next;
			NewCell->Element = Key;
			L->Next = NewCell;
		}
	}
	printf("Insert calls\n");
}

/*******************.c文件**********************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include"HashSep.h"

int main()
{
	int j,element;
	Position P;
	HashTable H;

	H=InitializeTable(5);
	srand((int)time(0));
	for(j=0;j<20;j++)
	{
		element=rand()%100;
		Insert(element,H);
	}
	P=Find(2,H);
	if(P!=NULL)
	{
		element=Retrieve(P);
		printf("%d\n",element);
	}

	DestroyTable(H);

	return 0;
}
