## 底层原理
- STL中的vector与map底层原理
    - vector。vector是动态数组，通过预分配空间来降低二次分配的成本，当已分配空间不够用时，就需要重新分配空间，并把数据挪到新的空间去
    - map。map是一个键值存储，其底层实现是红黑树
    - [《C++ vector（STL vector）底层实现机制》](http://c.biancheng.net/view/6901.html)

- STL 的 unordered_map 和 map 的区别
    - unordered_map。底层实现是哈希表, 无序的，查找搜索复杂度是 O(1)
    - map。底层实现是红黑树。有序的,查找搜索复杂度是O(logN)。

- unorder_map底层原理
  - hash表+拉链法解决冲突
  - 负载因子（load factor）
  ```
  负载因子 = 容器存储的总键值对 / 桶数
  ```
  - rehash。当负载因子大于一定阈值时，为了减少hash冲突，需要扩充桶的数量，并对已有的值重新计算hash值。如果数值比较多，那么rehash的过程可能是渐进式的，有old和new两张hash表，通过读写触发渐进式rehash迁移（可以参考golang的map实现）
  - [《C++ STL无序容器底层实现原理（深度剖析）》](http://c.biancheng.net/view/7235.html)
  - [《哈希表（散列表）详解（包含哈希表处理冲突的方法）》](哈希表（散列表）详解（包含哈希表处理冲突的方法）)

- 介绍一下 STL 源码的内容
  - STL分为六大组件
    - 容器(container)：常用数据结构，大致分为两类，序列容器，如vector，list，deque，关联容器，如set，map。在实现上，是类模板(class template)
    - 迭代器(iterator)：一套访问容器的接口，行为类似于指针。它为不同算法提供的相对统一的容器访问方式，使得设计算法时无需关注过多关注数据。（“算法”指广义的算法，操作数据的逻辑代码都可认为是算法）
    - 算法(algorithm)：提供一套常用的算法，如sort，search，copy，erase … 在实现上，可以认为是一种函数模板(function template)。
    - 配置器(allocator)：为容器提供空间配置和释放，对象构造和析构的服务，也是一个class template。
    - 仿函数(functor)：作为函数使用的对象，用于泛化算法中的操作。
    - 配接器(adapter)：将一种容器修饰为功能不同的另一种容器，如以容器vector为基础，在其上实现stack，stack的行为也是一种容器。这就是一种配接器。除此之外，还有迭代器配接器和仿函数配接器。
  - [《《STL源码剖析》提炼总结：概览》](https://zhuanlan.zhihu.com/p/31505598)

- map用find和[]的区别
  - 下标运算符[]。将关键码作为下标去执行查找，并返回对应的值；如果不存在这个关键码，就将一个具有该关键码和值类型的默认值的项插入这个map。如果这个对象的类没有默认构造函数怎么办？编译不会通过
  - find。用关键码执行查找，找到了返回该位置的迭代器；如果不存在这个关键码，就返回尾迭代器


- vector和list的区别，哪个对缓存更友好（空间局部性更好）
  - vector是连续的内存存储，空间局部性更好一些

- map中为何使用红黑树而不是二叉平衡树
  - 红黑树是一种弱平衡二叉树（由于是弱平衡，可以看到，在相同的节点情况下，AVL树的高度低于红黑树），相对于要求严格的AVL树来说，它的旋转次数少，所以对于搜索，插入，删除操作较多的情况下，我们就用红黑树

- vector：是否能存裸指针
  - 可以，不过存在野指针风险，最好不要存裸指针

- vector v1(100,0) 和 vector v2(200,0) ，它们sizeof大小分别为多少
  - sizeof(vec)只取决于vector里面存放的数据类型，与元素个数无关，因为存储数据的内存是从堆上分配，vector中只保存了指针

- vector使用迭代器进行循环，当循环开始时push_back一个数在后面，会发生什么
  - 可能没有问题，也可能迭代器失效导致程序崩溃
  - 如果push_back导致vector做了扩容操作，迭代器就会失效

- vector的导致迭代器失效的操作，vector和list的适用场景
  - vector。元素是分配在连续的内存中，insert和erase操作，都会使得删除点和插入点之后的元素挪位置，所以，插入点和删除掉之后的迭代器全部失效，也就是说insert(*iter)(或erase(*iter))，然后在iter++，是没有意义的。解决方法：erase(*iter)的返回值是下一个有效迭代器的值。 iter =cont.erase(iter)
  - list。对于list型的数据结构，使用了不连续分配的内存，删除运算使指向删除位置的迭代器失效，但是不会失效其他迭代器.解决办法两种，erase(*iter)会返回下一个有效迭代器的值，或者erase(iter++)
  - 树形结构。使用红黑树来存储数据，插入不会使得任何迭代器失效；删除运算使指向删除位置的迭代器失效，但是不会失效其他迭代器.erase迭代器只是被删元素的迭代器失效，但是返回值为void，所以要采用erase(iter++)的方式删除迭代器


- list的实现
  - 底层是用双向链表实现的。有的STL可能是双向循环链表

## 迭代器
- STL库为什么要设计迭代器
  - 迭代器iterator 提供了一种一般化的方法对顺序或关联容器类型中的每个元素进行连续访问

- 迭代器的种类
  - 输入。从容器中读取元素。输入迭代器只能一次读入一个元素向前移动，输入迭代器只支持一遍算法，同一个输入迭代器不能两遍遍历一个序列
  - 输出。向容器中写入元素。输出迭代器只能一次一个元素向前移动。输出迭代器只支持一遍算法，统一输出迭代器不能两次遍历一个序列
  - 正向。组合输入迭代器和输出迭代器的功能，并保留在容器中的位置
  - 双向。组合正向迭代器和逆向迭代器的功能，支持多遍算法
  - 随机访问。组合双向迭代器的功能与直接访问容器中任何元素的功能，即可向前向后跳过任意个元素






## 内存管理
- allocator，涉及到了内存池机制（优点、怎么做的）
  - 双层级配置器。第一级采用malloc、free，第二级视情况采用不同策略。
  - ![](http://images-1251273400.cosgz.myqcloud.com/20201017101005.png)
  - 申请流程如下
  ![](http://images-1251273400.cosgz.myqcloud.com/20201017101033.png)
  - 释放流程如下
  ![](http://images-1251273400.cosgz.myqcloud.com/20201017101047.png)
  - [《STL内存池是怎么实现的》](https://blog.csdn.net/weixin_33912638/article/details/85898253?utm_medium=distribute.pc_relevant_t0.none-task-blog-BlogCommendFromMachineLearnPai2-1.channel_param&depth_1-utm_source=distribute.pc_relevant_t0.none-task-blog-BlogCommendFromMachineLearnPai2-1.channel_param)
  - [《STL中的内存池管理技术》](https://blog.csdn.net/a987073381/article/details/52245795)
- STL 中的内存管理(allocator)的原理, 以及如何让它线程安全
  - 二级空间配置器保存的空闲内存块链表数组，对它的申请和释放都需要加锁
  - 锁的实现利用了RAII，来实现锁的自动释放，避免申请内存的线程异常退出导致锁没有释放
  ```c++
  static void* Allocate(size_t n)
  {
    void * ret = 0;
        __TRACE("二级空间配置器申请n = %u\n",n);
        if(n>_MAX_BYTES)
            ret = MallocAlloc::Allocate(n);

        _Obj* volatile * __my_free_list = _freeList + _FreeListIndex(n);

        //利用RAII（资源获取即初始化原则）进行封装，保证 即使内部抛出异常，依旧执行解锁操作
        #ifdef __STL_THREADS
          _Lock __lock_instance;
        #endif
        _Obj* __result = *__my_free_list;
    
        if (__result == 0)
            ret = _Refill(RoundUp(n));
        else
        {
            *__my_free_list = __result -> _freeListLink;
            ret = __result;
        }
        return ret;
    }
  ```
  - [《STL空间配置器那点事》](https://www.cnblogs.com/lang5230/p/5556611.html)
  - [《stl空间配置器线程安全问题补充》](https://www.cnblogs.com/lang5230/p/5576336.html)

- vector内存扩充的机制
    - 先申请一定的大小的数组, 当数组填满之后,另外申请一块原数组两倍大的新数组, 然后把原数组的数据拷贝到新数组, 最后释放原数组的大小

- STL容器的数据实际存在什么位置？
  - 如果大于128Byte，就直接调用malloc从堆上申请内存
  - 如果小于182Byte，则从二级空间配置器的缓冲中申请合适的内存块，不过二级空间配置器的内存也是从堆上申请的