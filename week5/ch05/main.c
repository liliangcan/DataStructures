#include<stdio.h>

#define Infinity 99999
//#define N 10
#define N 4

typedef int TowDimArray[N][N];

void OptMatrix(const long C[],TowDimArray M,TowDimArray LastChange)
{
	int i,k,Left,Right;
	long ThisM;

	for(Left=1;Left<=N;Left++)
		M[Left][Left]=0;

	for(k=1 ;k<N ;k++)         //k is right-left
		for(Left=1;Left<=N-k;Left++)
		{
			//for each position
			Right=Left+k;
			M[Left][Right]=Infinity;
			for(i=Left;i<Right;i++)
			{
				ThisM = M[Left][i] + M[i+1][Right] + C[Left-1]*C[i]*C[Right];
				if(ThisM < M[Left][Right])
				{
					//update min
					M[Left][Right]=ThisM;
					LastChange[Left][Right]=i;
				}
			}
		}
}

int main()
{
	int i,j;
	int M[N][N],LastChange[N][N];
//	long C[]={3,4,5,6,7,8,9,10,11,12,13};
	long C[]={50,10,40,30,5};

	OptMatrix(C,M,LastChange);
	for(i=1;i<=N;i++)
	{
		for(j=i;j<=N;j++)
			printf("%d ",M[i][j]);
		printf("\n");
	}
	printf("%d\n ",M[N-1][N]);			//这个位置的数值有问题

	return 0;
}
