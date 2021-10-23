#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct node;
typedef struct node *PtrtoNode;
typedef PtrtoNode KeyNode;
typedef PtrtoNode Position;

#define Size 50
 
struct node
{
	int key;
	Position next;
};
 
void BucketSort(int keys[],int size,int BucketSize)
{
	int i,j,index;
	KeyNode p,k;
	KeyNode node;
	KeyNode *BucketTable=malloc(BucketSize*sizeof(KeyNode*));
	
	k = NULL;
	for(i=0;i<BucketSize;i++)
	{
		BucketTable[i]=malloc(sizeof(KeyNode));
		BucketTable[i]->key=0;
		BucketTable[i]->next=NULL;
	}
	for(j=0;j<size;j++)
	{
		node=malloc(sizeof(KeyNode));
		node->key=keys[j];
		node->next=NULL;
		index=keys[j]/10;
		p=BucketTable[index];
		if(p->key==0)
		{
			BucketTable[index]->next = node;
			(BucketTable[index]->key)++;
		}
		else
		{
			while(p->next!=NULL && p->next->key<=node->key)
				p = p->next;
			node->next=p->next;
			p->next=node;
			(BucketTable[index]->key)++;
		}
	}

	printf("桶排序结果为：");
	for(i=0;i<BucketSize;i++)
		for(k=BucketTable[i]->next;k!=NULL;k=k->next)
			printf("%d ",k->key);
	printf("\n");
}
 
 
int main()
{
	int i;
	int data[Size];
	
	srand((unsigned int)time(NULL));
	for(i=0;i<Size;i++)
		data[i]=rand()%100+1;
	
	BucketSort(data,Size,10);
}
