> 这个代码是二叉查找树，主要功能是置空、查找、插入、删除、去元素，另外加了中序遍历的函数。
> 
> 根据这次代码练习，我觉得突出的一个最重要的问题就是，我对初始化一直没有根本性弄懂，对结构初始化的时候我基本都会出点小问题，即使没有报错也经常运行不出来，说明我对结构的认知还是处于会用但却不是百分百理解的阶段。然后就是当函数运行的时候没有特别注意返回值的保存，在插入的时候导致一直在树根地方不断插入数据却对函数外的树没有改变。结果就是运行程序时输出异常却一时找不到错误根源。
> 
> 关于其他的部分没有什么问题，这个二叉查找树的练习代码让我看到了递归的实例用法，在编写代码时的确看上去很简洁，但是通过测试程序的输出也能发现在不断的引用函数形成堆栈时开销也不小。