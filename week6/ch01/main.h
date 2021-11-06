#ifdef _SplayTree_H

SplayTree MakeEmpty(SplayTree T);
SplayTree Find(ElementType X,SplayTree T);
SplayTree FindMin(SplayTree T);
SplayTree FindMax(SplayTree T);
SplayTree Initialize(void);
SplayTree Insert(ElementType X,SplayTree T);
SplayTree Remove(ElementType Item,SplayTree T);
ElementType Retrieve(SplayTree T);	//get root's item

#endif /* _SplayTree_H */
