#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef int HugeInt;

HugeInt Witness(HugeInt A,HugeInt i,HugeInt N)
{
	HugeInt X,Y;
	
	if(i==0)
		return 1;

	X=Witness(A,i/2,N);
	if(X==0)  //if N is recursively composite,stop
		return 0;

	//N is not prime if we find a non-trivial root of 1
	Y=(X*X)%N;
	if(Y==1 && X!=1 && X!=N-1)
		return 0;

	if(i%2!=0)
		Y=(A*Y)%N;
	return Y;
}

RandInt(int a,int b)
{
	srand((unsigned)time(NULL));
	return rand()%(b-a+1)+a;
}

int IsPrime(HugeInt N)
{
	return Witness(RandInt(2,N-2),N-1,N)==1;
}

int main()
{
	HugeInt Huge=3949;
	if(IsPrime(Huge))
		printf("%d is prime\n",Huge);
	else
		printf("%d is not prime\n",Huge);

	return 0;
}
