/*****************.h文件部分*****************/

typedef int ElementType;
struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;

#ifdef _List_H

List MakeEmpty(List L);               //置空
int IsEmpty(List L);					     //判断是否为空
int IsLast(Position P,List L);			 //判断是否为最后一个节点
Position Find(ElementType X,List L);		//按元素查找
int FindKth(int K,List L);					//按位置查找
void DeleteX(ElementType X,List L);				//按元素删除
Position FindPrevious(ElementType X,List L);			//查找前驱结点的位置
void Insert(ElementType X,List L,Position P);			//按元素插入
void DeleteList(List L);						//删除表
Position Header(List L);					//返回头结点
Position First(List L);							//返回第一个有元素的结点
Position Advance(Position P);				 //返回后继结点
ElementType Retrieve(Position P);				//取结点元素
void Traverse(List L);						//遍历

#endif  /* _List_H */

struct Node
{
	ElementType Element;
	Position Next;
};

void initial(List L)
{
	Position header=malloc(sizeof(struct Node));
	header=L;
	header->Next=NULL;
}

void DeleteList(List L)
{
	Position P,TmpCell;
	
	P=L->Next;
	L->Next=NULL;
	while(P!=NULL)
	{
		TmpCell=P->Next;
		free(P);
		P=TmpCell;
	}
}

List MakeEmpty(List L)
{
	if(L!=NULL)
		DeleteList(L);
	L=malloc(sizeof(struct Node));
	if(L==NULL)
		printf("Out of memory!");
	L->Next=NULL;
	return L;
}

int IsEmpty(List L)
{
	return L->Next == NULL;
}

int IsLast(Position P,List L)
{
	return P->Next == NULL;
}

ElementType Retrieve(Position P)
{
	return P->Element;
}

void Traverse(List L)
{
	Position P;
	int element;
	P=L;
	if(IsEmpty(L))
		printf("Empty list\n");
	while(!IsLast(P,L))
	{
		element=P->Next->Element;
		printf("%d ",element);
		P=P->Next;
	}
	element=P->Element;
	printf("%\n\n",element);

}

Position Advance(Position P)
{
	return P->Next;
}

int FindKth(int K,List L)
{
	Position P;
	int i;

	P=L->Next;
	for(i=1;i<K;i++)
		P=P->Next;

	return P->Element;
}

Position Header(List L)
{
	return L;
}

Position First(List L)
{
	return L->Next;
}

Position Find(ElementType X,List L)
{
	Position P;
	
	P=L->Next;
	while(P!=NULL && P->Element!=X)
		P=P->Next;

	return P;
}

Position FindPrevious(ElementType X,List L)
{
	Position P;

	P=L;
	while(P->Next!=NULL && P->Next->Element!=X)
		P=P->Next;
	
	return P;
}

void DeleteX(ElementType X,List L)
{
	Position P,TmpCell;

	P=FindPrevious(X,L);
	
	if(!IsLast(P,L))
	{
		TmpCell=P->Next;
		P->Next=TmpCell->Next;
		free(TmpCell);
	}
}

void Insert(ElementType X,List L,Position P)
{
	Position TmpCell;

	TmpCell=malloc(sizeof(struct Node));
	if(TmpCell == NULL)
		printf("Out of space!!!");

	TmpCell->Element=X;
	TmpCell->Next=P->Next;
	P->Next=TmpCell;
}

/*****************.c文件部分(测试运行)*****************/

#include<stdio.h>
#include<time.h>
#include<stdlib.h>

#include"List.h"

int main()
{
	List L;
	Position P;
	int element,i;
	int n=10;

	L=MakeEmpty(NULL);

	srand((int)time(0));
	for(i=0;i<n;i++)
	{
		element=rand()%100;
		Insert(element,L,Header(L));
	}
	printf("生成初始长度为10的随机链表为：");
	Traverse(L);

	Insert(77,L,Header(L));
	printf("在头部插入77后随机链表为：");
	Traverse(L);

	P=Find(77,L);
	Insert(88,L,P);
	printf("在数77后插入88后随机链表为：");
	Traverse(L);

	printf("目前链表第二个数是：%d\n\n",FindKth(2,L));

	DeleteX(77,L);
	printf("删除77后目前链表第三个数是：%d\n\n",FindKth(3,L));

	DeleteList(L);
	printf("删除链表后目前链表为：");
	Traverse(L);
  
}
