>这个代码是关于AA树堆实现，它其实就是一个带有附加条件的红黑树，因为红黑树需要判断许多可能旋转的情形，而导致编程相当复杂。而AA树规定一个节点最多可以有一个红儿子。
>
>我觉得更简单的一种理解就是，当儿子是红的时候，与其父节点在同一个层次，只有黑节点会到下一个层次，这使得整棵树的层次不会像一般红黑树一样差别太大。这个程序最主要的部分就是消除左水平链接和两个连续的右水平链接，分别通过右旋转和左旋转解决，称为skew和split。在skew中虽然消灭了一个左水平链接但可能创造连续的右水平链接，所以需要再使用一次split。在AA树中比较复杂的就是删除，书中为了有助于解决问题，使用了deleteptr和lastptr，在往下遍历的过程中，deleteptr指向包含了需要删除的项的节点，lastptr指向查找终止处的树叶。同样在之后的操作中需要利用skew和split来调整树的结构使之还满足AA树的性质。
