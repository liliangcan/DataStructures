/****************.h文件部分********************/

typedef double ElementType;
typedef int PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;

#define SpaceSize 20

#ifdef _Cursor_H

void InitializeCursorSpace(void);                  //初始化
List MakeEmpty(List L);                     //置空
int IsEmpty(const List L);                           //判断是否为空
int IsLast(const Position P,const List L);         //判断是否为最后
Position Find(ElementType X,const List L);            //查找
void Delete(ElementType X,List L);                  //删除
Position FindPrevious(ElementType X,const list L);              //查找前驱
void Insert(ElementType X,List L,Position P);           //插入
void DeleteList(List L);                             //删除表
Position Header(const List L);                     //返回头结点
Position First(const List L);                       //返回第一个元素
Position Advance(const Position p);                      //返回后继
ElementType Retrieve(const Position p);              //取值
void Traverse(List L);								//遍历

#endif     /*  _Cursor_H */


struct Node
{
	ElementType Element;
	Position Next;
};

struct Node CursorSpace[SpaceSize];

void FatalError(char *s)
{
    printf("%s\n",s);
}

int IsEmpty(List L)
{
    return CursorSpace[L].Next == 0;
}

void Traverse(List L)
{
	Position P;
	double element;
	P=L;
	if(IsEmpty(L))
		FatalError("Empty list!\n");
	while(!IsLast(P,L))
	{
		element=CursorSpace[CursorSpace[P].Next].Element;
		printf("%d ",element);
		P=CursorSpace[P].Next;
	}
	element=CursorSpace[P].Element;
	printf("%\n\n",element);

}

void InitializeCursorSpace(void)
{
    int i;
    for(i=0;i<SpaceSize;i++)
        CursorSpace[i].Next = i==SpaceSize-1?0:i+1;
}


Position FindPrevious(ElementType X,const List L)
{
    Position P;
    P=L;
    while(P && CursorSpace[CursorSpace[P].Next].Element!=X)
        P=CursorSpace[P].Next;
    return P;
}

static Position CursorAlloc(void)
{
    Position P;

    P = CursorSpace[0].Next;
    CursorSpace[0].Next=CursorSpace[P].Next;

    return P;
}

static void CursorFree(Position P)
{
    CursorSpace[P].Next=CursorSpace[0].Next;
    CursorSpace[0].Next=P;
}

int IsLast(Position P,List L)
{
    return CursorSpace[P].Next == 0;
}

Position Find(ElementType X,List L)
{
    Position P;

    P = CursorSpace[L].Next;
    while(P && CursorSpace[P].Element!=X)
        P=CursorSpace[P].Next;

    return P;
}

void Delete(ElementType X,List L)
{
    Position P,TmpCell;

    P=FindPrevious(X,L);

    if(!IsLast(P,L))
    {
        TmpCell=CursorSpace[P].Next;
        CursorSpace[P].Next=CursorSpace[TmpCell].Next;
        CursorFree(TmpCell);
    }
}

void Insert(ElementType X,List L,Position P)
{
    Position TmpCell;

    TmpCell=CursorAlloc();
    if(TmpCell == 0)
        FatalError("Out of space!!!");

    CursorSpace[TmpCell].Element=X;
    CursorSpace[TmpCell].Next=CursorSpace[P].Next;
    CursorSpace[P].Next=TmpCell;
}

/*****************.c文件部分***********************/

#include<stdio.h>
#include"Cursor.h"

int main()
{
	List L;
	Position P;
    InitializeCursorSpace();
    
	L=CursorAlloc();

    CursorSpace[L].Next=0;
    Insert(1,L,L);
    Insert(6,L,L);
    Insert(12.998,L,L);
//    Delete(12.998,L);

    P=CursorSpace[L].Next;
	P=CursorSpace[P].Next;
    printf("%lf\n",CursorSpace[P].Element);
}
