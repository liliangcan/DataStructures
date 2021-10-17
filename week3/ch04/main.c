/****************.c文件部分****************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef int ElementType;
#define LeftChild(i) (2*(i)+1)
#define Size 15

void PercDown(ElementType A[],int i,int N)
{
	int Child;
	ElementType Tmp;

	for(Tmp=A[i];LeftChild(i)<N;i=Child)
	{
		Child=LeftChild(i);
		if(Child!=N-1 && A[Child+1]>A[Child])
			Child++;
		if(Tmp<A[Child])
			A[i]=A[Child];
		else
			break;
	}
	A[i]=Tmp;
}

void Swap(ElementType *X,ElementType *Y)
{
	ElementType Tmp;
	Tmp=*X;
	*X=*Y;
	*Y=Tmp;
}
void HeapSort(ElementType A[],int N)
{
	int i;

	for(i=N/2;i>=0;i--)
		PercDown(A,i,N);  /* buildheap */
	for(i=N-1;i>0;i--)
	{
		Swap(&A[0],&A[i]);  /* deletemax */
		PercDown(A,0,i);
	}
}

void InsertionSort(ElementType A[],int N)
{
	int j,P;

	ElementType Tmp;
	for(P=1;P<N;P++)
	{
		Tmp=A[P];
		for(j=P;j>0 && A[j-1]>Tmp;j--)
			A[j]=A[j-1];
		A[j]=Tmp;
	}
}

void ShellSort(ElementType A[],int N)
{
	int i,j,Increment;
	ElementType Tmp;

	for(Increment=N/2;Increment>0;Increment/=2)
		for(i=Increment;i<N;i++)
		{
			Tmp=A[i];
			for(j=i;j>=Increment;j-=Increment)
				if(Tmp<A[j-Increment])
					A[j]=A[j-Increment];
				else
					break;
			A[j]=Tmp;
		}
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
	int i;
	ElementType A[Size];

	srand((unsigned int)time(NULL));
	for(i=0;i<15;i++)
		A[i]=rand()%100+1;
	printf("未排序时：");
	Print(A,Size);

//	InsertionSort(A,Size);
//	printf("使用插入排序结果为：");

//	ShellSort(A,Size);
//	printf("使用希尔排序结果为：");

	HeapSort(A,Size);
	printf("使用堆排序结果为：");

	Print(A,Size);
	return 0;
}
