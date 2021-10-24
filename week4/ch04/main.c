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
	KeyNode *BucketTable=malloc(BucketSize * sizeof(KeyNode));
	
	k = NULL;
	for(i=0;i<BucketSize;i++)
	{
		BucketTable[i]=malloc(sizeof(KeyNode));
		BucketTable[i]->key=0;                 //桶的第一个节点中key表示桶内数据量，初始值为0
		BucketTable[i]->next=NULL;
	}
	for(j=0;j<size;j++)
	{
		node=malloc(sizeof(KeyNode));        //为节点分配空间
		node->key=keys[j];
		node->next=NULL;
		index=keys[j]/10;                 //分桶
		p=BucketTable[index];
		if(p->key==0)                            //若为空桶，直接往后接
		{
			BucketTable[index]->next = node;
			(BucketTable[index]->key)++;
		}
		else
		{
			while(p->next!=NULL && p->next->key <= node->key)    //若不为空桶，类比链表插入
				p = p->next;               
			node->next=p->next;                 //插入节点
			p->next=node;
			(BucketTable[index]->key)++;           //记录数据量加一
		}
	}

	printf("桶排序结果为：");
	for(i=0;i<BucketSize;i++)                   //外循环每个桶
		for(k=BucketTable[i]->next;k!=NULL;k=k->next)     //内循环桶内依次输出
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
