#ifdef _RedBlackTree_H

RedBlackTree Initialize(void);
RredBlackTree Insert(ElementType Item,RedBlackTree T);
void Delete(ElementType Item,RedBlackTree T);
void PrintTree(RedBlackTree T);
Position Find(ElementType Item,RedBlackTree T);
RedBlackTree SingleRotateWithLeft(RedBlackTree T);
RedBlackTree SingleRotateWithRight(RedBlackTree T);

#endif /* _RedBlackTree_H */
