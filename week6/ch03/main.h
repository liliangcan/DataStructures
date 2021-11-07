#ifdef _AATree_H

AATree Initialize(void);
AATree SingleRotateWithLeft(AATree T);
AATree SingleRotateWithRight(AATree T);
AATree Insert(ElementType Item,AATree T);
AATree Split(AATree T);
AATree Skew(AATree T);
AATree Remove(ElementType Item,AATree T);

#endif /* _AATree_H */
