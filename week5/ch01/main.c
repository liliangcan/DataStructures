#include<stdio.h>
#include<stdlib.h>

int Fibonacci(int N)
{
	int i,Last,NextToLast,Answer;

	if(N<=1)
		return 1;

	Last=NextToLast=1;
	for(i=2;i<=N;i++)
	{
		Answer=Last+NextToLast;
		NextToLast=Last;
		Last=Answer;
	}
	return Answer;

}

double Eval(int N)
{
	int i,j;
	double Sum,Answer;
	double *C;

	C=malloc(sizeof(double)*(N+1));
	if(C==NULL)
		printf("Out of space!!!");

	C[0]=1.0;
	for(i=1;i<=N;i++)
	{
		Sum=0.0;
		for(j=0;j<i;j++)
			Sum+=C[j];
		C[i]=2.0*Sum/i+i;
	}

	Answer=C[N];
	free(C);

	return Answer;
}

int main()
{
	int Key;

	Key=Fibonacci(10);
	printf("斐波拉契数列F(10)=%d\n",Key);

	Key=(int)Eval(10);
	printf("数列C(10)=%d\n",Key);

	return 0;
}
