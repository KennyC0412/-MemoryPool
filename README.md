# -MemoryPool
基本结构:MemoryBlock存放每一块内存块的信息：编号，引用次数，所属内存池，下一块位置，是否在内存池中
MemoryAlloc为内存池,其中有内存申请函数,内存池地址，内存池头部指针，内存块大小和数量，并负责在结束后释放申请的内存
MemoryManage用于管理内存池中内存的申请和释放





基本逻辑：重载运算符operator new和operator delete,其调用内存管理类中的分配函数，内存管理类使用单例模式避免反复初始化。
首先会初始化一块内存区域，并使用pHead标记头部，将每一部分以链表的形式连起来。
申请分配一块内存时，首先检查其大小是否超出最大设置的内存大小，若超出则直接调用系统函数进行分配，并将其封装上一个MemoryBlock块以便管理
若未超出，则调用对应的分配函数在内存池中进行分配，直接使用pHead所指向的内存块返回。相应的回收内存时只需要将pHead指向回收内存的头部并调整next指针即可。
回收一块内存时，若该内存为系统分配(可以从是否在内存池中这个标志位判断)，则直接调用free释放。否则调用相应的回收内存函数，过程如上。

如何寻找可用的内存块：初始化一个内存池映射数组，并将其与一个声明大小和数量的内存池进行映射。
