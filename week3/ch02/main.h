/***************.h文件*******************/

#ifdef _LeftHeap_H

/* Minimal set of priority queue operations */
/* Note that nodes will be shared among several */
/* leftist heaps after a merge;the user must */
/* make sure to not use the old leftist heaps */

PriorityQueue Initialize(void);
ElementType FindMin(PriorityQueue H);
int IsEmpty(PriorityQueue H);
PriorityQueue Merge(PriorityQueue H1,PriorityQueue H2);
void Print(PriorityQueue H);

#define Insert(X,H)  (H=Insert1((X),H))
#define DeleteMin(H)  (H=DeleteMin1(H))

PriorityQueue Insert1(ElementType X,PriorityQueue H);
PriorityQueue DeleteMin1(PriorityQueue H);

#endif
