/*****************.h文件部分**********************/

typedef int ElementType;
struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode Stack;

#ifdef _Stack_h

int IsEmpty(Stack S);                  //判空
Stack CreateStack(void);                //创建栈
void DisposeStack(Stack S);           //释放栈的例程
void MakeEmpty(Stack S);                 //置空
void Push(ElementType X,Stack S);          //入栈
ElementType Top(Stack S);                 //取栈顶元素
void Pop(Stack S);                      //出栈

#endif      /* _Stack_h */

struct Node
{
	ElementType Element;
	PtrToNode Next;
};

void FatalError(char *s)
{
    printf("%s\n",s);

}

int IsEmpty(Stack S)
{
	return S->Next == NULL;
}

void Pop(Stack S)
{
	PtrToNode FirstCell;
	if(IsEmpty(S))
		printf("Empty stack");
	else
	{
		FirstCell=S->Next;
		S->Next=S->Next->Next;
		free(FirstCell);
	}
}

void MakeEmpty(Stack S)
{
	if(S == NULL)
		FatalError("Must use CreateStack first!");
	else
		while(!IsEmpty(S))
			Pop(S);
}

Stack CreateStack(void)
{
	Stack S;

	S=malloc(sizeof(struct Node));
	if(S == NULL)
		FatalError("Out of space!!!");
	S->Next=NULL;
	MakeEmpty(S);
	return S;
}

void DisposeStack(Stack S)
{
	PtrToNode TmpCell;
	while(S != NULL)
	{
		TmpCell=S->Next;
		free(S);
		S=TmpCell;
	}
}

void Push(ElementType X,Stack S)
{
	PtrToNode TmpCell;

	TmpCell=malloc(sizeof(struct Node));
	if(TmpCell == NULL)
		FatalError("Out of space!!!");
	else
	{
		TmpCell->Element=X;
		TmpCell->Next=S->Next;
		S->Next=TmpCell;
	}
}

ElementType Top(Stack S)
{
	if(!IsEmpty(S))
		return S->Next->Element;
	printf("Empty stack");
	return 0;
}

/**************.c文件部分*****************/

#include<stdio.h>
#include"Stack.h"

int main()
{
	int i,n=15;
	Stack S;
	S=CreateStack();
	for(i=1;i<=n;i++)
	{
		Push(i,S);
	}
	Push(20,S);
	printf("压入20后栈顶元素为：%d\n",Top(S));

  DisposeStack(S);
	return 0;
}
