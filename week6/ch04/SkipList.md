>这个代码是确定性跳跃表，它是从单链表中衍生出来的，它的主要功能就是查找，插入和删除。当对一个单链表作查询时需要的是O（N）的时间，但如果在这个单链表上增加索引，就能节省到O（logN）的期望运行时间。
>
>这里引出了一个新的概念叫间隙容量，每一个间隙的容量为1、2或3的叫1-2-3确定性跳跃表。这个程序是1-2-3确定性跳跃表的链表实现方法，一开始对我来说有点难以理解，因为没有看懂它究竟是怎么从抽象的跳跃表图示转到实际实现结构。插入和删除都挺复杂，插入中最主要需要考虑插入后当间隙容量达到3时需要增加高度，而删除时相反，当间隙容量为1需要把间隙放大，这里可以从相邻的借一点也可以降低形成间隙的节点的高度两个方面着手。根据书中所说，确定性跳跃表的性能似乎要比红黑树要强，虽然要似乎付出空间的代价（最坏情况下有2N个节点），但某些情况实际上使用的空间却少于红黑树。
