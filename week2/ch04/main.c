/***************.h文件****************/

typedef int ElementType;
typedef unsigned int Index;
typedef Index Position;

struct HashTbl;
typedef struct HashTbl *HashTable;

#define MinTableSize 5

#ifdef _HashQuad_H

HashTable InitializeTable(int TableSize);
void DestroyTable(HashTable H);
Position Find(ElementType Key,HashTable H);
void Insert(ElementType Key,HashTable H);
ElementType Retrieve(Position P,HashTable H);
HashTable Rehash(HashTable H);
void DeleteX(ElementType Key,HashTable H);
void DeleteP(Position P,Hashtable H);

#endif  /* _HashQuad_H */

enum KindOfEntry{Legitimate,Empty,Deleted};

struct HashEntry
{
	ElementType Element;
	enum KindOfEntry Info;
};

typedef struct HashEntry Cell;

struct HashTbl
{
	int TableSize;
	Cell *TheCells;
};

void FatalError(char *s)
{
    printf("%s\n",s);
}

void Error(char *s)
{
    printf("%s\n",s);
}

static Index Hash(const ElementType Key,int TableSize)
{
	unsigned int HashVal=0;

	HashVal=(HashVal<<5) + Key;

	return HashVal % TableSize;
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

HashTable InitializeTable(int TableSize)
{
	HashTable H;
	int i;

	if(TableSize < MinTableSize)
	{
		Error("Table size too small");
		return NULL;
	}

	H=malloc(sizeof(struct HashTbl));
	if(H==NULL)
		FatalError("Out of space!!!");

	H->TableSize=NextPrime(TableSize);

	H->TheCells=malloc(sizeof(Cell)*H->TableSize);
	if(H->TheCells == NULL)
		FatalError("Out of space!!!");

	for(i=0;i<H->TableSize;i++)
		H->TheCells[i].Info = Empty;

	return H;
}

Position Find(ElementType Key,HashTable H)
{
	Position CurrentPos;
	int CollisionNum;

	CollisionNum=0;
	CurrentPos=Hash(Key,H->TableSize);
	while(H->TheCells[CurrentPos].Info!=Empty && H->TheCells[CurrentPos].Element!=Key)
	{
		CurrentPos += 2* ++CollisionNum - 1;
		if((int)CurrentPos >= H->TableSize)
			CurrentPos -= H->TableSize;
	}
	return CurrentPos;
}

void Insert(ElementType Key,HashTable H)
{
	Position Pos;

	Pos=Find(Key,H);
	if(H->TheCells[Pos].Info!=Legitimate)
	{
		H->TheCells[Pos].Info=Legitimate;
		H->TheCells[Pos].Element=Key;
	}
	printf("insert calls\n");
}

HashTable Rehash(HashTable H)
{
	int i,OldSize;
	Cell *OldCells;

	OldCells=H->TheCells;
	OldSize=H->TableSize;

	H=InitializeTable(2*OldSize);

	for(i=0;i<OldSize;i++)
		if(OldCells[i].Info==Legitimate)
			Insert(OldCells[i].Element,H);
	free(OldCells);

	return H;
}

void DestroyTable(HashTable H)
{
	if(H != NULL)
		free(H);
}

void DeleteP(Position P,HashTable H)
{
	if(H->TheCells[P].Info == Legitimate)
		H->TheCells[P].Info=Deleted;
}

ElementType Retrieve(Position P,HashTable H)
{
	if(H->TheCells[P].Info == Legitimate)
		return H->TheCells[P].Element;
	else
	{
		printf("position %d is empty!",P+1);
		return 0;
	}
}

void DeleteX(ElementType Key,HashTable H)
{
	Position Pos=Find(Key,H);
	DeleteP(Pos,H);
}

/****************.c文件*****************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include"HashQuad.h"

int main()
{
	Position P;
	int i,element;
	HashTable H;
	H=InitializeTable(15);

	srand((int)time(0));
	for(i=0;i<10;i++)
	{
		element=rand()%100;
		Insert(element,H);
	}
	Insert(20,H);
	P=Find(20,H);
	element=Retrieve(P,H);
	printf("插入元素20后根据其位置再取出：%d\n",element);

	printf("从头遍历一次数组所有位置：\n",element);
	for(i=0;i<15;i++)
		printf("%d\n",Retrieve(i,H));

	DeleteX(20,H);
	P=Find(20,H);
	element=Retrieve(P,H);
	printf("删除元素20后再试着取出：%d\n",element);

	return 0;
}
