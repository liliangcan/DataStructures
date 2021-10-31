#include<stdio.h>

#define Infinity 999999

#define N 10

void OptMatrix(const long C[],int N,TwoDimArray **M,TwoDimArray **LastChange,int N,int N,int N,int N)
{
	int i,k,Left,Right;
	long ThisM;

	for(Left=1;Left<=N;Left++)
		M[Left][Left]=0;
	for(k=1;k<N;k++)         //k is right-left
		for(Left=1;Left<=N-k;Left++)
		{
			//for each position
			Right=Left+k;
			M[Left][Right]=Infinity;
			for(i=Left;i<Right;i++)
			{
				ThisM=M[Left][i]+M[i+1][Right]+C[Left-1]*C[i]*C[Right];
				if(ThisM<M[Left][Right])
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
	TwoDimArray M[N][N];
	TwoDimArray LastChange[N][N];
	int C[]={43,45,76,78,34,65,44,55,66,77};

	for(i=0;i<N;i++)
		for(j=0;j<N;j++)
		{
			M[i][j]=0;
			LastChange[i][j]=0;
		}

	OptMatrix(C,N,M,LastChange,N,N,N,N);

	return 0;
}