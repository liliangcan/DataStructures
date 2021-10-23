#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef int ElementType;
#define Size 15
#define Cutoff 3

void FatalError(char *s)
{
    printf("%s\n",s);
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

void Swap(ElementType *a,ElementType *b)
{
	ElementType Tmp;
	Tmp=*a;
	*a=*b;
	*b=Tmp;
}

ElementType Median3(ElementType A[],int Left,int Right)
{
	int Center=(Left+Right)/2;

	if(A[Left]>A[Center])
		Swap(&A[Left],&A[Center]);
	if(A[Left]>A[Right])
		Swap(&A[Left],&A[Right]);
	if(A[Center]>A[Right])
		Swap(&A[Center],&A[Right]);

	// invariant: A[Left]<=A[Center]<=A[Right]

	Swap(&A[Center],&A[Right-1]);      // hide pivot
	return A[Right-1];           //return pivot
}

void Qsort(ElementType A[],int Left,int Right)
{
	int i,j;
	ElementType Pivot;

	if(Left+Cutoff<=Right)
	{
		Pivot=Median3(A,Left,Right);
		i=Left;
		j=Right-1;
		for(;;)
		{								//当A[i]=A[j]=Pivot,会产生一个无限循环
			while(A[++i]<Pivot){}		//while(A[i]<Pivot) i++;
			while(A[--j]>Pivot){}		//while(A[j]>Pivot) j--;
			if(i<j)
				Swap(&A[i],&A[j]);
			else
				break;
		}
		Swap(&A[i],&A[Right-1]);  // restore pivot

		Qsort(A,Left,i-1);
		Qsort(A,i+1,Right);
	}
	else  // do an insertion sort on the subarray
		InsertionSort(A+Left,Right-Left+1);
}

void Qselect(ElementType A[],int k,int Left,int Right)
{
	int i,j;
	ElementType Pivot;

	if(Left+Cutoff<=Right)
	{
		Pivot=Median3(A,Left,Right);
		i=Left;
		j=Right-1;
		for(;;)
		{								//当A[i]=A[j]=Pivot,会产生一个无限循环
			while(A[++i]<Pivot){}		//while(A[i]<Pivot) i++;
			while(A[--j]>Pivot){}		//while(A[j]>Pivot) j--;
			if(i<j)
				Swap(&A[i],&A[j]);
			else
				break;
		}
		Swap(&A[i],&A[Right-1]);  // restore pivot

		if(k<=i)
			Qselect(A,k,Left,i-1);
		if(k>i+1)
			Qselect(A,k,i+1,Right);
	}
	else  // do an insertion sort on the subarray
		InsertionSort(A+Left,Right-Left+1);

}

void QuickSort(ElementType A[],int N)
{
	Qsort(A,0,N-1);
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

	k=5;

	srand((unsigned int)time(NULL));
	for(i=0;i<Size;i++)
		A[i]=rand()%100+1;
	printf("未排序时：");
	Print(A,Size);

	QuickSort(A,Size);
	printf("使用快速排序结果为：");

	Print(A,Size);	
	
	Qselect(A,k,0,Size-1);
	printf("使用快速选择，第%d小的数为：%d\n",k,A[k-1]);
	return 0;
}
