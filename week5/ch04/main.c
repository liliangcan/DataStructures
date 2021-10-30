#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
 
#define TRUE 1
#define FALSE 0
#define BUILDED 1
#define UNBUILDING 0
 
int x_i=0;	
 
int cmp(const void * a, const void * b)			//排序
{
    return *(int*)a - *(int*)b;
}
 
int Empty(int **a,int n)
{
    int i;
    for(i=0;i<n;i++)
	{
        if(a[1][i]==UNBUILDING)
		{
            return FALSE;
        }
    }
    return TRUE;
}
 
int DeleteMax(int **a,int n)
{
    int i,max=0,max_i=0;
    for(i=0;i<n;i++)
	{
        if( a[0][i]>max && a[1][i]==UNBUILDING)
		{
            max=a[0][i];
            max_i=i;
        }
    }
    a[1][max_i]=BUILDED;
    return max;
}
 
int FindMax(int **a,int n)
{
    int i,max=0;
    for(i=0;i<n;i++)
	{
        if( a[0][i]>max && a[1][i]==UNBUILDING)
		{
            max=a[0][i];
        }
    }
    return max;
}
 
void Delete(int num,int **a,int n)
{
    int i;
    for(i=0;i<n;i++)
	{
        if(a[0][i]==num && a[1][i]==UNBUILDING)
		{
            a[1][i]=BUILDED;
            return;
        }
    }
}
 
void Insert(int num,int **a,int n)
{
    int i;
    for(i=0;i<n;i++)
	{
        if(a[0][i]==num && a[1][i]==BUILDED)
		{
            a[1][i]=UNBUILDING;
            return;
        }
    }
}
 
int Place(int *x,int **a,int n,int pos)
{
	int i,j,k,t=0;
	int temp_i=0;
	int *temp;
    int Dmax,Found=FALSE;
	temp=malloc(n*sizeof(int));
 
    if(Empty(a,n))
	{								//重排成功
        x_i=pos;
        return TRUE;
    }
 
    Dmax=FindMax(a,n);					//获取最大数
 
    memset(temp,0,sizeof(temp));
 
    for(i=0;i<pos;i++)
	{					//检测最大数是否可以进入重排
        k=0;
        for(j=0;j<n;j++)
		{
            if(a[0][j]==abs(Dmax-x[i]) && a[1][j]==UNBUILDING)
			{
                k=1;
                temp[temp_i++]=a[0][j];
                a[1][j]=BUILDED;
                break;
            }
        }
        if(k==0)
		{
            break;
        }
        if(k==1 && i==pos-1)
		{									//进入重排下一个
            x[pos++]=Dmax;
            Found=Place(x,a,n,pos);
            t=1;
        }
    }
    if(!Found)
	{
        for(i=0;i<temp_i;i++)
		{										//重新放回路段数组
            Insert(temp[i],a,n);
        }
        if(t==1)									//进入重排下一个,但不成功
            pos--;
    }
 
    temp_i=t=0;
    if(!Found)
	{
        Dmax=x[1]-Dmax;									//获取最大值的补植
        for(i=0;i<pos;i++)
		{
            k=0;
            for(j=0;j<n;j++)
			{								//是否可以重排
                if(a[0][j]==abs(Dmax-x[i]) && a[1][j]==UNBUILDING)
				{
                    k=1;
                    temp[temp_i++]=a[0][j];
                    a[1][j]=BUILDED;
                    break;
                }
            }
            if(k==0)
			{
                break;
            }
            if(k==1 && i==pos-1)
			{									//---递归进入重排
                x[pos++]=Dmax;
                Found=Place(x,a,n,pos);
                t = 1;
            }
        }
        if(!Found)
		{
            for(i=0;i<temp_i;i++)
			{
                Insert(temp[i],a,n);
            }
            if(t == 1)
                pos--;
        }
    }
    return Found;
}
 
int Turnpike(int *x,int **a,int n)
{
    int i;
    x[0]=0;
    x[1]=DeleteMax(a,n);
    x[2]=DeleteMax(a,n);
    for(i=0;i<n;i++)
	{
        if(a[0][i]==abs(x[1]-x[2]) && a[1][i]==UNBUILDING)
		{
            a[1][i]=BUILDED;
            return Place(x,a,n,3);
        }
    }
    return FALSE;
}
 
int main()
{
    int i,j,n;
	int *x;							//重建数组；
	int **a=malloc(2*sizeof(int*));
	n=20;
	x=malloc((n/2+1)* sizeof(int));
	
//    scanf("%d",&n);
    
    for(i=0;i<2;i++)
        a[i]=malloc(n*sizeof(int));
    for(j=0;j<n;j++)
	{
        scanf("%d",&a[0][j]);
        a[1][j]=UNBUILDING;
    }
 
    if(Turnpike(&x[0],a,n))					//重排成功
        printf("Good! ok\n");
    else
        printf("No! error\n");
 
    for(i=0;i<n;i++)					//检测是否完全重排
        printf("%d ",a[1][i]);
    printf("\n");
 
    qsort(x,x_i,sizeof(int*),cmp);			//排序
    for(i=0;i<x_i;i++)
        printf("%d ",x[i]);
    printf("\n");
    return 0;
}
