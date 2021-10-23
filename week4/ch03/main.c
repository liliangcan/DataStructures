#include<stdio.h>

#include"DisjSet.h"

#define NumSets 9

typedef int DisjSet[NumSets+1];
typedef int SetType;
typedef int ElementType;

void Initialize(DisjSet S)
{
	int i;
	for(i=NumSets;i>0;i--)
		S[i]=0;
}

//assumes Root1 and Root2 are roots
//union is a C keyword, so this routine is named SetUnion

/*
void SetUnion(DisjSet S,SetType Root1,SetType Root2)
{
	S[Root2]=Root1;
}
*/

void SetUnion(DisjSet S,SetType Root1,SetType Root2)
{
	if(S[Root2]<S[Root1])		//Root2 is deeper set
		S[Root1]=Root2;			//make Root2 new root
	else
	{
		if(S[Root1]==S[Root2])	//same height
			S[Root1]--;			//so update
		S[Root2]=Root1;
	}
}

/*
SetType Find(ElementType X,DisjSet S)
{
	if(S[X]<=0)
		return X;
	else
		return Find(S[X],S);
}
*/

SetType Find(ElementType X,DisjSet S)
{
	if(S[X]<=0)
		return X;
	else
		return S[X]=Find(S[X],S);
}

int main()
{
	DisjSet S;
	Initialize(S);

	SetUnion(S,7,8);
	SetUnion(S,5,6);
	SetUnion(S,5,7);
	SetUnion(S,4,5);

	printf("查找8的结果为：%d\n",Find(8,S));

	return 0;
}
