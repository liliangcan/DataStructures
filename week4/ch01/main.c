#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef int ElementType;
#define Size 15

void FatalError(char *s)
{
    printf("%s\n",s);
}

void Merge(ElementType A[],ElementType TmpArray[],int Lpos,int Rpos,int RightEnd)
{
	int i,LeftEnd,NumElements,TmpPos;

	LeftEnd=Rpos-1;           //曾错误打成Lpos-1导致运行有问题
	TmpPos=Lpos;
	NumElements=RightEnd-Lpos+1;

	while(Lpos<=LeftEnd && Rpos<=RightEnd)	// main loop
		if(A[Lpos]<=A[Rpos])
			TmpArray[TmpPos++]=A[Lpos++];
		else
			TmpArray[TmpPos++]=A[Rpos++];

	while(Lpos<=LeftEnd)
		TmpArray[TmpPos++]=A[Lpos++];
	while(Rpos<=RightEnd)
		TmpArray[TmpPos++]=A[Rpos++];

	for(i=0;i<NumElements;i++,RightEnd--)	// cpoy tmparray back
		A[RightEnd]=TmpArray[RightEnd];
}

void MSort(ElementType A[],ElementType TmpArray[],int Left,int Right)
{
	int Center;

	if(Left<Right)
	{
		Center=(Left+Right)/2;
		MSort(A,TmpArray,Left,Center);
		MSort(A,TmpArray,Center+1,Right);
		Merge(A,TmpArray,Left,Center+1,Right);
	}
}

void MergeSort(ElementType A[],int N)
{
	ElementType *TmpArray;

	TmpArray=malloc(N * sizeof(ElementType));
	if(TmpArray!=NULL)
	{
		MSort(A,TmpArray,0,N-1);
		free(TmpArray);
	}
	else
		FatalError("No space for tmp array!!!");
}

void Print(ElementType A[],int N)
{
	int i;
	for(i=0;i<N;i++)
		printf("%d ",A[i]);
	printf("\n");
}

int main()
{
	int i,k;
	ElementType A[Size];

	srand((unsigned int)time(NULL));
	for(i=0;i<Size;i++)
		A[i]=rand()%100+1;
	printf("未排序时：");
	Print(A,Size);

	MergeSort(A,Size);
	printf("使用归并排序结果为：");

	Print(A,Size);	
	return 0;
}
