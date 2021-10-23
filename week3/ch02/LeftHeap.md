>这个代码是左式堆，最主要的功能就是两个左式堆的合并，这也是难点。
>
>我觉得左式堆是一个很有意思的结构，它跟之前学的AVL树完全不一样，AVL追求平衡，它追求不平衡，但是各有优势。这里出现了一个新名词叫零路径长，用它来判断左式堆的是否。这个代码其实以树的结构为基础，以其固有的特性让一部分的判断条件很简洁，这一点非常重要。比如，在合并堆时，当H1的left为Null时，可以直接讲H2变成H1的left，因为此时完全可以断定H1它没有右子堆。再由堆的性质，查找最小值也很方便，删除不过是删除最小值之后，将左子堆和右子堆进行一次合并操作。这个代码在初始化时出了一个问题，在用初始化函数初始化后，无法在根处插入数值，当直接用Null去初始化时就可以，我还不太理解为什么。